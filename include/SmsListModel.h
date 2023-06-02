#ifndef SmsListModel_H
#define SmsListModel_H

//Qt include
#include <QAbstractListModel>

//2W include
#include "GuiController.h"
#include "Smscontent.h"
#include "MagicNumbers.h"
#include "PhoneController.h"

class SmsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SmsListModel(QObject* parent = nullptr, std::shared_ptr<PhoneController> phoneCtrl = nullptr);
    ~SmsListModel() override;
    enum SmsRole {
        addressRole = Qt::UserRole,
        bodyRole,
        dateRole,
        readRole,
        typeRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    void addMessage(SmsContent* smsContent);
    void setMessageList(QList<SmsContent*> list);

private:
    //!
    //! \brief m_smsList
    //!
    QList<SmsContent*>m_smsList;

    //!
    //! \brief m_phoneController
    //!
    std::shared_ptr<PhoneController> m_phoneController;
};

#endif // SmsListModel_H
