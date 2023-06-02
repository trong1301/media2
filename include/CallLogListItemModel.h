#ifndef CALLLOGLISTITEMMODEL_H
#define CALLLOGLISTITEMMODEL_H

// Qt include
#include <QAbstractListModel>
#include <QObject>

// 2W include
#include "CallLogItemModel.h"
#include "PhoneController.h"

class CallLogListItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CallLogRoles{
        CallLogNameRole = Qt::UserRole + 1,
        CallLogNumberRole,
        CallLogDateRole,
        CallLogDurationRole,
        CallLogTypeRole
    };

    explicit CallLogListItemModel(QObject* parent = nullptr, std::shared_ptr<PhoneController> phoneCtrl = nullptr);
    ~CallLogListItemModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex& index) const;

    QHash<int, QByteArray> roleNames() const;

    void addCallLog(CallLogItemModel *CallLogItem);
    void setCallLogList(QList<CallLogItemModel*> list);

private:
    //!
    //! \brief mCallLogItems
    //!
    QList<CallLogItemModel *> mCallLogItems;

    //!
    //! \brief m_phoneController
    //!
    std::shared_ptr<PhoneController> m_phoneController;

};

#endif // CALLLOGLISTITEMMODEL_H

