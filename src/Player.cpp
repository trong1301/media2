#include "include/Player.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QFileDialog>
#include <QTime>

// Taglib include
#include <tag.h>
#include <cstring>
#include <iostream>
#include <fileref.h>

// Video player include
#include <QImage>
#include <QPainter>
#include <QSize>
#include <QVideoFrame>
#include <QRandomGenerator>
#include <QDateTime>

using namespace TagLib;

Player::Player(QObject *parent)
    : QObject{parent}
{
    connect(&(this->mMPlayer), SIGNAL(positionChanged(qint64)),
            this, SIGNAL(positionChanged(qint64)));

    connect(&(this->mMPlayer), SIGNAL(durationChanged(qint64)),
            this, SIGNAL(durationChanged(qint64)));

    connect(&(this->mMPlayer), SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this, SLOT(setState()));

    connect(&(this->mMPlayer), SIGNAL(videoSinkChanged()),
            this, SLOT(videoSurfaceChanged()));


    mAudio = new QAudioOutput;
    mAudio->setVolume(0.5);
    mMPlayer.setAudioOutput(mAudio);

// Video player
    m_timer.setInterval(500);
    connect(&m_timer, &QTimer::timeout, this, &Player::handleTimeout);
}

//Set media player to play mode
void Player::play()
{
    if (!mMPlayer.source().isEmpty())
    {
        mMPlayer.play();
        emit stateChanged();
    }
}

//Set media player to pause mode
void Player::pause()
{
    if (mMPlayer.playbackState() == QMediaPlayer::PlayingState)
    {
        mMPlayer.pause();
        emit stateChanged();
    }
}

//Set media player to stop mode
void Player::stop()
{
    mMPlayer.stop();
    emit stateChanged();
}

//Set mute to audio
void Player::mute()
{
    setMuted(true);
}

//Set unmute to audio
void Player::unmute()
{
    setMuted(false);
}

bool Player::isPlaying()
{
    return (mMPlayer.playbackState() == QMediaPlayer::PlayingState);
}

bool Player::isPaused()
{
    return (mMPlayer.playbackState() == QMediaPlayer::PausedState);
}

bool Player::isStopped()
{
    return (mMPlayer.playbackState() == QMediaPlayer::StoppedState);
}

qint64 Player::position() const
{
    return mMPlayer.position();
}

void Player::setPosition(const qint64 position)
{
    if (position != mMPlayer.position())
    {

        if (position > mMPlayer.duration()) mMPlayer.setPosition(mMPlayer.duration());
        else
        {
            if (position < 0) mMPlayer.setPosition(0);
            else mMPlayer.setPosition(position);
        }
    }
}

QMediaPlayer::PlaybackState Player::getState()
{
    return mMPlayer.playbackState();
}


void Player::setState(const QMediaPlayer::PlaybackState state)
{
    if (state != mMPlayer.playbackState())
    {
        switch(state)
        {
        case 0:
            mMPlayer.stop();
            break;
        case 1:
            mMPlayer.play();
            break;
        case 2:
            mMPlayer.stop();
            break;
        default:
            break;
        }
        emit stateChanged();
    }
}

qint64 Player::volume() const
{
    qint64 a = int((mAudio->volume())*100);
    return a;
}

void Player::setVolume(const qint64 volume)
{
    if (float(volume/100) != mAudio->volume())
    {
        if (float(volume/100) > 1) mAudio->setVolume(1);
        else
        {
            if (float(volume/100) < 0) mAudio->setVolume(0);
            else mAudio->setVolume(float(volume/100));
        }
        emit volumeChanged();
    }
}

bool Player::muted() const
{
    return mAudio->isMuted();
}

void Player::setMuted(const bool muted)
{
    mAudio->setMuted(muted);
    emit mutedChanged();
}

bool Player::repeat() const
{
    return (mMPlayer.loops() < 0);
}

void Player::setRepeat(const bool repeat)
{
    if (repeat) {
        mMPlayer.setLoops(QMediaPlayer::Infinite);
    } else {
        mMPlayer.setLoops(QMediaPlayer::Once);
    }
    emit repeatChanged();
    qDebug() << mMPlayer.loops();
}

void Player::setSource(QString source)
{
    mMPlayer.setSource(source);
    if (source == "") setImage(QImage(":/image/main.jpg"));
}

qint64 Player::duration() const
{
    return mMPlayer.duration();
}

void Player::onMediaStatusChanged()
{
    switch(mMPlayer.mediaStatus())
    {
    case QMediaPlayer::EndOfMedia:
    {
        emit endOfSong();
    }
        break;
    case QMediaPlayer::LoadedMedia:
    {
//        QMediaMetaData songcontent = mMPlayer.metaData();
//        setImage(songcontent[QMediaMetaData::ThumbnailImage].value<QImage>());
//        emit imageChanged();
    }
        break;
    default:
        break;
    }
}

void Player::onErrorChanged(QMediaPlayer::Error error)
{

}

void Player::onSourceChanged(QString source)
{
    setSource(source);
}

const QImage &Player::image() const
{
    return mImage;
}

void Player::setImage(const QImage newimage)
{
    mImage = newimage;
    emit imageChanged();
}


// Video Player

QVideoSink *Player::videoSink() const
{
    return m_videoSink.get();
}

void Player::setVideoSink(QVideoSink *newVideoSink)
{
    if (m_videoSink == newVideoSink)
        return;
    m_videoSink = newVideoSink;
    emit videoSinkChanged();
}

void Player::start()
{
    m_timer.start();
    handleTimeout();
}

void Player::handleTimeout()
{
    if(!m_videoSink)
        return;
    QVideoFrame video_frame(QVideoFrameFormat(QSize(64, 48),QVideoFrameFormat::Format_BGRA8888));
    if(!video_frame.isValid() || !video_frame.map(QVideoFrame::WriteOnly)){
        qWarning() << "QVideoFrame is not valid or not writable";
        return;
    }
    QImage::Format image_format = QVideoFrameFormat::imageFormatFromPixelFormat(video_frame.pixelFormat());
    if(image_format == QImage::Format_Invalid){
        qWarning() << "It is not possible to obtain image format from the pixel format of the videoframe";
        return;
    }
    int plane = 0;
    QImage image(video_frame.bits(plane), video_frame.width(),video_frame.height(), image_format);
    image.fill(QColor::fromRgb(QRandomGenerator::global()->generate()));
    QPainter painter(&image);
    painter.drawText(image.rect(), Qt::AlignCenter, QDateTime::currentDateTime().toString());
    painter.end();

    video_frame.unmap();
    m_videoSink->setVideoFrame(video_frame);
}
