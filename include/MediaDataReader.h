#ifndef MEDIA_READER_H
#define MEDIA_READER_H

#include <QtCore>
#include <QObject>
#include <QDate>
#include <QQueue>
#include <QFileInfoList>
#include <QImage>
#include <vector>
#include <tag.h>
#include <fileref.h>
#include <iterator>
#include "mpeg/mpegfile.h"
#include <id3v2tag.h>
#include "frames/unsynchronizedlyricsframe.h"

#if defined(Q_OS_WIN)
    #define OS 1
#elif defined(Q_OS_MAC)
    #define OS 2
#elif defined(Q_OS_LINUX)
    #define OS 3
#endif

using namespace TagLib;

class MediaReader : public QObject {
    Q_OBJECT
public:
    MediaReader(QObject* parent = 0);
    Q_PROPERTY(QString genre READ genre)
    Q_PROPERTY(QString filePath READ filePath)
    Q_PROPERTY(QString fileName READ fileName)
    Q_PROPERTY(QString artist READ artist)
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString album READ album)
    Q_PROPERTY(QString year READ year)
    Q_PROPERTY(QString duration READ duration)
    Q_PROPERTY(QString trackNumber READ trackNumber)
    Q_PROPERTY(QImage image READ image)
    Q_PROPERTY(bool imgLoaded READ imgLoaded)

    struct MediaData {
        FileRef fileRef;
        ID3v2::UnsynchronizedLyricsFrame *frame;
        QString genre;
        QString filePath;
        QString fileName;
        QString artist;
        QString title;
        QString album;
        QString year;
        QString duration;
        QString absolutePath;
        QString trackNumber;
        QString lyrics;
        QImage  img;
        ByteVector data;
        bool imgLoaded;
    };

    QString genre() const;
    QString filePath() const;
    QString fileName() const;
    QString artist() const;
    QString title() const;
    QString album() const;
    QString year() const;
    QString duration() const;
    QString trackNumber() const;
    QImage  image() const;

    bool imgLoaded() const;
    
    void setMediaData(QFileInfoList);

    std::vector<MediaData> getMediaData(){
    return m_mediaData;
}

signals:

    void setMusicList(QStringList list);
    void sendImage(QImage img);
    void errorInvalidImage(QString msg);

public slots:
    void setMediaIndex(int);
    void readMusic(int recurs, QString = "");
    void readVideo(int recurs, QString = "");
//    void setImage(QString);
//    void saveImage(QString);
    void saveMedia(QString, QString, QString, QString,
                   QString, QString, QString);

private:
    int m_mediaIndex = 0;
    int m_sortedValue = 0;

    double m_imageSize = 0;

    bool m_sort = true;

    std::vector<MediaData> m_mediaData;

    MediaData m_lastMedia;

    QString m_dirPath;

    void getImg(QString);

    bool checkSuffix(QString, QString);
    QFileInfoList recursRead(QString);

};

#endif
