#ifndef PHONECONTROLLER_H
#define PHONECONTROLLER_H

// Qt include
#include <QObject>
#include <QTimer>

// SDL include
#include "sdl_libs/include/SDLTypes.h"

// 2W include
#include "GuiController.h"
#include "SettingHandler.h"
#include "ViewManager.h"
#include "GuiPhoneDataModel.h"
#include "Smscontent.h"
#include "ContactItem.h"

using namespace sdl;

class PhoneController : public sdl::GuiController
{
    Q_OBJECT

    //!
    //! \brief Expose the m_isPhoneConnected member to qml
    //!
    Q_PROPERTY(bool isPhoneConnected READ getIsPhoneConnected NOTIFY IsPhoneConnectedChanged)

    //!
    //! \brief Expose the m_isAppActivated member to qml
    //!
    Q_PROPERTY(bool isAppActivated READ getIsAppActivated NOTIFY IsAppActivatedChanged)

    //!
    //! \brief Expose the m_nameUserCalling member to qml
    //!
    Q_PROPERTY(QString nameUserCalling READ nameUserCalling WRITE setNameUserCalling NOTIFY nameUserCallingChanged)

    //!
    //! \brief Expose the m_smsItemSelected member to qml
    //!
    Q_PROPERTY(QString smsItemSelected READ getSmsItemSelected WRITE setSmsItemSelected NOTIFY smsItemSelectedChanged)

    //!
    //! \brief Expose the m_currentIndextList member to qml
    //!
    Q_PROPERTY(int currentIndexList READ getCurrentIndexList WRITE setCurrentIndexList NOTIFY currentIndexListChanged)

    //!
    //! \brief Expose the m_showPopUp member to qml
    //!
    Q_PROPERTY(bool showPopUp MEMBER m_showPopUp NOTIFY showPopUpChanged)

    //!
    //! \brief Expose the mSmSPopUpAsSmSContentModel member to qml
    //!
    Q_PROPERTY(SmsContent* smsPopUp READ getSmSPopUpContentAsSmSContentModel NOTIFY smSPopUpContentAsSmSContentModelChanged)
public:

    //!
    //! \brief PhoneController
    //! \param parent
    //! \param viewManager
    //! \param phoneDataModel
    //!
    explicit PhoneController(QObject* parent = nullptr
                             , std::shared_ptr<ViewManager> viewManager = nullptr
                             , std::shared_ptr<GuiPhoneDataModel> phoneDataModel = nullptr
                             , std::shared_ptr<SettingHandler> settingHandler = nullptr);


    //!
    //! \brief ~PhoneController
    //!
    ~PhoneController();

    //!
    //! \brief init
    //!
    void init() override;

    //!
    //! \brief getPhoneDataModel
    //! \return
    //!
    std::shared_ptr<GuiPhoneDataModel> getPhoneDataModel();

    //!
    //! \brief getIsPhoneConnected
    //! \return
    //!
    bool getIsPhoneConnected();

    //!
    //! \brief setIsPhoneConnected
    //! \param isPhoneConnected
    //!
    void setIsPhoneConnected(const bool& isPhoneConnected);

    //!
    //! \brief getIsAppActivated
    //! \return
    //!
    bool getIsAppActivated();

    //!
    //! \brief setIsAppActivated
    //! \param isAppActivated
    //!
    void setIsAppActivated(const bool& isAppActivated);

    //!
    //! \brief setNameUserCalling
    //! \param nameUserCalling
    //!
    void setNameUserCalling(QString nameUserCalling);

    //!
    //! \brief nameUserCalling
    //! \return
    //!
    QString nameUserCalling() const;

    //!
    //! \brief getSmsItemSelected
    //! \return
    //!
    QString getSmsItemSelected() const;

    //!
    //! \brief setSmsItemSelected
    //! \param itemSelected
    //!
    void setSmsItemSelected(QString itemSelected);

    //!
    //! \brief getCurrentIndexList
    //! \return
    //!
    int getCurrentIndexList() const;

    //!
    //! \brief setCurrentIndexList
    //! \param currentIndexList
    //!
    void setCurrentIndexList(int currentIndexList);

