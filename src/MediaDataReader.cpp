// Taglib includes

#include "include/MediaDataReader.h"
#include <QImage>
#include <id3v2frame.h>
#include <frames/attachedpictureframe.h>
#include <id3v2tag.h>
#include <frames/unsynchronizedlyricsframe.h>
#include <mpeg/mpegfile.h>
#include <frames/attachedpictureframe.h>

MediaReader::MediaReader(QObject* parent) : QObject(parent) {

}

bool MediaReader::checkSuffix(QString str, QString suff) {
    short int sfx = suff.length();
    int len = str.length();

    for (int i = 1; i <= sfx; i++) {
        if (str[len - i] != suff[sfx - i]) {
            return false;
        }
    }
    return true;
}

void MediaReader::setMediaData(QFileInfoList list) {
    m_mediaData.clear();

    for (auto& i : list) {
        MediaData data;
        String filePath = i.filePath().toStdWString().c_str();
        FileRef file(filePath.toCString(1));
        if (file.isNull())
            continue;
        data.fileRef = file;
        data.filePath = i.absolutePath();
        data.fileName = i.fileName();
        data.album = QString::fromStdWString(file.tag()->album().toWString());
        data.genre = QString::fromStdWString(file.tag()->genre().toWString());
        data.artist = QString::fromStdWString(file.tag()->artist().toWString());
        data.title = QString::fromStdWString(file.tag()->title().toWString());
        data.trackNumber = QString::fromStdString(std::to_string(file.tag()->track()));
        data.year = QString::fromStdString(std::to_string(file.tag()->year()));
        data.duration = QString::fromStdString(std::to_string(file.audioProperties()->length()));

        data.absolutePath = i.absolutePath();

        MPEG::File f(filePath.toCString(1));
        ID3v2::FrameList frames = f.ID3v2Tag()->frameListMap()["USLT"];
        ID3v2::UnsynchronizedLyricsFrame *frame = NULL;

        if (!frames.isEmpty()) {
            frame = dynamic_cast<ID3v2::UnsynchronizedLyricsFrame *>(frames.front());
            if (frame) data.lyrics = QString::fromStdWString(frame->text().toWString());
            else data.lyrics = "";
        }

        TagLib::ID3v2::FrameList frameList = f.ID3v2Tag()->frameList("APIC");
        if (!frameList.isEmpty()) {
            TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
            QImage coverQImg;
            coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
            data.img = coverQImg.scaled(226, 226, Qt::KeepAspectRatio);
            data.imgLoaded = 1;
        } else {
            data.imgLoaded = 0;
        }
        m_mediaData.push_back(data);
    }
     qDebug() << "Media data setted";
}

void MediaReader::setMediaIndex(int index) {
    m_mediaIndex = index;
    m_lastMedia = m_mediaData[m_mediaIndex];
    qDebug() << "Media index setted";
}

QString MediaReader::genre() const {
    return m_lastMedia.genre;
}

QString MediaReader::filePath() const {
    return m_lastMedia.filePath;
}

QString MediaReader::fileName() const {
    return m_lastMedia.fileName;
}

QString MediaReader::artist() const {
    return m_lastMedia.artist;
}

QString MediaReader::title() const {
    return m_lastMedia.title;
}

QString MediaReader::album() const {
    return m_lastMedia.album;
}

QString MediaReader::year() const {
    return m_lastMedia.year;
}


QString MediaReader::duration() const {
    return m_lastMedia.duration;
}


QString MediaReader::trackNumber() const {
    return m_lastMedia.trackNumber;
}

QImage MediaReader::image() const {
    return m_lastMedia.img;
}

class ImageFile : public TagLib::File {
public:
    ImageFile(const wchar_t *file) : TagLib::File(FileName(file)) { }
    ImageFile(const char *file) : TagLib::File(file) { }

    TagLib::ByteVector data() {
        return readBlock(length());
    }
private:
    virtual TagLib::Tag *tag() const { return 0; }
    virtual TagLib::AudioProperties *MediaProperties() const { return 0; }
    virtual bool save() { return false; }
};

//void MediaReader::setImage(QString url) {
//    QString _path;

//    for (int i = OS == 1 ? 8 : 7; i < url.length(); ++i)
//        _path.push_back(url[i]);
//    QImage _img = QImage(_path).scaled(226, 226, Qt::KeepAspectRatio);
//    if (!_img.isNull()) {
//        m_lastMedia.img = QImage(_img);
//        m_lastMedia.imgLoaded = 1;

//        String fpath = _path.toStdWString().c_str();
//        ImageFile img(fpath.toCString(1));

//        m_lastMedia.data = img.data();
//        if (m_mediaData.size() != 0) {
//            m_mediaData[m_mediaIndex].imgLoaded = 1;
//            m_mediaData[m_mediaIndex].img = QImage(m_lastMedia.img);
//            m_mediaData[m_mediaIndex].data = m_lastMedia.data;
//        }
//    } else {
//        emit errorInvalidImage(_path);
//    }
//}

