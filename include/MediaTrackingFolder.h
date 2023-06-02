#ifndef MEDIATRACKINGFOLDER_H
#define MEDIATRACKINGFOLDER_H

// Qt includes
#include <QUrl>
#include <QDir>
#include <QDebug>
#include <QObject>
#include <QProcess>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QFileSystemWatcher>

// 2W includes
#include "MediaItemDataModel.h"

// Taglib include
#include "include/MediaDataReader.h"
#include <tag.h>
#include <fileref.h>
#include <QDir>
#include <QList>
#include <string>
#include <QFile>

class MediaTrackingFolder : public QObject
{
    Q_OBJECT
public:
    explicit MediaTrackingFolder(bool isMusicMode, QObject *parent = nullptr);

    ~MediaTrackingFolder();

    //!
    //! \brief loadMediaFilesFromFolder
    //!
    void loadMediaFilesFromFolder();

    //!
    //! \brief isFolderModifies
    //! \return
    //!
    bool isFolderModifies();

    //!
    //! \brief loadDataFromJson
    //!
    void loadDataFromJson();

    //!
    //! \brief loadDataFromTaglib
    //!
    void loadDataFromTaglib();

    //!
    //! \brief loadMetaData
    //!
    void loadMetaData();

    //!
    //! \brief invokeGenerateMediaMetadataScript
    //!
    void invokeGenerateMediaMetadataScript();

    //!
    //! \brief invokeGenerateMediaMetadataByTaglib
    //!
    void invokeGenerateMediaMetadataByTaglib();

    //!
    //! \brief writeDataToJson
    //!
    void writeDataToJson();

    //!
    //! \brief refreshData
    //!
    void refreshData();

    //!
    //! \brief getListMediaContent
    //! \return
    //!
    QList<QUrl> getListMediaContent() const;

    //!
    //! \brief mediaPlaylistDir
    //! \return
    //!
    QStringList mediaPlaylistDir() const;

    //!
    //! \brief setMediaPlaylistDir
    //! \param newMediaPlaylistDir
    //!
    void setMediaPlaylistDir(const QStringList &newMediaPlaylistDir);

    //!
    //! \brief getMediaDataModelList
    //! \return
    //!
    QList<MediaItemDataModel*> getMediaDataModelList() const;

    //!
    //! \brief startLoadMetaData
    //!
    void startLoadMetaData();

    //!
    //! \brief getTWDatader
    //! \return
    //!
    QString getTWDataFolder() const;

    //!
    //! \brief getRecurs
    //! \return
    //!
    int getRecurs() const;

    //!
    //! \brief setRecurs
    //! \return
    //!
    void setRecurs(int value);

private:
    //!
    //! \brief MUSIC_PATH
    //!
    const QString MUSIC_PATH;

    //!
    //! \brief VIDEO_PATH
    //!
    const QString VIDEO_PATH;

    //!
    //! \brief m_listMediaContent
    //!
    QList<QUrl> m_listMediaContent;

    //!
    //! \brief m_mediaFolderWatcher
    //!
    std::shared_ptr<QFileSystemWatcher> m_mediaFolderWatcher;

    //!
    //! \brief m_jsonFolderWatcher
    //!
    std::shared_ptr<QFileSystemWatcher> m_jsonFolderWatcher;

    //!
    //! \brief m_loadDataProcess
    //!
    std::shared_ptr<QProcess> m_loadDataProcess;

    //!
    //! \brief m_mediaReader
    //!
    std::shared_ptr<MediaReader> m_mediaReader;

    //!
    //! \brief m_recurs
    //!
    int m_recurs = 0;

    //!
    //! \brief m_dirPath
    //!
    QString m_dirPath = "";

    //!
    //! \brief m_jsonFile
    //!
    QFile m_jsonFile;

    //!
    //! \brief m_isMusicMode
    //!
    bool m_isMusicMode;

    //!
    //! \brief m_twDataFolder
    //!
    QString m_twDataFolder;

    //!
    //! \brief m_mediaPlaylistDir
    //!
    QStringList m_mediaPlaylistDir;

    //!
    //! \brief m_currentDirectoryMedia
    //!
    QDir m_currentDirectoryMedia;

    //!
    //! \brief m_mediaDataModelList
    //!
    QList<MediaItemDataModel* > m_mediaDataModelList;

signals:
    void mediaDataReloading();
    void mediaDataLoaded();
    void mediaPlaylistDirChanged();

};

#endif // MEDIATRACKINGFOLDER_H
