// 2W includes
#include "include/MediaTrackingFolder.h"
#include "include/MediaDataReader.h"

MediaTrackingFolder::MediaTrackingFolder(bool isMusicMode, QObject *parent)
    : QObject(parent)
    , MUSIC_PATH{QStandardPaths::standardLocations(QStandardPaths::MusicLocation)[0]}
    , VIDEO_PATH{QStandardPaths::standardLocations(QStandardPaths::MoviesLocation)[0]}
    , m_mediaFolderWatcher(std::make_shared<QFileSystemWatcher>(nullptr))
    , m_jsonFolderWatcher(std::make_shared<QFileSystemWatcher>(nullptr))
    , m_isMusicMode(isMusicMode)
    , m_mediaReader(std::make_shared<MediaReader>(nullptr))

{
    // Create twData folder if not exist
    QDir tempDir(QDir::currentPath());
    while(!QDir(tempDir.path() + "/twData").exists()){
        tempDir.mkdir("twData");
    }
    tempDir.cd("twData");
    tempDir.mkdir("json");  //create folder to save json folders
    tempDir.mkdir("images"); //create folder to save thumbnail images
    m_twDataFolder = tempDir.path() + "/"; // Combine to path: ./twData/
    tempDir.cd("json");
    tempDir.mkdir("music"); //create folder to save json files to avoid re-trigger all json
    tempDir.mkdir("video"); //create folder to save json files to avoid re-trigger all json

    // NOTICE: Because of json file change too large -> We need to watcher the directories

    if(m_isMusicMode){
        m_currentDirectoryMedia.setPath(MUSIC_PATH);
        qDebug()<< "Set MUSIC path" << MUSIC_PATH;

        setRecurs(0);
        QDir dir(m_currentDirectoryMedia);
        m_dirPath = dir.absolutePath();
//        m_mediaFolderWatcher->addPath(MUSIC_PATH);
//        m_jsonFile.setFileName(m_twDataFolder+ "json/music/musicMetaData.json");
//        m_jsonFolderWatcher->addPath(m_twDataFolder+"json/music");
    } else {

        m_currentDirectoryMedia.setPath(VIDEO_PATH);
//        m_mediaFolderWatcher->addPath(VIDEO_PATH);
//        m_jsonFile.setFileName(m_twDataFolder+ "json/video/videoMetaData.json");
//        m_jsonFolderWatcher->addPath(m_twDataFolder+"json/video");

        //Set Recursive Folder
        setRecurs(0);
        QDir dir(m_currentDirectoryMedia);
        m_dirPath = dir.absolutePath();
        qDebug()<< "Set VIDEO path" << VIDEO_PATH;

    }

    QObject::connect(m_mediaFolderWatcher.get(),&QFileSystemWatcher::directoryChanged, this, [&](){
        refreshData();
    });
    QObject::connect(m_jsonFolderWatcher.get(),&QFileSystemWatcher::directoryChanged, this, [&](){
//        if (m_jsonFile.exists() || (m_jsonFile.size() > 0)) {
//            loadDataFromJson();
//        }
        loadDataFromTaglib();
    });
}

MediaTrackingFolder::~MediaTrackingFolder()
{
    disconnect(m_mediaFolderWatcher.get(),&QFileSystemWatcher::directoryChanged, this, nullptr);
    disconnect(m_jsonFolderWatcher.get(),&QFileSystemWatcher::directoryChanged, this, nullptr);
}

void MediaTrackingFolder::startLoadMetaData()
{
    if(isFolderModifies()){
        qDebug()<<"Data will be refresh due to folder had just modified/created";
        refreshData();
    } else {
//        qDebug()<<"Data will be loaded from JSON file: " << m_jsonFile.fileName();
//        loadDataFromJson();
        qDebug()<<"Data will be loaded by Taglib: ";

        loadDataFromTaglib();
    };
}

QString MediaTrackingFolder::getTWDataFolder() const
{
    return m_twDataFolder;
}

