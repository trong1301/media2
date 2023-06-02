// 2W includes
#include "include/MediaItemDataModel.h"

MediaItemDataModel::MediaItemDataModel(QObject *parent)
    : QObject{parent}
    , m_mediaDir("")
    , m_mediaFileName("Unknown")
    , m_mediaTitle("Unknown")
    , m_mediaSinger("Unknown")
    , m_mediaDuration(0)
{

}

QUrl MediaItemDataModel::mediaDir() const
{
    return m_mediaDir;
}

void MediaItemDataModel::setMediaDir(const QUrl &newMediaDir)
{
    if (m_mediaDir == newMediaDir)
        return;
    m_mediaDir = newMediaDir;
    emit mediaDirChanged();
}

QString MediaItemDataModel::mediaFileName() const
{
    return m_mediaFileName;
}

void MediaItemDataModel::setMediaFileName(const QString &newMediaFileName)
{
    if (m_mediaFileName == newMediaFileName)
        return;
    m_mediaFileName = newMediaFileName;
    emit mediaFileNameChanged();
}

QString MediaItemDataModel::mediaTitle() const
{
    return m_mediaTitle;
}

void MediaItemDataModel::setMediaTitle(const QString &newMediaTitle)
{
    if (m_mediaTitle == newMediaTitle)
        return;
    m_mediaTitle = newMediaTitle;
    emit mediaTitleChanged();
}

QString MediaItemDataModel::mediaSinger() const
{
    return m_mediaSinger;
}

void MediaItemDataModel::setMediaSinger(const QString &newMediaSinger)
{
    if (m_mediaSinger == newMediaSinger)
        return;
    m_mediaSinger = newMediaSinger;
    emit mediaSingerChanged();
}

int MediaItemDataModel::mediaDuration() const
{
    return m_mediaDuration;
}

void MediaItemDataModel::setMediaDuration(int newMediaDuration)
{
    if (m_mediaDuration == newMediaDuration)
        return;
    m_mediaDuration = newMediaDuration;
    emit mediaDurationChanged();
}
