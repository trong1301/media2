// Qt include
#include "QDebug"
#include <QDateTime>

// 2W include
#include "include/PhoneController.h"

using namespace sdl;
using namespace Helper::MagicNumbers;

PhoneController::PhoneController(QObject *parent
    , std::shared_ptr<ViewManager> viewManager
    , std::shared_ptr<GuiPhoneDataModel> phoneDataModel
    , std::shared_ptr<SettingHandler> settingHandler)
    : sdl::GuiController(parent, settingHandler)
    , m_isPhoneConnected(false)
    , m_isAppActivated(false)
    , m_ViewManager(viewManager)
    , m_PhoneDataModel(phoneDataModel)
    , m_Application(0,"",nullptr)
    , m_nameUserCalling("")
    , m_smsItemSelected("")
    , m_currentIndexList(0)
    , m_isRequested(false)
    , m_isNewCallLogData(true)
    , m_isNewSmsData(true)
    , m_showPopUp(false)
    , mSmSPopUpAsSmSContentModel(new SmsContent(parent))
{

    // Timer to show popUp
    m_timerShowPopUp = new QTimer(this);
    m_timerShowPopUp->setSingleShot(true);
    m_timerShowPopUp->setInterval(5000);
    connect(m_timerShowPopUp, &QTimer::timeout, this, [&](){
        m_showPopUp = false;
        emit showPopUpChanged();
    });

    connect(this, &PhoneController::smSPopUpContentAsSmSContentModelChanged, this, [&]{
        if(m_isAppActivated) // Avoid trigger when phone was disconnected :|
        {
            // Trigger show popUp in N sec
            m_showPopUp = true;
            emit showPopUpChanged();
            m_timerShowPopUp->start();
        }
    });

#ifdef NATIVE_BUILD
//    std::shared_ptr<CallLogItem> test1 = std::make_shared<CallLogItem>(1,"Mr.A","111","1646665749856","0",CallLogType::DIAL);
//    std::shared_ptr<CallLogItem> test2 = std::make_shared<CallLogItem>(2,"Mr.B","222","1646933663017","0",CallLogType::MISSED);
//    std::shared_ptr<CallLogItem> test3 = std::make_shared<CallLogItem>(3,"Mr.C","333","1646665749856","0",CallLogType::IN_CALL);
//    std::shared_ptr<CallLogItem> test4 = std::make_shared<CallLogItem>(4,"Mr.D","444","1652341860000","0",CallLogType::IN_CALL);
//    std::shared_ptr<CallLogItem> test5 = std::make_shared<CallLogItem>(4,"Mr.E","555","1652514720000","0",CallLogType::DIAL);
//    m_list1.push_back(test1);
//    m_list1.push_back(test2);
//    m_list1.push_back(test3);
//    m_list1.push_back(test4);
//    m_list1.push_back(test5);

//    std::shared_ptr<ContactItem> t1 = std::make_shared<ContactItem>(1,"A very long long text user address","111");
//    std::shared_ptr<ContactItem> t2 = std::make_shared<ContactItem>(2,"Số nước ngoài","+184383925644");
//    std::shared_ptr<ContactItem> t3 = std::make_shared<ContactItem>(3,"Boschler 1","02838270150");
//    std::shared_ptr<ContactItem> t4 = std::make_shared<ContactItem>(4,"Universal-777 ","0938827922");
//    std::shared_ptr<ContactItem> t5 = std::make_shared<ContactItem>(5,"emc-34","+84936992724");
//    std::shared_ptr<ContactItem> t6 = std::make_shared<ContactItem>(6,"tống Anh Quân","123456789");
//    m_list2.push_back(t1);
//    m_list2.push_back(t2);
//    m_list2.push_back(t3);
//    m_list2.push_back(t4);
//    m_list2.push_back(t5);
//    m_list2.push_back(t6);

//    std::shared_ptr<SMSMessage> test6 = std::make_shared<SMSMessage>(1,"Nhân vật từ một vũ trụ khác","Text1","1646665749856",0,1);
//    std::shared_ptr<SMSMessage> test7 = std::make_shared<SMSMessage>(2,"Mr.A","You can read about the opening of a new software center in Hanoi "
//                                                                                "to help expand its business. "
//                                                                                "The BGSW site in Hanoi, "
//                                                                                "a subsidiary company of Bosch","1646894445622",1,1);
//    std::shared_ptr<SMSMessage> test8 = std::make_shared<SMSMessage>(3,"Mr.B","Text3","1646933590000",1,2);
//    std::shared_ptr<SMSMessage> test9 = std::make_shared<SMSMessage>(4,"Mr.B","Text4","1646933663017",1,2);
//    std::shared_ptr<SMSMessage> test10 = std::make_shared<SMSMessage>(5,"Mr.A","Siemens Home Appliances Brand Reshaping Announcement now online!","1646894144622",1,2);
//    std::shared_ptr<SMSMessage> test11 = std::make_shared<SMSMessage>(6,"Xiu","New sms to Boschlerrrr "
//                                                                                "We are BGSV's member in this earth "
//                                                                                "Our universal has 2W project, Yay! "
//                                                                                "FixMergeConflict AndHelpTaAnhDuy "
//                                                                                "FixMergeConflict AndHelpTaAnhDuy "
//                                                                                "FixMergeConflict AndHelpTaAnhDuy "
//                                                                                "FixMergeConflict AndHelpTaAnhDuy "
//                                                                                "FixMergeConflict","1646665749856",1,2);
//    std::shared_ptr<SMSMessage> test12 = std::make_shared<SMSMessage>(7,"Mice","Text7","1646662349856",1,1);

//    m_list3.push_back(test6);
//    m_list3.push_back(test7);
//    m_list3.push_back(test8);
//    m_list3.push_back(test9);
//    m_list3.push_back(test10);
//    m_list3.push_back(test11);
//    m_list3.push_back(test12);

    setDataCallLog(callLogsId,callLogsInfor,callLogsState);
    setDataContact(contacts);
    setDataSms(messages,messagesState);

    updatePhoneList(m_list1);
    updateContactList(m_list2);
    updateSMSList(m_list3);
#endif
}