    //!
    //! \brief setIsMissedCall
    //! \param isMissedCall
    //!
    void setIsMissedCall(const bool& isMissedCall);

    //!
    //! \brief shutdown
    //!
    void shutdown() override;

    //!
    //! \brief makeAPhoneCall
    //! \param phoneNumber
    //!
    Q_INVOKABLE void makeAPhoneCall(QString phoneNumber);

    //!
    //! \brief onDialNumber
    //! \param appId
    //! \param number
    //! \param name
    //!
    void onDialNumber(uint32_t /*appId*/,const std::string /*number*/, const std::string /*name*/);

    //!
    //! \brief updateContactList
    //! \param data
    //!
    void updateContactList(const std::vector<std::shared_ptr<ContactItem>>& /*data*/);

    //!
    //! \brief updateSMSList
    //! \param data
    //!
    void updateSMSList(const std::vector<std::shared_ptr<SMSMessage>>& /*data*/);

    //!
    //! \brief updatePhoneList
    //! \param data
    //!
    void updatePhoneList(const std::vector<std::shared_ptr<CallLogItem>>& /*data*/);

    //!
    //! \brief setSmSPopUpContentAsSmSContentModel
    //! \param sms
    //!
    void setSmSPopUpContentAsSmSContentModel(const std::shared_ptr<sdl::SMSMessage>& smsPopUp);

    //!
    //! \brief getSmSPopUpContentAsSmSContentModel
    //! \return
    //!
    SmsContent* getSmSPopUpContentAsSmSContentModel();

    //!
    //! \brief requestCallLogData, process when press Call on QML
    //!
    Q_INVOKABLE void requestCallLogData();

    //!
    //! \brief requestContactData, process when press Contact on QML
    //!
    Q_INVOKABLE void requestContactData();

    //!
    //! \brief requestMessageData, process when press SMS on QML
    //!
    Q_INVOKABLE void requestMessageData();

signals:

    //!
    //! \brief IsPhoneConnectedChanged
    //!
    void IsPhoneConnectedChanged(const bool&);

    //!
    //! \brief IsAppActivatedChanged()
    //!
    void IsAppActivatedChanged();

    //!
    //! \brief onUsbIconVisibilityChanged
    //!
    void onUsbIconVisibilityChanged(const bool&);

    //!
    //! \brief onWifiIconVisibilityChanged
    //!
    void onWifiIconVisibilityChanged(const bool&);

    //!
    //! \brief onMessageIconVisibilityChanged
    //!
    void onMessageIconVisibilityChanged(const bool&);

    //!
    //! \brief onCallIconVisibilityChanged
    //!
    void onCallIconVisibilityChanged(const bool&);

    //!
    //! \brief onCallLogChanged, signal to inform call data changed
    //!
    void onCallLogChanged();

    //!
    //! \brief onContactDataChanged, signal to inform contact data changed
    //!
    void onContactDataChanged();

    //!
    //! \brief onMessageDataChanged, signal to inform SMS data changed
    //!
    void onMessageDataChanged();

    //!
    //! \brief nameUserCallingChanged
    //!
    void nameUserCallingChanged();

    //!
    //! \brief smsItemSelectedChanged
    //!
    void smsItemSelectedChanged();

    //!
    //! \brief currentIndexListChanged
    //!
    void currentIndexListChanged();

    //!
    //! \brief showPopUpChanged
    //!
    void showPopUpChanged();

    //!
    //! \brief smSPopUpContentAsSmSContentModelChanged
    //!
    void smSPopUpContentAsSmSContentModelChanged();

private:
    //!
    //! \brief m_isPhoneConnected
    //!
    bool m_isPhoneConnected;

    //!
    //! \brief m_isAppActivated
    //!
    bool m_isAppActivated;

    //!
    //! \brief m_ViewManager
    //!
    std::shared_ptr<ViewManager> m_ViewManager;

    //!
    //! \brief m_PhoneDataModel
    //!
    std::shared_ptr<GuiPhoneDataModel> m_PhoneDataModel;

