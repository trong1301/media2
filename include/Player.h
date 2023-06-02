/***********************************************
*THIS CLASS IS USED MANAGE MEDIA PLAYER & AUDIO OBJECT
************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QImage>

// Video player include
#include <QPointer>
#include <QVideoSink>
#include <QTimer>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMediaPlayer::PlaybackState state READ getState WRITE setState NOTIFY stateChanged)

    Q_PROPERTY(qint64 volume READ volume WRITE setVolume NOTIFY volumeChanged)

    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    
    //A property for displaying the duration of the media.
   
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)

    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
    
    Q_PROPERTY(bool repeat READ repeat WRITE setRepeat NOTIFY repeatChanged)

    Q_PROPERTY(QImage image MEMBER mImage READ image NOTIFY imageChanged)

    // Video player
    Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)

public:
    explicit Player(QObject *parent = nullptr);

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    Q_INVOKABLE void mute();
    Q_INVOKABLE void unmute();

    Q_INVOKABLE bool isPlaying();
    Q_INVOKABLE bool isPaused();
    Q_INVOKABLE bool isStopped();

    qint64 duration() const;

    qint64 position() const;
    void setPosition(const qint64);

    QMediaPlayer::PlaybackState getState();
    void setState(const QMediaPlayer::PlaybackState);

    int getintState();


    qint64 volume() const;
    void setVolume(const qint64 volume);

    bool muted() const;
    void setMuted(const bool muted);

    bool repeat() const;
    void setRepeat(const bool repeat);
    void setSource(QString source);

    QString errorText() const;

    const QImage &image() const;
    void setImage(const QImage newimage);


    QVideoSink *videoSink() const;
    void setVideoSink(QVideoSink *newVideoSink);
    void start();

signals:
    void positionChanged(qint64);
    void durationChanged(qint64);
    void endOfSong();
    void stateChanged();
    void volumeChanged();
    void mutedChanged();
    void repeatChanged();

    void imageChanged();
    void videoSinkChanged();
public slots:
    void onMediaStatusChanged();
    void onErrorChanged(QMediaPlayer::Error);
    void onSourceChanged(QString source);

private:
    QMediaPlayer mMPlayer;
    QAudioOutput *mAudio;

    QString mErrorText;
    QImage mImage;

    QPointer<QVideoSink> m_videoSink;
    void handleTimeout();
    QTimer m_timer;
};

#endif // PLAYER_H
