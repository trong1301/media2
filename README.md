# media2

MediaTrackingFolder Class:

IF media mode change between Music and Video 
  THEN dicrectory change and Data will be refresh due to folder had just modified/created:
     refreshData() will be inwoke
ELSE loadDataFromTaglib() will be inwoke

IN refreshData() funtion:
   Clear model to inform data changing -> Loading screen will be displayed
      m_mediaDataModelList.clear();
      m_listMediaContent.clear();
   Reloading files from folder:
      loadMediaFilesFromFolder();
   Generate Media Metadata by Taglib:
      invokeGenerateMediaMetadataByTaglib();
   Load Media Metadata:
      loadDataFromTaglib();
     
IN loadDataFromTaglib() funtion:
    getMediaData() be invoke from class THEN save metadata into metaDataList vector
    Add list of media to playlist m_listMediaContent
    Add list of mediadata to data model list m_mediaDataModelList

IN invokeGenerateMediaMetadataByTaglib() funtion:
