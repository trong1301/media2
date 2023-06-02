#ifndef MEDIAPLAYLISTMODEL_H
#define MEDIAPLAYLISTMODEL_H

// Qt include
#include <QDir>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QStandardPaths>
#include <QPointer>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoSink>

// 2W include
#include "GuiController.h"
#include "MediaDataModel.h"
#include "MediaTrackingFolder.h"
#include "ViewManager.h"

// Modify include

#include "include/qmediaplaylist.h"
#include "include/Player.h"

class MediaPlayListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int  volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int  position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int  duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(int playBackMode READ playBackMode WRITE setPlayBackMode NOTIFY playBackModeChanged)
    Q_PROPERTY(int mediaState READ mediaState WRITE setMediaState NOTIFY mediaStateChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(bool isMusicMode READ isMusicMode WRITE setIsMusicMode NOTIFY isMusicModeChanged)
    Q_PROPERTY(QString twMediaDataFolder MEMBER m_twMediaDataFolder NOTIFY twMediaDataFolderChanged)
    Q_PROPERTY(QVideoSink* videoSurface READ getVideoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)
    Q_PROPERTY(MediaItemDataModel* currentMediaPlaying READ currentMediaPlaying WRITE setCurrentMediaPlaying NOTIFY currentMediaPlayingChanged)
    Q_PROPERTY(bool isMediaLoading READ isMediaLoading NOTIFY isMediaLoadingChanged)
public:
    explicit MediaPlayListModel(QObject *parent = nullptr, MediaDataModel* mediaDataModel = nullptr, std::shared_ptr<ViewManager> viewManager = nullptr);
    ~MediaPlayListModel();


    void setSource(QString source);
    const QImage &image() const;
    void setImage(const QImage newimage);

    // Video surface help to display video from this model class
    //!
    //! \brief getVideoSurface
    //! \return
    //!
    QVideoSink *getVideoSurface() const;

    //!
    //! \brief setVideoSurface
    //! \param newVideoSurface
    //!
    void setVideoSurface(QVideoSink *newVideoSurface);

    //!
    //! \brief getAllMediaFiles
    //!
    void getAllMediaFiles();

    //!
    //! \brief currentIndex
    //! \return
    //!
    int currentIndex() const;

    //!
    //! \brief setCurrentIndex
    //! \param newCurrentIndex
    //!
    void setCurrentIndex(int newCurrentIndex);

    //!
    //! \brief isMusicMode
    //! \return
    //!
    bool isMusicMode() const;

    //!
    //! \brief setIsMusicMode
    //! \param isMusicMode
    //!
    void setIsMusicMode(const bool& isMusicMode);

    //!
    //! \brief mediaState
    //! \return
    //!
    int mediaState() const;

    //!
    //! \brief setMediaState
    //! \param newMediaState
    //!
    void setMediaState(const int& newMediaState);

    //!
    //! \brief currentMediaPlaying
    //! \return
    //!
    MediaItemDataModel *currentMediaPlaying() const;

    //!
    //! \brief setCurrentMediaPlaying
    //! \param newCurrentMediaPlaying
    //!
    void setCurrentMediaPlaying(MediaItemDataModel *newCurrentMediaPlaying);

    //!
    //! \brief position
    //! \return
    //!
    int position() const;

    //!
    //! \brief setPosition
    //! \param newPosition
    //!
    void setPosition(const int &newPosition);

    //!
    //! \brief duration
    //! \return
    //!
    int duration() const;

    //!
    //! \brief setDuration
    //! \param newDuration
    //!
    void setDuration(int newDuration);

    //!
    //! \brief volume
    //! \return
    //!
    int volume() const;

    //!
    //! \brief setVolume
    //! \param newVolume
    //!
    void setVolume(const int &newVolume);

    //!
    //! \brief playBackMode
    //! \return
    //!

    int playBackMode() const;

    //!
    //! \brief setPlayBackMode
    //! \param newPlayBackMode
    //!
    void setPlayBackMode(const int &newPlayBackMode);

    //!
    //! \brief isMusicLoading
    //! \return
    //!
    bool isMusicLoading() const;

    //!
    //! \brief setIsMusicLoading
    //! \param newIsMusicLoading
    //!
    void setIsMusicLoading(bool newIsMusicLoading);

    //!
    //! \brief isVideoLoading
    //! \return
    //!
    bool isVideoLoading() const;

    //!
    //! \brief setIsVideoLoading
    //! \param newIsVideoLoading
    //!
    void setIsVideoLoading(bool newIsVideoLoading);

    //!
    //! \brief isMediaLoading
    //! \return
    //!
    bool isMediaLoading() const;

    //!
    //! \brief setIsMediaLoading
    //! \param newIsMediaLoading
    //!
    void setIsMediaLoading(bool newIsMediaLoading);

    //!
    //! \brief resetMedia
    //!
    Q_INVOKABLE void resetMedia();

    //!
    //! \brief startPlaying
    //!
    Q_INVOKABLE void startPlaying();

    //!
    //! \brief pausePlaying
    //!
    Q_INVOKABLE void pausePlaying();

    //!
    //! \brief stopPlaying
    //!
    Q_INVOKABLE void stopPlaying();

    //!
    //! \brief playNext
    //!
    Q_INVOKABLE void playNext();

    //!
    //! \brief playPrevious
    //!
    Q_INVOKABLE void playPrevious();


private:
    enum class REPEAT_TYPES{
        LOOP = 0,
        CURRENT_ITEM_IN_LOOP,
        RANDOM,
        NUM_OF_ITEMS = 3
    };

    //!
    //! \brief MUSIC_PATH
    //!
    const QString MUSIC_PATH;

    //!
    //! \brief VIDEO_PATH
    //!
    const QString VIDEO_PATH;

    //!
    //! \brief m_videoSurface
    //!
    QVideoSink *m_videoSurface;
//    QAbstractVideoSurface *m_videoSurface;

    //!
    //! \brief m_mediaDataModel
    //!
    MediaDataModel* m_mediaDataModel;

    //!
    //! \brief m_mediaPlayer
    //!
    std::shared_ptr<Player> m_mediaPlayer;




    //!
    //! \brief m_mediaPlaylist
    //!
    std::shared_ptr<QMediaPlaylist> m_mediaPlaylist;

    //!
    //! \brief m_musicTracker
    //!
    std::shared_ptr<MediaTrackingFolder> m_musicTracker;

    //!
    //! \brief m_videoTracker
    //!
    std::shared_ptr<MediaTrackingFolder> m_videoTracker;

    //!
    //! \brief m_guiController
    //!
    std::shared_ptr<sdl::GuiController> m_guiController;

    //!
    //! \brief m_isMusicMode
    //!
    bool m_isMusicMode;

    //!
    //! \brief m_mediaState
    //!
    int m_mediaState;

    //!
    //! \brief m_currentMediaPlaying
    //!
    MediaItemDataModel* m_currentMediaPlaying;

    //!
    //! \brief m_duration
    //!
    int m_duration;

    //!
    //! \brief m_playBackMode
    //!
    int m_playBackMode;

    //!
    //! \brief m_twMediaDataFolder
    //!
    QString m_twMediaDataFolder;

    //!
    //! \brief m_isMusicLoading
    //!
    bool m_isMusicLoading;

    //!
    //! \brief m_isVideoLoading
    //!
    bool m_isVideoLoading;

    //!
    //! \brief m_isMediaLoading
    //!
    bool m_isMediaLoading;

    //!
    //! \brief m_viewManager
    //!
    std::shared_ptr<ViewManager> m_viewManager;



signals:

    //!
    //! \brief mutedChanged
    //!
    void mutedChanged();

    //!
    //! \brief imageChanged
    //!
    void imageChanged();

    //!
    //! \brief sourceChanged
    //! \param source
    //!
    void sourceChanged(QString source);

    //!
    //! \brief directoryChanged
    //!
    void directoryChanged();

    //!
    //! \brief mediaStateChanged
    //!
    void mediaStateChanged();

    //!
    //! \brief positionChanged
    //!
    void positionChanged();

    //!
    //! \brief volumeChanged
    //!
    void volumeChanged();

    //!
    //! \brief currentIndexChanged
    //! \param data
    //!
    void currentIndexChanged(int data);

    //!
    //! \brief isMusicChanged
    //!
    void isMusicModeChanged();

    //!
    //! \brief currentMediaPlayingChanged
    //!
    void currentMediaPlayingChanged();

    //!
    //! \brief durationChanged
    //!
    void durationChanged();

    //!
    //! \brief playBackModeChanged
    //!
    void playBackModeChanged();

    //!
    //! \brief setVideoSurfaceChanged
    //!
    void videoSurfaceChanged();

    //!
    //! \brief twMediaDataFolderChanged
    //!
    void twMediaDataFolderChanged();

    //!
    //! \brief isMusicLoadingChanged
    //!
    void isMusicLoadingChanged();

    //!
    //! \brief isVideoLoadingChanged
    //!
    void isVideoLoadingChanged();

    //!
    //! \brief isMediaLoadingChanged
    //!
    void isMediaLoadingChanged();

};

#endif // MEDIAPLAYLISTMODEL_H