bool MediaReader::imgLoaded() const {
    return m_lastMedia.imgLoaded;
}

QFileInfoList MediaReader::recursRead(QString path) {
    QFileInfoList list;
    QFileInfoList dirsList;
    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::NoSymLinks);
    dirsList << dir.entryInfoList();
    for (auto& i : dirsList)
        list << recursRead(i.absoluteFilePath());
    QDir Medias(path);
    Medias.setNameFilters(QStringList() << "*.mp3"
                                 << "*.wav" << "*.flac"
                                 << "*.ogg" << "*.aiff"
                                 << "*.ape" << "*.ac3"
                                 << "*.amr" << "*.aud"
                                 << "*.iff" << "*.m3u"
                                 << "*.m3u8" << "*.m4a");
    list << Medias.entryInfoList();
    return list;
}

void MediaReader::readMusic(int recurs, QString dirPath) {
    if (dirPath == "")
        dirPath = m_dirPath;
    QDir dir(dirPath);
    QFileInfoList list;
    m_dirPath = dirPath;
    if (recurs) {
        list << recursRead(m_dirPath);
    }   
    else {
        dir.setNameFilters(QStringList() << "*.mp3"
                           << "*.wav" << "*.flac"
                           << "*.ogg" << "*.aiff"
                           << "*.ape" << "*.ac3"
                           << "*.amr" << "*.aud"
                           << "*.iff" << "*.m3u"
                           << "*.m3u8" << "*.m4a");
        list << dir.entryInfoList();
    }
    
    setMediaData(std::move(list));
    qDebug() << "Read metadata audio finish";
}

void MediaReader::readVideo(int recurs, QString dirPath) {
    if (dirPath == "")
        dirPath = m_dirPath;
    QDir dir(dirPath);
    QFileInfoList list;
    m_dirPath = dirPath;
    if (recurs) {
        list << recursRead(m_dirPath);
    }
    else {
        dir.setNameFilters(QStringList()
                           << "*.mp4" << "*.MP4"
                           << "*.wmv" << "*.WMV"
                           << "*.avi" << "*.AVI"
                           << "*.ogg" << "*.MGG"
                           << "*.ogv" << "*.OGV"
                           << "*.mkv" << "*.MKV"
                           << "*.mov" << "*.MOV");
        list << dir.entryInfoList();
    }

    setMediaData(std::move(list));
    qDebug() << "Read metadata audio finish";
}

void MediaReader::saveMedia(QString artist, QString title, QString album,
                            QString genre, QString year, QString number,
                            QString lyrics) {
    m_lastMedia.artist = artist;
    m_lastMedia.title = title;
    m_lastMedia.album = album;
    m_lastMedia.genre = genre;
    m_lastMedia.year = year;
    m_lastMedia.trackNumber = number;
    m_lastMedia.lyrics = lyrics;
    m_lastMedia.fileRef.tag()->setArtist(artist.toStdWString());
    m_lastMedia.fileRef.tag()->setTitle(title.toStdWString());
    m_lastMedia.fileRef.tag()->setAlbum(album.toStdWString());
    m_lastMedia.fileRef.tag()->setGenre(genre.toStdWString());
    m_lastMedia.fileRef.tag()->setYear(year.toUInt());
    m_lastMedia.fileRef.tag()->setTrack(number.toUInt());
    m_lastMedia.fileRef.save();

    String filePath = m_lastMedia.filePath.toStdWString() + "/" + m_lastMedia.fileName.toStdWString();
    MPEG::File f(filePath.toCString(1));
    ID3v2::UnsynchronizedLyricsFrame *frame = new ID3v2::UnsynchronizedLyricsFrame();

    if (!f.ID3v2Tag()->frameListMap()["USLT"].isEmpty())
        f.ID3v2Tag()->removeFrames(f.ID3v2Tag()->frameListMap()["USLT"].front()->frameID());
    frame->setText(lyrics.toStdWString());
    f.ID3v2Tag()->addFrame(frame);
    if (checkSuffix(m_lastMedia.fileName, ".mp3")) {
        if (!f.ID3v2Tag()->frameListMap()["APIC"].isEmpty())
            f.ID3v2Tag()->removeFrames(f.ID3v2Tag()->frameListMap()["APIC"].front()->frameID());
        ID3v2::AttachedPictureFrame *imgFrame = new ID3v2::AttachedPictureFrame();
        ByteVector byteImg;
        QByteArray arr;
        QBuffer buffer(&arr);

        buffer.open(QIODevice::WriteOnly);
        m_lastMedia.img.save(&buffer, "image/jpeg");
        byteImg.setData(arr);
        imgFrame->setMimeType("image/jpeg");
        imgFrame->setPicture(m_lastMedia.data);
        f.ID3v2Tag()->addFrame(imgFrame);
    }
    f.save();
    if (m_mediaData.size() > static_cast<unsigned int>(m_mediaIndex))
        m_mediaData[m_mediaIndex] = m_lastMedia;
}
