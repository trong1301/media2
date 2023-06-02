// C++ includes
#include <memory>

// 2W includes
#include "include/MediaDataModel.h"
#include "include/qmediaplaylist.h"

MediaDataModel::MediaDataModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

MediaDataModel::~MediaDataModel()
{
}

int MediaDataModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_mediaDataContentList.count();
}

QVariant MediaDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    MediaItemDataModel* mediaItem = m_mediaDataContentList.at(index.row());
    switch(role) {
    case dirPathRole:
        return mediaItem->mediaDir();
    case fileNameRole:
        return mediaItem->mediaFileName();
    case titleRole:
        return mediaItem->mediaTitle();
    case singerRole:
        return mediaItem->mediaSinger();
    case durationRole:
        return mediaItem->mediaDuration();
    }

    return QVariant();
}

QMediaPlaylist *MediaDataModel::playlist() const
{
    return m_playlist.data();
}


bool MediaDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()||role != MediaRole::dirPathRole
            ||role != MediaRole::fileNameRole
            ||role != MediaRole::titleRole
            ||role != MediaRole::singerRole
            ||role != MediaRole::durationRole)
        return false;
    MediaItemDataModel* item = m_mediaDataContentList.at(index.row());
    switch (role) {
    case dirPathRole:
        item->setMediaDir(value.toString());
        break;
    case fileNameRole:
        item->setMediaFileName(value.toString());
        break;
    case titleRole:
        item->setMediaTitle(value.toString());
        break;
    case singerRole:
        item->setMediaSinger(value.toString());
        break;
    case durationRole:
        item->setMediaDuration(value.toInt());
    default:
        break;
    }
    if (data(index,role) != value){
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags MediaDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> MediaDataModel::roleNames() const
{
    QHash <int, QByteArray> names;
    names[dirPathRole] = "mediaDirPath";
    names[fileNameRole] = "mediaFileName";
    names[titleRole] = "mediaTitle";
    names[singerRole] = "mediaSinger";
    names[durationRole] = "mediaDuration";
    return names;
}

void MediaDataModel::addMediaDataModel(MediaItemDataModel* mediaDataContent)
{
    const int index = m_mediaDataContentList.size();
    beginInsertRows(QModelIndex(), index, index);
    m_mediaDataContentList.append(mediaDataContent);
    endInsertRows();
}

void MediaDataModel::setMediaDataModelList(QList<MediaItemDataModel*> list)
{
    beginResetModel();
    m_mediaDataContentList = list;
    endResetModel();
}

MediaItemDataModel* MediaDataModel::getMediaDataModel(const int index)
{
    if(index > rowCount() || index < 0)
    {
        if(rowCount() > 0)
        {
            return m_mediaDataContentList.at(0);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return m_mediaDataContentList.at(index);
    }
}