void PhoneController::setDataCallLog(std::vector<std::map<std::string, int> > &dataCallLogId,
                                     std::vector<std::map<std::string, std::string> > &dataCallLogInfor,
                                     std::vector<std::map<std::string, CallLogType> > &dataCallLogState)
{
    if(dataCallLogInfor.size() ==  dataCallLogState.size() && dataCallLogInfor.size() > 0){
        for (int i = 0; i < dataCallLogInfor.size(); ++i) {
            std::shared_ptr<CallLogItem>dataCallLogFrame = std::make_shared<CallLogItem>(dataCallLogId[i]["id"]
                    ,dataCallLogInfor[i]["Name"]
                    ,dataCallLogInfor[i]["Number"]
                    ,dataCallLogInfor[i]["Date"]
                    ,dataCallLogInfor[i]["Duration"]
                    ,dataCallLogState[i]["type"]);
            m_list1.push_back(dataCallLogFrame);
        }
    }else {
        qDebug() << "Can not pass value ";
    }
}

void PhoneController::setDataContact(std::vector<std::map<std::string, std::string> > &contactList)
{
    if(contactList.size()>0){
        for (int i = 0; i < contactList.size(); ++i) {
            std::shared_ptr<ContactItem>dataContactFrame = std::make_shared<ContactItem>(i,contactList[i]["Name"]
                    ,contactList[i]["Number"]);
            m_list2.push_back(dataContactFrame);
        }
    }
}

