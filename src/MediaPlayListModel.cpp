// C++ includes
#include <math.h>

// 2W includes
#include "include/MediaPlayListModel.h"

// Modify
#include "include/qmediaplaylist.h"

#include <QMediaMetaData>
#include <QMediaDevices>
#include <QAudioDevice>

#include <QMediaPlayer>
#include <QVideoSink>
#include <QAudioOutput>
#include <QMediaFormat>
#include <QIcon>
#include <QMap>
#include <QVariant>


MediaPlayListModel::MediaPlayListModel(QObject *parent
                                       , MediaDataModel* mediaDataModel
                                       , std::shared_ptr<ViewManager> viewManager
                                       )
    : QObject{parent}
    , MUSIC_PATH{QStandardPaths::standardLocations(QStandardPaths::MusicLocation)[0]}
    , VIDEO_PATH{QStandardPaths::standardLocations(QStandardPaths::MoviesLocation)[0]}
    , m_mediaDataModel(mediaDataModel)
    , m_isMusicLoading{false}
    , m_isVideoLoading{false}
    , m_isMediaLoading{false}
    , m_viewManager{viewManager}
    , m_mediaPlayer{std::make_shared<Player>(nullptr)}
    , m_mediaPlaylist{std::make_shared<QMediaPlaylist>(nullptr)}
    , m_musicTracker{std::make_shared<MediaTrackingFolder>(true)}
    , m_videoTracker{std::make_shared<MediaTrackingFolder>(false)}
    , m_isMusicMode{true}
    , m_currentMediaPlaying{nullptr}
    , m_duration{0}

