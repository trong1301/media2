#ifndef GUIPHONEDATAMODEL_H
#define GUIPHONEDATAMODEL_H

// Qt includes
#include <QObject>
#include <QVector>

// 2W includes
#include "Smscontent.h"
#include "ContactItem.h"
#include "CallLogItemModel.h"

// SDL includes
#include "sdl_libs/include/SDLTypes.h"

class GuiPhoneDataModel : public QObject
{
    Q_OBJECT

public:
    explicit GuiPhoneDataModel(QObject *parent = nullptr);

    //!
    //! \brief ~GuiPhoneDataModel
    //!
    ~GuiPhoneDataModel();

    //!
    //! \brief reset
    //!
    void reset();

    //!
    //! \brief setContactData, invoked from GuiController to save data
    //! \param contactItem
    //!
    void setContactData(const std::vector<std::shared_ptr<sdl::ContactItem>>& /*contactItem*/);

    //!
    //! \brief getContactData
    //! \return
    //!
    std::vector<sdl::ContactItem>& getContactData();

    //!
    //! \brief getContactDataAsQList
    //! \return
    //!
    QList<sdl::ContactItem> getContactDataAsQList();

    //!
    //! \brief setContactDataAsQListContactItemModel
    //!
    void setContactDataAsQListContactItemModel();

    //!
    //! \brief getContactDataAsQListContactItemModel
    //! \return
    //!
    QList<ContactItemModel *> getContactDataAsQListContactItemModel();

    //!
    //! \brief setCallLogData, invoked from GuiController to save data
    //!
    void setCallLogData(const std::vector<std::shared_ptr<sdl::CallLogItem>>&);

    //!
    //! \brief getCallLogData
    //! \return
    //!
    std::vector<sdl::CallLogItem>& getCallLogData();

    //!
    //! \brief getCallLogDataAsQList
    //! \return
    //!
    QList<sdl::CallLogItem> getCallLogDataAsQList();

    //!
    //! \brief addCallLogItem
    //! \param name
    //! \param number
    //! \param date
    //! \param type
    //!
    void addCallLogItem(const std::string /*name*/, const std::string /*number*/, const std::string /*date*/, sdl::CallLogType /*type*/);

    //!
    //! \brief setCallLogDataAsQListCallLogItemModel
    //!
    void setCallLogDataAsQListCallLogItemModel();

    //!
    //! \brief getCallLogDataAsQListCallLogItemModel
    //! \return
    //!
    QList<CallLogItemModel *> getCallLogDataAsQListCallLogItemModel();

    //!
    //! \brief setSmsData, invoked from GuiController to save data
    //!
    void setSmsData(const std::vector<std::shared_ptr<sdl::SMSMessage>>&);

    //!
    //! \brief getDateSortedSmsData
    //! \return
    //!
    std::vector<sdl::SMSMessage>& getDateSortedSmsData();

    //!
    //! \brief getDateSortedSmsDataAsQList
    //! \return
    //!
    QList<sdl::SMSMessage> getDateSortedSmsDataAsQList();

    //!
    //! \brief setDateSortedSmsDataAsQListSmSContentModel
    //!
    void setDateSortedSmsDataAsQListSmSContentModel();

    //!
    //! \brief getDateSortedSmsDataAsQListSmSContentModel
    //! \return
    //!
    QList<SmsContent*> getDateSortedSmsDataAsQListSmSContentModel();

    //!
    //! \brief setItemSmsContentDataAsQListSmSContentModel
    //! \param address
    //!
    void setItemSmsContentDataAsQListSmSContentModel(const QString& address);

    //!
    //! \brief getItemSmsContentDataAsQListSmSContentModel
    //! \return
    //!
    QList<SmsContent*> getItemSmsContentDataAsQListSmSContentModel();

    //!
    //! \brief getAddressUniqueSmsData
    //! \return
    //!
    std::vector<sdl::SMSMessage>& getAddressUniqueSmsData();

    //!
    //! \brief getAddressUniqueSmsDataAsQList
    //! \return
    //!
    QList<sdl::SMSMessage> getAddressUniqueSmsDataAsQList();

    //!
    //! \brief setAddressUniqueSmsDataAsQListSmSContentModel
    //!
    void setAddressUniqueSmsDataAsQListSmSContentModel();

    //!
    //! \brief getAddressUniqueSmsDataAsQListSmSContentModel
    //! \return
    //!
    QList<SmsContent*> getAddressUniqueSmsDataAsQListSmSContentModel();

    //!
    //! \brief setListOfAllSMS
    //! \param data
    //!
    void setListOfAllSMS(std::vector<sdl::SMSMessage>& data);

    //!
    //! \brief getListOfAllSMS
    //! \return
    //!
    std::map<std::string,std::vector<sdl::SMSMessage>>& getListOfAllSMS();

    //!
    //! \brief convertTimestampToHumanDate
    //! \param timestamp
    //! \return
    //!
    QString convertTimestampToHumanDate(std::string timestamp);

private:
    //!
    //! \brief mContactData, contain all contact Data
    //!
    std::vector<sdl::ContactItem> mContactData;

    //!
    //! \brief mContactDataAsQListContactItemModel, contain all contact Data
    //!
    QList<ContactItemModel*> mContactDataAsQListContactItemModel;

    //!
    //! \brief mCallLogData, contain all call log data
    //!
    std::vector<sdl::CallLogItem> mCallLogData;

    //!
    //! \brief mCallLogDataAsQListCallLogItemModel, contain all call log data from phone
    //!
    QList<CallLogItemModel*> mCallLogDataAsQListCallLogItemModel;

    //!
    //! \brief mDateSortedSmsData, contain all sms data
    //!
    std::vector<sdl::SMSMessage> mDateSortedSmsData;

    //!
    //! \brief mAddressUniqueSmsData, contain all sms data
    //!
    std::vector<sdl::SMSMessage> mAddressUniqueSmsData;

    //!
    //! \brief mDateSortedSmsDataAsQListSmsContentModel, contain all sms received from phone
    //!
    QList<SmsContent*> mDateSortedSmsDataAsQListSmsContentModel;

    //!
    //! \brief mAddressUniqueSmsDataAsQListSmsContentModel, contain all sms of unique addresses to display in sms list
    //!
    QList<SmsContent*> mAddressUniqueSmsDataAsQListSmsContentModel;

    //!
    //! \brief mItemSmsContentDataAsQListSmsContentModel, contain sms data of 1 address
    //!
    QList<SmsContent*> mItemSmsContentDataAsQListSmsContentModel;

    //!
    //! \brief m_listOfAllSMS, contain all data of sms with unique address
    //!
    std::map<std::string,std::vector<sdl::SMSMessage>> m_listOfAllSMS;

};

#endif // GUIPHONEDATAMODEL_H