    //!
    //! \brief m_Application
    //!
    sdl::ApplicationInfo m_Application;

    //!
    //! \brief m_nameUserCalling
    //!
    QString m_nameUserCalling;

    //!
    //! \brief m_smsItemSelected
    //!
    QString m_smsItemSelected;

    //!
    //! \brief m_currentIndexList, save previous position of list to jump back when re-access that list
    //!
    int m_currentIndexList;

    //!
    //! \brief m_isRequested, help to request once during phone is connecting
    //!
    bool m_isRequested;

    //!
    //! \brief m_isNewCallLogData, request new data from call log when has new data
    //!
    bool m_isNewCallLogData;

    //!
    //! \brief m_isNewSmsData, request new data from sms when has new data
    //!
    bool m_isNewSmsData;

    //!
    //! \brief m_isMissingCalled
    //!
    bool m_isMissedCalled;

    //!
    //! \brief m_showPopUp, variable keep state to showPopUp or not
    //!
    bool m_showPopUp;

    //!
    //! \brief m_timerShowPopUp stores the timer of popUp
    //!
    QTimer* m_timerShowPopUp;

    //!
    //! \brief mSmSPopUpAsSmSContentModel, contain sms data of 1 address
    //!
    SmsContent* mSmSPopUpAsSmSContentModel;

    std::vector<std::shared_ptr<CallLogItem>> m_list1;
    std::vector<std::shared_ptr<ContactItem>> m_list2;
    std::vector<std::shared_ptr<SMSMessage>>  m_list3;

    // Call Log List
//    std::shared_ptr<CallLogItem> test1 = std::make_shared<CallLogItem>(1,"Mr.A","111","1646665749856","0",CallLogType::DIAL);
//    std::shared_ptr<CallLogItem> test1 = std::make_shared<CallLogItem>(1,"Mr.A","111","1646665749856","0",CallLogType::DIAL);
    //    std::shared_ptr<CallLogItem> test2 = std::make_shared<CallLogItem>(2,"Mr.B","222","1646933663017","0",CallLogType::MISSED);
    //    std::shared_ptr<CallLogItem> test3 = std::make_shared<CallLogItem>(3,"Mr.C","333","1646665749856","0",CallLogType::IN_CALL);
    //    std::shared_ptr<CallLogItem> test4 = std::make_shared<CallLogItem>(4,"Mr.D","444","1652341860000","0",CallLogType::IN_CALL);
    //    std::shared_ptr<CallLogItem> test5 = std::make_shared<CallLogItem>(4,"Mr.E","555","1652514720000","0",CallLogType::DIAL);




    std::map<std::string, int> callLogId1 = {{"id",1}};
    std::map<std::string, std::string> callLogInfor1 = { {"Name", "Long"},{"Number","0966837365"},{"Date","1646933663017"},{"Duration","0"}};
    std::map<std::string, CallLogType> callLogState1 = {{"type", CallLogType::DIAL}};

    std::map<std::string, int> callLogId2 = {{"id",2}};
    std::map<std::string, std::string> callLogInfor2 = { {"Name", "Lieu"},{"Number","0966837365"},{"Date","1646933663017"},{"Duration","0"}};
    std::map<std::string, CallLogType> callLogState2 = {{"type",CallLogType::MISSED}};

    std::map<std::string, int> callLogId3 = {{"id",3}};
    std::map<std::string, std::string> callLogInfor3 = { {"Name", "Nguyen"},{"Number","096683365"},{"Date","1646933663017"},{"Duration","0"}};
    std::map<std::string, CallLogType> callLogState3 = {{"type",CallLogType::DIAL}};

    std::map<std::string, int> callLogId4 = {{"id",4}};
    std::map<std::string, std::string> callLogInfor4 = { {"Name", "Hong"},{"Number","096687365"},{"Date","1646933663017"},{"Duration","0"}};
    std::map<std::string, CallLogType> callLogState4 = {{"type",CallLogType::DIAL}};