{
    setCurrentIndex(-1);


    connect(m_musicTracker.get(), &MediaTrackingFolder::mediaDataLoaded, this, [&](){
        qDebug() << "Set new music media content";
        if(m_isMusicMode)
        {
            if(m_musicTracker->getMediaDataModelList().size() != 0)
            {
                m_mediaDataModel->setMediaDataModelList(m_musicTracker->getMediaDataModelList());
                getAllMediaFiles();
                setIsMusicLoading(false);
            }

        }
        setIsMediaLoading(isMusicLoading() || isVideoLoading());
    });

    connect(m_videoTracker.get(), &MediaTrackingFolder::mediaDataLoaded, this, [&](){
        qDebug() << "Set new video media content";
        if(!m_isMusicMode)
        {
            if(m_videoTracker->getMediaDataModelList().size() != 0)
            {
                m_mediaDataModel->setMediaDataModelList(m_videoTracker->getMediaDataModelList());
                getAllMediaFiles();
                setIsVideoLoading(false);
            }
        }
        else
        {
            // QuanTong
            // Only video need these check conditions
            // Because when first load data without `twData` folder, the `m_isMusicMode` is always `true`
            // The `if` condition above could not be entered -> Lead to `m_isVideoLoading` always is `true`
            // -> It will be display LoadingScreen forever
            if(m_videoTracker->getMediaDataModelList().size() != 0)
            {
                setIsVideoLoading(false);
            }
            else
            {
                setIsVideoLoading(true);
            }
        }
        setIsMediaLoading(isMusicLoading() || isVideoLoading());
    });

    // Check loading to display LoadingScreen
    connect(m_musicTracker.get(), &MediaTrackingFolder::mediaDataReloading, this, [&](){
        resetMedia();
        setIsMusicLoading(true);
        setIsMediaLoading(isMusicLoading() || isVideoLoading());
        if(m_viewManager->getViewState() != Helper::MagicNumbers::ViewScreen::MAINGAUGE.c_str())
        {
            m_viewManager->requestChangeViewState(Helper::MagicNumbers::ViewScreen::SUBGAUGE_MEDIA.c_str()
                                                  , Helper::MagicNumbers::ViewScreen::SUBGAUGE.c_str());
        }
    });
    connect(m_videoTracker.get(), &MediaTrackingFolder::mediaDataReloading, this, [&](){
        resetMedia();
        setIsVideoLoading(true);
        setIsMediaLoading(isMusicLoading() || isVideoLoading());
        if(m_viewManager->getViewState() != Helper::MagicNumbers::ViewScreen::MAINGAUGE.c_str())
        {
            m_viewManager->requestChangeViewState(Helper::MagicNumbers::ViewScreen::SUBGAUGE_MEDIA.c_str()
                                                  , Helper::MagicNumbers::ViewScreen::SUBGAUGE.c_str());
        }
    });

    // Check loading to hide LoadingScreen
    connect(this, &MediaPlayListModel::isMediaLoadingChanged, this, [&](){
        if(!isMediaLoading())
        {
            m_viewManager->requestChangeViewState(Helper::MagicNumbers::ViewScreen::SUBGAUGE_LOADING_SCREEN.c_str()
                                                  , Helper::MagicNumbers::ViewScreen::SUBGAUGE.c_str());
        }
    });

    connect(this, &MediaPlayListModel::isMusicModeChanged, this, [&](){
        if(m_isMusicMode)
        {
            if(m_musicTracker->getMediaDataModelList().size() != 0)
            {
                m_mediaDataModel->setMediaDataModelList(m_musicTracker->getMediaDataModelList());
            }
        }
        else
        {
            if(m_videoTracker->getMediaDataModelList().size() != 0)
            {
                m_mediaDataModel->setMediaDataModelList(m_videoTracker->getMediaDataModelList());
            }
        }
        getAllMediaFiles();
    });


    connect(m_mediaPlayer.get(), &Player::durationChanged, this, [&](qint64 duration){
        duration = floor(duration / 1000);
        setDuration(duration);
    });


//        connect(m_mediaPlayer.get(), &Player::mediaStatusChanged(QMediaPlayer::MediaStatus)),
//                this, [&](qint64 position){
//    emit onMediaStatusChanged();
//    });


    connect(m_mediaPlayer.get(), &Player::positionChanged, this, [&](qint64 position){
        emit positionChanged();
    });

    //    connect(m_mediaPlayer.get(), &Player::stateChanged, this, [&](QMediaPlayer::PlaybackState newState){
//        setMediaState(newState);
//      });
//    connect(m_mediaPlayer.get(), &QMediaPlayer::playbackStateChanged, this, [&](QMediaPlayer::PlaybackState newState){
//        setMediaState(newState);
//    });

    connect(m_mediaPlaylist.get(), &QMediaPlaylist::sourceChanged, this, [&](QString source){
        m_mediaPlayer->setSource(source);
    });


    connect(m_mediaPlaylist.get(), &QMediaPlaylist::currentIndexChanged, this, [&](int index){
        setCurrentMediaPlaying(m_mediaDataModel->getMediaDataModel(index));

        // Below signal is from 2W, not from QMediaPlaylist
        emit currentIndexChanged(index);

    });



    // QuanTong lazy solution to stop media when has phone call in/out
    connect(m_viewManager.get(), &ViewManager::viewStateChanged, this, [&](QString viewState){
        if(viewState.startsWith("Top"))
        {
            pausePlaying();
        }
    });

    setIsMusicMode(m_isMusicMode);

    // Should not put to Tracker's constructor due to data will be emited lately
    m_musicTracker->startLoadMetaData();
    m_videoTracker->startLoadMetaData();
    m_twMediaDataFolder = m_musicTracker->getTWDataFolder(); // jsonFolder is the same for music or video
    setPlayBackMode(static_cast<int>(REPEAT_TYPES::LOOP));
    setMediaState(m_mediaPlayer->getState());
}

MediaPlayListModel::~MediaPlayListModel(){
    disconnect(this);
    disconnect(m_musicTracker.get());
    disconnect(m_videoTracker.get());
    disconnect(m_mediaPlayer.get());
    disconnect(m_mediaPlaylist.get());
    disconnect(m_viewManager.get());
}

