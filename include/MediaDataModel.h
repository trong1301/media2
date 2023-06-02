#ifndef MEDIADATAMODEL_H
#define MEDIADATAMODEL_H

// Qt includes
#include <QObject>
#include <QAbstractListModel>

// 2W includes
#include "include/MediaItemDataModel.h"

class MediaDataModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MediaDataModel(QObject* parent = nullptr);
    ~MediaDataModel() override;
    enum MediaRole {
        dirPathRole = Qt::UserRole,
        fileNameRole,
        titleRole,
        singerRole,
        durationRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    //!
    //! \brief addMediaDataModel
    //! \param mediaDataContent
    //!
    void addMediaDataModel(MediaItemDataModel* mediaDataContent);

    //!
    //! \brief setMediaDataModelList
    //! \param list
    //!
    void setMediaDataModelList(QList<MediaItemDataModel* > list);

    //!
    //! \brief getMediaDataModel
    //! \param index
    //! \return
    //!
    MediaItemDataModel* getMediaDataModel(const int index);
private:
    //!
    //! \brief m_mediaDataContentList
    //!
    QList<MediaItemDataModel* > m_mediaDataContentList;
};


#endif // MEDIADATAMODEL_H
