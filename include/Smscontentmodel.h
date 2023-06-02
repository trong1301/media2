#ifndef SMSCONTENTMODEL_H
#define SMSCONTENTMODEL_H

//Qt include
#include <QAbstractListModel>

//2W include
#include "GuiController.h"
#include "Smscontent.h"
#include "MagicNumbers.h"
#include "PhoneController.h"

class SmsContentModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SmsContentModel(QObject* parent = nullptr, std::shared_ptr<PhoneController> phoneCtrl = nullptr);
    ~SmsContentModel() override;
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
    //! \brief m_smsContentList
    //!
    QList<SmsContent*>m_smsContentList;

    //!
    //! \brief m_phoneController
    //!
    std::shared_ptr<PhoneController> m_phoneController;
};

#endif // SMSCONTENTMODEL_H
