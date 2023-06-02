#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

// Qt include
#include <QAbstractListModel>
#include <QObject>

// 2W include
#include "ContactItem.h"
#include "PhoneController.h"

class ContactModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ContactRoles{
        ContactNameRole = Qt::UserRole + 1,
        ContactImageRole,
        ContactNumberRole
    };

    explicit ContactModel(QObject* parent = nullptr, std::shared_ptr<PhoneController> phoneCtrl = nullptr);
    ~ContactModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex& index) const;

    QHash<int, QByteArray> roleNames() const;

    void addContact(ContactItemModel *ContactItem);
    void setContactList(QList<ContactItemModel*>);

private:
    //!
    //! \brief mContactItems
    //!
    QList<ContactItemModel *> mContactItems;

    //!
    //! \brief m_phoneController
    //!
    std::shared_ptr<PhoneController> m_phoneController;
};

#endif // CONTACTMODEL_H
