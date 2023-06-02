#include "include/CallLogListItemModel.h"
#include <QDebug>

CallLogListItemModel::CallLogListItemModel(QObject* parent, std::shared_ptr<PhoneController> phoneCtrl)
    : QAbstractListModel(parent)
    , m_phoneController(phoneCtrl)
{
    connect(m_phoneController.get(), &PhoneController::onCallLogChanged, this, [&](){
        setCallLogList(m_phoneController->getPhoneDataModel()->getCallLogDataAsQListCallLogItemModel());
    });
}

CallLogListItemModel::~CallLogListItemModel()
{
    disconnect(m_phoneController.get(), &PhoneController::onCallLogChanged, this, nullptr);
}

int CallLogListItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mCallLogItems.size();
}

QVariant CallLogListItemModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mCallLogItems.count())
        return QVariant();

    //The index is valid
    CallLogItemModel * mCallLogItemModel = mCallLogItems[index.row()];
    if( role == CallLogNameRole)
        return mCallLogItemModel->getCallLogName();
    if( role == CallLogNumberRole)
        return mCallLogItemModel->getCallLogNumber();
    if( role == CallLogDateRole)
        return mCallLogItemModel->getCallLogDate();
    if( role == CallLogDurationRole)
        return mCallLogItemModel->getCallLogDuration();
    if( role == CallLogTypeRole)
        return mCallLogItemModel->getCallLogType();
    return QVariant();
}

Qt::ItemFlags CallLogListItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> CallLogListItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CallLogNameRole] = "callLogName";
    roles[CallLogNumberRole] = "callLogNumber";
    roles[CallLogDateRole] = "callLogDate";
    roles[CallLogDurationRole] = "callLogDuration";
    roles[CallLogTypeRole] = "callLogType";

    return roles;
}

void CallLogListItemModel::addCallLog(CallLogItemModel *CallLogItem)
{
    const int index = mCallLogItems.size();
    beginInsertRows(QModelIndex(),index, index);
    mCallLogItems.append(CallLogItem);
    endInsertRows();
}

void CallLogListItemModel::setCallLogList(QList<CallLogItemModel *> list)
{
    beginResetModel();
    mCallLogItems = list;
    endResetModel();
}
