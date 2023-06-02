#include "include/Smscontentmodel.h"
#include "include/Smscontent.h"
#include <QDebug>


SmsContentModel::SmsContentModel(QObject* parent, std::shared_ptr<PhoneController> phoneCtrl)
    : QAbstractListModel(parent)
    , m_phoneController(phoneCtrl)
{
    connect(m_phoneController.get(), &PhoneController::smsItemSelectedChanged, this, [&](){
        qDebug() << "Set new sms content";
        setMessageList(m_phoneController->getPhoneDataModel()->getItemSmsContentDataAsQListSmSContentModel());
    });
}

SmsContentModel::~SmsContentModel()
{
    disconnect(m_phoneController.get(), &PhoneController::smsItemSelectedChanged, this, nullptr);
}

int SmsContentModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_smsContentList.count();
}

QVariant SmsContentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    SmsContent *smscontent = m_smsContentList.at(index.row());
    switch(role) {
    case addressRole:
        return smscontent->address();
    case bodyRole:
        return smscontent->body();
    case dateRole:
        return smscontent->date();
    case readRole:
        return smscontent->read();
    case typeRole:
        return smscontent->type();
    }

    return QVariant();
}

bool SmsContentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()||role != SmsRole::addressRole
            ||role != SmsRole::bodyRole
            ||role != SmsRole::dateRole
            ||role != SmsRole::readRole
            ||role != SmsRole::typeRole)
        return false;
    SmsContent *item = m_smsContentList.at(index.row());
    switch (role) {
    case addressRole:
        item->setAddress(value.toString());
        break;
    case bodyRole:
        item->setBody(value.toString());
        break;
    case dateRole:
        item->setDate(value.toString());
        break;
    case readRole:
        item->setRead(value.toUInt());
        break;
    case typeRole:
        item->setType(value.toUInt());
    default:
        break;
    }
    if (data(index,role) != value){
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags SmsContentModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> SmsContentModel::roleNames() const
{
    QHash <int, QByteArray> names;
    names[addressRole] = "address";
    names[bodyRole] = "body";
    names[dateRole] = "date";
    names[readRole] = "read";
    names[typeRole] = "type";
    return names;
}

void SmsContentModel::addMessage(SmsContent *smsContent)
{
    const int index = m_smsContentList.size();
    beginInsertRows(QModelIndex(), index, index);
    m_smsContentList.append(smsContent);
    endInsertRows();
}

void SmsContentModel::setMessageList(QList<SmsContent *> list)
{
    beginResetModel();
    m_smsContentList = list;
    endResetModel();
}