void MediaPlayListModel::getAllMediaFiles()
{
    m_mediaPlaylist->clear();
    if(m_isMusicMode)
    {
        m_mediaPlaylist->addMedia(m_musicTracker->getListMediaContent());

    }
    else
    {
        m_mediaPlaylist->addMedia(m_videoTracker->getListMediaContent());

    }
//    m_mediaPlayer->setPlaylist(m_mediaPlaylist.get());

    // When reload data, index is set to 0 (I guess, because could not use setCurrentIndex())
    // It will return in the body of first if condition -> Only emit to QML


    m_mediaPlayer->setSource((m_mediaPlaylist->currentMedia()).toString());
//    emit currentIndexChanged(0);
    emit currentIndexChanged(-1);
}




void MediaPlayListModel::startPlaying()
{
    if (m_mediaPlaylist->mediaCount() == 0) return;
    if (currentIndex() == -1)
    {
        setCurrentIndex(0);
        m_mediaPlayer->setSource((m_mediaPlaylist->currentMedia()).toString());
        m_mediaPlayer->play();
    }
    else
    {
        if (m_mediaPlayer->getState() == QMediaPlayer::PlayingState) m_mediaPlayer->pause();
        else m_mediaPlayer->play();
    }
//    m_mediaPlayer->play();
    qDebug() << currentIndex() << "<-- Current Media Index";
    qDebug() <<  m_mediaPlaylist->currentMedia() << "<-- Current Media";
    qDebug() << m_mediaPlayer->position()/1000 << "<-- Current position";


}

void MediaPlayListModel::pausePlaying()
{
    m_mediaPlayer->pause();

    if (m_mediaPlayer->getState() == QMediaPlayer::PlayingState)
       {
           m_mediaPlayer->pause();
//           emit mediaStateChanged();
       }
}

void MediaPlayListModel::stopPlaying()
{
    m_mediaPlayer->stop();
//    emit mediaStateChanged();

}

void MediaPlayListModel::playNext()
{
    m_mediaPlaylist->next();
    m_mediaPlayer->setSource((m_mediaPlaylist->currentMedia()).toString());
    qDebug() <<  m_mediaPlaylist->currentMedia() << "<-- Current Media";
}

void MediaPlayListModel::playPrevious()
{
    m_mediaPlaylist->previous();
    m_mediaPlayer->setSource((m_mediaPlaylist->currentMedia()).toString());
    qDebug() <<  m_mediaPlaylist->currentMedia() << "<-- Current Media";
}

int MediaPlayListModel::volume() const

{
    return m_mediaPlayer->volume();

}

void MediaPlayListModel::setVolume(const int &newVolume)
{
    if(volume() == newVolume)
        return;
    m_mediaPlayer->setVolume(newVolume);

    if(newVolume == 0 || newVolume <= 2) {
        m_mediaPlayer->setMuted(true);
    }
    else{
        m_mediaPlayer->setMuted(false);
    }
    emit volumeChanged();
}


int MediaPlayListModel::position() const
{
    return floor(m_mediaPlayer->position()/1000);
}

void MediaPlayListModel::setPosition(const int &newPosition)
{
    if (position() == newPosition)
        return;

    // No need to trigger signal here, due to setPosition had already triggered
    // That is the reason why have a connect fn() to QMediaPlayer::positionChanged above
    m_mediaPlayer->setPosition(newPosition*1000);
}

int MediaPlayListModel::currentIndex() const
{
    return m_mediaPlaylist->currentIndex();
}

void MediaPlayListModel::setCurrentIndex(int newCurrentIndex)
{
    if (currentIndex() == newCurrentIndex)
        return;
    m_mediaPlaylist->setCurrentIndex(newCurrentIndex);
    emit currentIndexChanged(newCurrentIndex);
}

bool MediaPlayListModel::isMusicMode() const
{
    return m_isMusicMode;
}

void MediaPlayListModel::setIsMusicMode(const bool& isMusicMode)
{
    if (m_isMusicMode == isMusicMode)
        return;
    m_isMusicMode = isMusicMode;
    emit isMusicModeChanged();
}

int MediaPlayListModel::mediaState() const
{
    return m_mediaState;
}