void MediaTrackingFolder::refreshData()
{
    // Inform data is going to be RELOADING!!!
    emit mediaDataReloading();

    // Clear model to inform data changing -> Loading screen will be displayed
    for (auto iter : m_mediaDataModelList)
    {
        if(iter != nullptr)
            delete iter;
    }
    m_mediaDataModelList.clear();
    m_listMediaContent.clear();
    emit mediaDataLoaded();

    // Reloading
    loadMediaFilesFromFolder();

    // Generate Media Metadata by Taglib

//    invokeGenerateMediaMetadataScript();
    invokeGenerateMediaMetadataByTaglib();
    loadDataFromTaglib();

}
QList<QUrl> MediaTrackingFolder::getListMediaContent() const
{
    return m_listMediaContent;
}

void MediaTrackingFolder::loadMediaFilesFromFolder()
{
    // Load all medias from folder
    if (m_isMusicMode){
        setMediaPlaylistDir(m_currentDirectoryMedia.entryList(QStringList()
                                                              << "*.mp3" << "*.MP3"
                                                              << "*.aac" << "*.AAC"
                                                              << "*.m4a" << "*.M4A"
                                                              << "*.wav" << "*.WAV"
                                                              << "*.wma" << "*.WMA"
                                                              << "*.flac" << "*.FLAC"
                                                              ,QDir::Files));
    }
    else {
        setMediaPlaylistDir(m_currentDirectoryMedia.entryList(QStringList()
                                                              << "*.mp4" << "*.MP4"
                                                              << "*.wmv" << "*.WMV"
                                                              << "*.avi" << "*.AVI"
                                                              << "*.ogg" << "*.MGG"
                                                              << "*.ogv" << "*.OGV"
                                                              << "*.mkv" << "*.MKV"
                                                              << "*.mov" << "*.MOV"
                                                              ,QDir::Files));
    }

    m_listMediaContent.clear();
    for(QString& media : m_mediaPlaylistDir)
    {
        m_listMediaContent.push_back(QUrl::fromLocalFile(m_currentDirectoryMedia.path() + "/" + media));
        qDebug() << QUrl::fromLocalFile(m_currentDirectoryMedia.path() + "/" + media);
        qDebug() << m_listMediaContent;

    }

}

bool MediaTrackingFolder::isFolderModifies()
{
    bool isModified = false;
    QFileInfo mediaFolderInfo(m_currentDirectoryMedia.path());
    QFileInfo mediaJson(m_jsonFile.fileName());

    qDebug() << "mediaFolderInfo " << mediaFolderInfo;
    qDebug() << "mediaJson " << mediaJson;

    if ((mediaFolderInfo.lastModified() > mediaJson.lastModified()) || (mediaJson.size() == 0)){
        isModified = true;
    } else {
        isModified = false;
    }
    return isModified;
}

void MediaTrackingFolder::loadDataFromJson()
{
    if(m_jsonFile.open( QIODevice::ReadOnly )){
        QByteArray jsonData = m_jsonFile.readAll();
        m_jsonFile.close();

        QJsonDocument saveJsonData = QJsonDocument::fromJson(jsonData);

        auto jsonRootObj = saveJsonData.array();

        for (auto iter : m_mediaDataModelList)
        {
            if(iter != nullptr)
                delete iter;
        }
        m_mediaDataModelList.clear();
        m_listMediaContent.clear();

        for(int i = 0; i < jsonRootObj.count();i++){
            auto jsonMediaObject = jsonRootObj[i].toObject();

            QString link =(jsonMediaObject["link"].toString());

            // To add list media to playlist
            m_listMediaContent.push_back(QUrl::fromLocalFile(link));
            // To add list media to data model
            MediaItemDataModel* tempData = new MediaItemDataModel();
            tempData->setMediaDir(link);
            tempData->setMediaFileName(jsonMediaObject["fileName"].toString());
            tempData->setMediaTitle(jsonMediaObject["title"].toString());
            tempData->setMediaSinger(jsonMediaObject["singer"].toString());
            tempData->setMediaDuration(jsonMediaObject["duration"].toInt());
            m_mediaDataModelList.push_back(tempData);
        }
        m_jsonFile.close();
        emit mediaDataLoaded();
    }
    else{
        qWarning()<< "Load file errorrr!";
    }
    m_jsonFile.close();
}