void PhoneController::setDataSms(std::vector<std::map<std::string,std::string>>&messages
                                ,std::vector<std::map<std::string, int>> &messagesState)
{
    if( messages.size() > 0 && messages.size() == messagesState.size() ){
        for(int i  = 0 ; i < messages.size() ; i++){
            std::shared_ptr<SMSMessage>dataFrame = std::make_shared<SMSMessage>(messagesState[i]["id"]
                    ,messages[i]["Address"]
                    ,messages[i]["Body"]
                    ,messages[i]["Date"]
                    ,messagesState[i]["read"]
                    ,messagesState[i]["type"]);
            m_list3.push_back(dataFrame);
        }
    }
}

PhoneController::~PhoneController()
{
    shutdown();
}

void PhoneController::init()
{
    sdl::GuiController::init();
}

std::shared_ptr<GuiPhoneDataModel> PhoneController::getPhoneDataModel()
{
    return m_PhoneDataModel;
}

bool PhoneController::getIsPhoneConnected()
{
    return m_isPhoneConnected;
}

void PhoneController::setIsPhoneConnected(const bool& isPhoneConnected)
{
    if(m_isPhoneConnected == isPhoneConnected)
        return;

    m_isPhoneConnected = isPhoneConnected;
    emit IsPhoneConnectedChanged(m_isPhoneConnected);
}

bool PhoneController::getIsAppActivated()
{
    return m_isAppActivated;
}

void PhoneController::setIsAppActivated(const bool &isAppActivated)
{
    if(m_isAppActivated == isAppActivated)
        return;

    m_isAppActivated = isAppActivated;
    emit IsAppActivatedChanged();
}

void PhoneController::shutdown()
{
    disconnect(m_timerShowPopUp, &QTimer::timeout, this, nullptr);
    disconnect(this, &PhoneController::smSPopUpContentAsSmSContentModelChanged, this, nullptr);
}

void PhoneController::onDialNumber(uint32_t appId, const std::string number, const std::string name)
{
    qDebug() << "onDial Number calling: " << number.c_str() << " - name: " << name.c_str() << " appId: " << appId;
    if(TwoWheelsTypes::UNKNOWN_USER_CALLING == name.c_str())
    {
        setNameUserCalling(number.c_str());
    }
    else
    {
        setNameUserCalling(name.c_str());
    }
    // When has new dialing, change param to request new data from phone (But just temporary until could indentify CALL STATE)
    m_isNewCallLogData = true;

    // Get current viewState before change to outgoing screen
    m_ViewManager->setLastViewState(m_ViewManager->getViewState());
    m_ViewManager->requestChangeViewState(ViewScreen::ANYWHERE.c_str(),ViewScreen::TOP_OUTGOING_CALL.c_str());
}

void PhoneController::updatePhoneList(const std::vector<std::shared_ptr<CallLogItem> > &data)
{
    qDebug() << "CALL_LOG list: " << data.size() << "items";
    m_PhoneDataModel->setCallLogData(data);

    setCurrentIndexList(0);
    emit onCallLogChanged();

    // The call log list will be updated when re-enter if has any phone call before
    // -> We will remove missed call icon
    setIsMissedCall(false);
}

void PhoneController::setSmSPopUpContentAsSmSContentModel(const std::shared_ptr<SMSMessage> &smsPopUp)
{
    if(m_PhoneDataModel->getContactData().size() != 0)
    {
        QString popUpAddr = smsPopUp.get()->address_.c_str();
        popUpAddr.remove(0,3);
        bool isExisted = false;
        for(int i = 0 ; i < m_PhoneDataModel->getContactDataAsQListContactItemModel().size(); i++)
        {
            QString numberOfContact = m_PhoneDataModel->getContactDataAsQListContactItemModel().at(i)->contactNumber();
            if(numberOfContact.contains(popUpAddr))
            {
                mSmSPopUpAsSmSContentModel->setAddress(m_PhoneDataModel->getContactDataAsQListContactItemModel().at(i)->contactName());
                isExisted = true;
                break;
            }
        }
        if(!isExisted)
        {
            mSmSPopUpAsSmSContentModel->setAddress(smsPopUp.get()->address_.c_str());
        }
    }
    else
    {
        mSmSPopUpAsSmSContentModel->setAddress(smsPopUp.get()->address_.c_str());
    }
    mSmSPopUpAsSmSContentModel->setBody(smsPopUp.get()->body_.c_str());
    mSmSPopUpAsSmSContentModel->setDate(m_PhoneDataModel->convertTimestampToHumanDate(smsPopUp.get()->date_.c_str()));
    mSmSPopUpAsSmSContentModel->setRead(smsPopUp.get()->read_);
    mSmSPopUpAsSmSContentModel->setType(smsPopUp.get()->type_);

    emit smSPopUpContentAsSmSContentModelChanged();
}

