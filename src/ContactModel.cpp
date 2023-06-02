#include "include/ContactModel.h"
#include <QDebug>

ContactModel::ContactModel(QObject* parent, std::shared_ptr<PhoneController> phoneCtrl)
    : QAbstractListModel(parent)
    , m_phoneController(phoneCtrl)
{
    connect(m_phoneController.get(), &PhoneController::onContactDataChanged, this, [&](){
        setContactList(m_phoneController->getPhoneDataModel()->getContactDataAsQListContactItemModel());
    });
}

ContactModel::~ContactModel()
{
    disconnect(m_phoneController.get(), &PhoneController::onContactDataChanged, this, nullptr);
}

int ContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mContactItems.size();
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mContactItems.count())
        return QVariant();

    //The index is valid
    ContactItemModel * mContactItemModel = mContactItems[index.row()];
    if( role == ContactNameRole)
        return mContactItemModel->contactName();
    if( role == ContactImageRole)
        return mContactItemModel->contactImage();
    if( role == ContactNumberRole)
        return mContactItemModel->contactNumber();
    return QVariant();
}

Qt::ItemFlags ContactModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ContactModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ContactNameRole] = "contactName";
    roles[ContactImageRole] = "contactImage";
    roles[ContactNumberRole] = "contactNumber";

    return roles;
}

void ContactModel::addContact(ContactItemModel *contactItem)
{
    const int index = mContactItems.size();
    beginInsertRows(QModelIndex(),index, index);
    mContactItems.append(contactItem);
    endInsertRows();
}

void ContactModel::setContactList(QList<ContactItemModel *> list)
{
    beginResetModel();
    mContactItems = list;
    endResetModel();
}