void MediaTrackingFolder::loadDataFromTaglib()
{
        for (auto iter : m_mediaDataModelList)
        {
            if(iter != nullptr)
                delete iter;
        }
        m_mediaDataModelList.clear();
        m_listMediaContent.clear();

        QDir dir(m_currentDirectoryMedia);

        std::vector metaDataList =  m_mediaReader->getMediaData();

        for (int64_t i=0 ; i<metaDataList.size(); i++){
            m_mediaReader->setMediaIndex(i);

            QString m_title= "";
            if (m_mediaReader->title() == ""){
            qDebug() << "Music Title"<< m_mediaReader->fileName().remove(".mp3");
            m_title = m_mediaReader->fileName().remove(".mp3");
            }else{
            qDebug() << "Music Title"<< m_mediaReader->title();
            m_title = m_mediaReader->title();
            }

            QString link =(m_mediaReader->filePath()+ "/" + m_mediaReader->fileName());          
            qDebug() << link;

            // To add list media to playlist
            m_listMediaContent.push_back(QUrl::fromLocalFile(link));
            // To add list media to data model
            MediaItemDataModel* tempData = new MediaItemDataModel();
            tempData->setMediaDir(link);
            tempData->setMediaFileName(m_mediaReader->fileName());
            tempData->setMediaTitle(m_title);
            tempData->setMediaSinger(m_mediaReader->artist());
            tempData->setMediaDuration((m_mediaReader->duration()).toInt());
            m_mediaDataModelList.push_back(tempData);
        }

        emit mediaDataLoaded();

        qDebug() << "Load data by Taglib success";

}


void MediaTrackingFolder::invokeGenerateMediaMetadataScript()
{
    QDir scriptGenerateMetadataFileDir{CURRENT_PROJECT_DIR"/assets/script/loadMetaData.sh"};
    m_loadDataProcess->startDetached("/bin/bash", QStringList() << scriptGenerateMetadataFileDir.path()
                                     << m_currentDirectoryMedia.path()
                                     << (m_jsonFile.fileName())
                                     << (m_isMusicMode ? "music" : "video"));

    if(!m_isMusicMode){
        QDir scriptGenerateThumbnailFileDir{CURRENT_PROJECT_DIR"/assets/script/genVideoThumnail.sh"};
        m_loadDataProcess->startDetached("/bin/bash", QStringList() << scriptGenerateThumbnailFileDir.path()
                                         << m_currentDirectoryMedia.path()
                                         << (m_twDataFolder + "images/"));
    }
}
void MediaTrackingFolder::invokeGenerateMediaMetadataByTaglib(){

    QDir dir(m_currentDirectoryMedia);
    qDebug() << "Generate metadata";
    m_dirPath = dir.absolutePath();
    qDebug() <<"Current directory "<< m_dirPath;
    m_recurs = getRecurs();
    m_mediaReader->readMusic(m_recurs, m_dirPath);
    if(!m_isMusicMode){
         m_mediaReader->readVideo(m_recurs, m_dirPath);
    }
    qDebug() <<"invoke Generate MediaMetadata By Taglib";

}

int MediaTrackingFolder::getRecurs() const {
    return m_recurs;
}

void MediaTrackingFolder::setRecurs(int value) {
    m_recurs = value;
}

QStringList MediaTrackingFolder::mediaPlaylistDir() const
{
    return m_mediaPlaylistDir;
}

void MediaTrackingFolder::setMediaPlaylistDir(const QStringList &newMediaPlaylistDir)
{
    if (m_mediaPlaylistDir == newMediaPlaylistDir)
        return;
    m_mediaPlaylistDir = newMediaPlaylistDir;
    emit mediaPlaylistDirChanged();
}

QList<MediaItemDataModel*> MediaTrackingFolder::getMediaDataModelList() const
{
    return m_mediaDataModelList;
}