SmsContent *PhoneController::getSmSPopUpContentAsSmSContentModel()
{
    return mSmSPopUpAsSmSContentModel;
}

void PhoneController::updateContactList(const std::vector<std::shared_ptr<ContactItem>>& data)
{
    qDebug() << "CONTACT list:" << data.size() << "items";
    m_PhoneDataModel->setContactData(data);

    setCurrentIndexList(0);
    emit onContactDataChanged();
}

void PhoneController::updateSMSList(const std::vector<std::shared_ptr<SMSMessage> > &data)
{
    qDebug() << "SMS list: " << data.size() << "items";
    m_PhoneDataModel->setSmsData(data);

    setCurrentIndexList(0);
    emit onMessageDataChanged();
}

int PhoneController::getCurrentIndexList() const
{
    return m_currentIndexList;
}

void PhoneController::setCurrentIndexList(int currentIndexList)
{
    if (m_currentIndexList == currentIndexList)
        return;

    m_currentIndexList = currentIndexList;
    emit currentIndexListChanged();
}

void PhoneController::setIsMissedCall(const bool &isMissedCall)
{
    if (m_isMissedCalled == isMissedCall)
        return;

    m_isMissedCalled = isMissedCall;
    emit onCallIconVisibilityChanged(m_isMissedCalled);
}

void PhoneController::setNameUserCalling(QString nameUserCalling)
{
    if (m_nameUserCalling == nameUserCalling)
        return;

    m_nameUserCalling = nameUserCalling;
    emit nameUserCallingChanged();
}

QString PhoneController::nameUserCalling() const
{
    return m_nameUserCalling;
}

QString PhoneController::getSmsItemSelected() const
{
    return m_smsItemSelected;
}

void PhoneController::setSmsItemSelected(QString itemSelected)
{
    if (m_smsItemSelected != itemSelected || m_isNewSmsData)
    {
        m_smsItemSelected = itemSelected;
        m_PhoneDataModel->setItemSmsContentDataAsQListSmSContentModel(m_smsItemSelected);

        emit smsItemSelectedChanged();
    }
    m_ViewManager->requestChangeViewState(ViewScreen::SUBGAUGE_PHONE_SMS_LIST.c_str(), ViewScreen::SUBGAUGE_PHONE_SMS_ITEM.c_str());
}

void PhoneController::makeAPhoneCall(QString phoneNumber){
    qDebug() << "Make a phone call to" << phoneNumber;
}

void PhoneController::requestCallLogData()
{
    if(m_PhoneDataModel->getCallLogData().size() == 0 || m_isNewCallLogData)
    {
        m_isNewCallLogData = false;
    }
    emit onCallLogChanged();
}

void PhoneController::requestContactData()
{
    if(m_PhoneDataModel->getContactData().size() == 0)
    {
    }
    emit onContactDataChanged();
}

void PhoneController::requestMessageData()
{
    if((m_PhoneDataModel->getDateSortedSmsData().size() == 0
            && m_PhoneDataModel->getAddressUniqueSmsData().size() == 0) || m_isNewSmsData)
    {
        m_smsItemSelected = "";
        m_isNewSmsData = false;
    }
    emit onMessageDataChanged();
}