    std::map<std::string, int> callLogId5 = {{"id",5}};
    std::map<std::string, std::string> callLogInfor5 = { {"Name", "Hoang"},{"Number","0966383765"},{"Date","1646933663017"},{"Duration","20"}};
    std::map<std::string, CallLogType> callLogState5 = {{"type",CallLogType::DIAL}};

    // Contact List
    std::map<std::string, std::string> contact1 = { {"Name", "Long"},{"Number","0966837365"}};
    std::map<std::string, std::string> contact2 = { {"Name", "Do"},{"Number","0966837365"}};
    std::map<std::string, std::string> contact3 = { {"Name", "Nam"},{"Number","0966837365"}};
    std::map<std::string, std::string> contact4 = { {"Name", "Viet"},{"Number","0966837365"}};
    std::map<std::string, std::string> contact5 = { {"Name", "Hai"},{"Number","0966837365"}};

    // Sms
    std::map<std::string, std::string> message1 = { {"Address", "Long"},{"Date","1646665749856"} ,{"Body", "Hello world"}};
    std::map<std::string, int> state1 = {{"id",1},{"read",1},{"type",1}};
    std::map<std::string, std::string> message2 = {{"Address", "Truong"},{"Date","1646933590000"}, {"Body", "Good bye"}};
    std::map<std::string, int> state2 = {{"id", 2}, {"read",0},{"type",0}};
    std::map<std::string, std::string> message3 = { {"Address", "Tan"},{"Date","1646933590000"}, {"Body", "Xin chao"}};
    std::map<std::string, int> state3 = {{"id", 3},{"read",0},{"type",2}};
    std::map<std::string, std::string> message4 = { {"Address", "Han"},{"Date","1646933590000"}, {"Body", "What?"}};
    std::map<std::string, int> state4 = {{"id", 4},{"read",0},{"type",1}};
    std::map<std::string, std::string> message5 = { {"Address", "Tuan"},{"Date","1646933590000"}, {"Body", "I have a gift for you"}};
    std::map<std::string, int> state5 = {{"id", 5},{"read",1},{"type",2}};



    // Create dumpmy data call log
    std::vector<std::map<std::string, int>> dataCallLogId = {callLogId1,callLogId2,callLogId3,callLogId4,callLogId5};
    std::vector<std::map<std::string, std::string>> dataCallLogInfor = {callLogInfor1,callLogInfor2,callLogInfor3,callLogInfor4,callLogInfor5};
    std::vector<std::map<std::string, sdl::CallLogType>> dataCallLogState = {callLogState1,callLogState2,callLogState3,callLogState4,callLogState5};
    // Receive Data CallLogs
    std::vector<std::map<std::string, int>> callLogsId = dataCallLogId;
    std::vector<std::map<std::string, std::string>> callLogsInfor = dataCallLogInfor;
    std::vector<std::map<std::string, sdl::CallLogType>> callLogsState = dataCallLogState;

    // Create dumpmy data contact
    std::vector<std::map<std::string, std::string>> dataContact = {contact1,contact2,contact3,contact4,contact5};
    // Receive Data Contacts
    std::vector<std::map<std::string, std::string>> contacts = dataContact;

    // Create dumpmy data Sms
    std::vector<std::map<std::string, std::string>> dataSms = {message1,message2,message3,message4,message5};
    std::vector<std::map<std::string, int>> dataSmsState = {state1,state2,state3,state4,state5};
    // Receive Data Sms
    std::vector<std::map<std::string, std::string>> messages = dataSms;
    std::vector<std::map<std::string, int>> messagesState = dataSmsState;



    // Process Data CallLog
    void setDataCallLog(std::vector<std::map<std::string, int>> &dataCallLogId
                       ,std::vector<std::map<std::string, std::string>> &dataCallLogInfor
                       ,std::vector<std::map<std::string, sdl::CallLogType>> &dataCallLogState);

    // Process Data Contact
    void setDataContact(std::vector<std::map<std::string, std::string>> &contactList);

    // Process Data Sms
    void setDataSms(std::vector<std::map<std::string, std::string>> &messages
                   ,std::vector<std::map<std::string, int>> &messagesState);

};

#endif // PHONECONTROLLER_H