void MediaPlayListModel::setMediaState(const int& newMediaState)
{

    if (m_mediaState == newMediaState)
        return;
    m_mediaState = newMediaState;
    emit mediaStateChanged();
}

int MediaPlayListModel::duration() const
{
    return m_duration;
}

void MediaPlayListModel::setDuration(int newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

int MediaPlayListModel::playBackMode() const
{
    return m_playBackMode;
}

void MediaPlayListModel::setPlayBackMode(const int &newPlayBackMode)
{
    if (m_playBackMode == newPlayBackMode)
        return;
    m_playBackMode = newPlayBackMode;

    if (static_cast<int>(REPEAT_TYPES::NUM_OF_ITEMS) > newPlayBackMode)
        m_playBackMode = newPlayBackMode;
    else
        m_playBackMode = static_cast<int>(REPEAT_TYPES::LOOP);

    auto playbackMode = QMediaPlaylist::Loop;
    switch(newPlayBackMode)
    {
    case static_cast<int>(REPEAT_TYPES::LOOP):
        playbackMode = QMediaPlaylist::Loop;
        break;
    case static_cast<int>(REPEAT_TYPES::CURRENT_ITEM_IN_LOOP):
        playbackMode = QMediaPlaylist::CurrentItemInLoop;
        break;
//    case static_cast<int>(REPEAT_TYPES::RANDOM):
//        playbackMode = QMediaPlaylist::Random;
//        break;
    default:
        playbackMode = QMediaPlaylist::Loop;
        break;
    }

    m_mediaPlaylist->setPlaybackMode(playbackMode);
    qDebug()<<m_mediaPlaylist->playbackMode();

    emit playBackModeChanged();
}

void MediaPlayListModel::resetMedia()
{
    // QuanTong
    // This function only invoked when exit the media screen from QML
    // Currently, the reason is to stop video -> Just need to do as below to reload data
    // If you need reset more things in the future -> Please feel free to add them here
    stopPlaying();
    setIsMusicMode(true);
}
//QAbstractVideoSurface *MediaPlayListModel::getVideoSurface() const
QVideoSink *MediaPlayListModel::getVideoSurface() const
{
    return m_videoSurface;
}

void MediaPlayListModel::setVideoSurface(QVideoSink *newVideoSurface)
////void MediaPlayListModel::setVideoSurface(QAbstractVideoSurface  *newVideoSurface)
{
    m_videoSurface = newVideoSurface;
    m_mediaPlayer->setVideoSink(m_videoSurface);
//    m_mediaPlayer->setAudioOutput(m_videoSurface);
    m_mediaPlayer->start();

}

MediaItemDataModel *MediaPlayListModel::currentMediaPlaying() const
{
    return m_currentMediaPlaying;
}

void MediaPlayListModel::setCurrentMediaPlaying(MediaItemDataModel *newCurrentMediaPlaying)
{
    if (m_currentMediaPlaying == newCurrentMediaPlaying)
        return;
    m_currentMediaPlaying = newCurrentMediaPlaying;
    emit currentMediaPlayingChanged();
}

bool MediaPlayListModel::isMusicLoading() const
{
    return m_isMusicLoading;
}

void MediaPlayListModel::setIsMusicLoading(bool newIsMusicLoading)
{
    if (m_isMusicLoading == newIsMusicLoading)
        return;
    m_isMusicLoading = newIsMusicLoading;
    emit isMusicLoadingChanged();
}

bool MediaPlayListModel::isVideoLoading() const
{
    return m_isVideoLoading;
}

void MediaPlayListModel::setIsVideoLoading(bool newIsVideoLoading)
{
    if (m_isVideoLoading == newIsVideoLoading)
        return;
    m_isVideoLoading = newIsVideoLoading;
    emit isVideoLoadingChanged();
}

bool MediaPlayListModel::isMediaLoading() const
{
    return m_isMediaLoading;
}

void MediaPlayListModel::setIsMediaLoading(bool newIsMediaLoading)
{
    if (m_isMediaLoading == newIsMediaLoading)
        return;
    m_isMediaLoading = newIsMediaLoading;
    emit isMediaLoadingChanged();
}



