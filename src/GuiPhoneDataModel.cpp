// 2W includes
#include "include/GuiPhoneDataModel.h"
#include "include/MagicNumbers.h"

// Qt includes
#include "QDebug"
#include <QDateTime>

GuiPhoneDataModel::GuiPhoneDataModel(QObject *parent) : QObject(parent)
{

}

GuiPhoneDataModel::~GuiPhoneDataModel()
{
    qDebug() << "~GuiPhoneDataModel DESTRUCTOR";
    reset();
}

void GuiPhoneDataModel::reset(){
    mContactData.clear();
    mCallLogData.clear();
    mDateSortedSmsData.clear();
    mAddressUniqueSmsData.clear();
    for (auto iter : mContactDataAsQListContactItemModel)
    {
        if(iter != nullptr)
            delete iter;
    }
    for (auto iter : mCallLogDataAsQListCallLogItemModel)
    {
        if(iter != nullptr)
            delete iter;
    }
    for (auto iter : mDateSortedSmsDataAsQListSmsContentModel)
    {
        if(iter != nullptr)
            delete iter;
    }
    for (auto iter : mAddressUniqueSmsDataAsQListSmsContentModel)
    {
        if(iter != nullptr)
            delete iter;
    }
    for (auto iter : mItemSmsContentDataAsQListSmsContentModel)
    {
        if(iter != nullptr)
            delete iter;
    }
    mContactDataAsQListContactItemModel.clear();
    mCallLogDataAsQListCallLogItemModel.clear();
    mDateSortedSmsDataAsQListSmsContentModel.clear();
    mAddressUniqueSmsDataAsQListSmsContentModel.clear();
    mItemSmsContentDataAsQListSmsContentModel.clear();
}

std::string to_lower(std::string s)
{
    for (auto & c : s)
        c = std::tolower(c);
    return s;
}

bool string_comp(std::string const & lhs, std::string const & rhs)
{
    auto lhs_lower = to_lower(lhs);
    auto rhs_lower = to_lower(rhs);
    if (lhs_lower == rhs_lower)
        return rhs < lhs;
    return lhs_lower < rhs_lower;
}

void GuiPhoneDataModel::setContactData(const std::vector<std::shared_ptr<sdl::ContactItem>>& data){
    // clear old data
    mContactData.clear();

    for(uint32_t i=0; i<data.size();i++){
        // Put data into list
        sdl::ContactItem contactItem(
                    data[i]->command_id_,
                    data[i]->name_,
                    data[i]->number_
                    );
        mContactData.push_back(contactItem);
    }
    std::sort(mContactData.begin(), mContactData.end(), [](const sdl::ContactItem& lhs, const sdl::ContactItem& rhs) {
        return string_comp(lhs.name_ , rhs.name_);
    });
    setContactDataAsQListContactItemModel();
    //    for(uint32_t i =0; i < mContactData.size(); i++)
    //    {
    //        qDebug() << "id: " << mContactData.at(i).command_id_ << "name: " << mContactData.at(i).name_.c_str() << "number: " << mContactData.at(i).number_.c_str() ;
    //    }
}

std::vector<sdl::ContactItem>& GuiPhoneDataModel::getContactData(){
    return mContactData;
}

QList<sdl::ContactItem> GuiPhoneDataModel::getContactDataAsQList(){
    QList<sdl::ContactItem> myQList;
    myQList.reserve(mContactData.size());
    for(size_t i = 0, l = mContactData.size(); i < l; ++i)
        myQList << mContactData[i];

    return myQList;
}

void GuiPhoneDataModel::setContactDataAsQListContactItemModel()
{
    for (auto iter : mContactDataAsQListContactItemModel)
    {
        if(iter != nullptr)
            delete iter;
    }
    mContactDataAsQListContactItemModel.clear();
    for (auto iter = mContactData.begin(); iter != mContactData.end(); ++iter)
    {
        ContactItemModel* tmp = new ContactItemModel();
        tmp->setContactName(iter->name_.c_str());
        tmp->setcontactNumber(iter->number_.c_str());
        tmp->setcontactImage("");
        mContactDataAsQListContactItemModel.push_back(tmp);
    }
}

QList<ContactItemModel *> GuiPhoneDataModel::getContactDataAsQListContactItemModel()
{
    return mContactDataAsQListContactItemModel;
}

void GuiPhoneDataModel::setCallLogData(const std::vector<std::shared_ptr<sdl::CallLogItem>>& data){
    // clear old data
    mCallLogData.clear();

    for(uint32_t i=0; i<data.size();i++){
        // Put data into list
        sdl::CallLogItem callLogItem(
                    data[i]->command_id_,
                    data[i]->name_,
                    data[i]->number_,
                    data[i]->date_,
                    data[i]->duration_,
                    data[i]->type_
                    );
        mCallLogData.push_back(callLogItem);
    }

    setCallLogDataAsQListCallLogItemModel();
    //    for (uint32_t i = 0; i < mCallLogData.size(); i++)
    //    {
    //        qDebug() << "###############################";
    //        qDebug() << "id:"<<mCallLogData.at(i).command_id_<<"name:"<<mCallLogData.at(i).name_.c_str();
    //        qDebug() << "number:"<<mCallLogData.at(i).number_.c_str()<<"date:"<<mCallLogData.at(i).date_.c_str();
    //        qDebug() << "duration:"<<mCallLogData.at(i).duration_.c_str()<<"type:"<<(int)mCallLogData.at(i).type_;
    //    }
}

void GuiPhoneDataModel::addCallLogItem(const std::string name, const std::string number, const std::string date, sdl::CallLogType type){
    sdl::CallLogItem callLogItem(
                1, // dummy
                name,
                number,
                date,
                "0", // dummy
                type
                );

    std::vector<sdl::CallLogItem>::iterator it;
    it = mCallLogData.begin();
    mCallLogData.insert(it, callLogItem);
}

void GuiPhoneDataModel::setCallLogDataAsQListCallLogItemModel()
{
    for (auto iter : mCallLogDataAsQListCallLogItemModel)
    {
        if(iter != nullptr)
            delete iter;
    }

    mCallLogDataAsQListCallLogItemModel.clear();
    for (auto iter = mCallLogData.begin(); iter != mCallLogData.end(); ++iter)
    {
        CallLogItemModel* tmp = new CallLogItemModel();
        if(TwoWheelsTypes::UNKNOWN_USER_CALLING == iter->name_.c_str())
        {
            tmp->setCallLogName(iter->number_.c_str());
        }
        else
        {
            tmp->setCallLogName(iter->name_.c_str());
        }
        tmp->setCallLogNumber(iter->number_.c_str());
        tmp->setCallLogDate(convertTimestampToHumanDate(iter->date_.c_str()));
        tmp->setCallLogDuration(iter->duration_.c_str());
        uint8_t callType = 0;
        if(iter->type_ == sdl::CallLogType::IN_CALL)
        {
            callType = 1;
        }
        else if(iter->type_ == sdl::CallLogType::DIAL)
        {
            callType = 2;
        }
        else if(iter->type_ == sdl::CallLogType::MISSED)
        {
            callType = 3;
        }
        tmp->setCallLogType(callType);
        mCallLogDataAsQListCallLogItemModel.push_back(tmp);
    }
}

QList<CallLogItemModel *> GuiPhoneDataModel::getCallLogDataAsQListCallLogItemModel()
{
    return mCallLogDataAsQListCallLogItemModel;
}

std::vector<sdl::CallLogItem>& GuiPhoneDataModel::getCallLogData(){
    return mCallLogData;
}

QList<sdl::CallLogItem> GuiPhoneDataModel::getCallLogDataAsQList(){
    QList<sdl::CallLogItem> myQList;
    myQList.reserve(mCallLogData.size());
    for(size_t i = 0, l = mCallLogData.size(); i < l; ++i)
        myQList << mCallLogData[i];

    return myQList;
}

void GuiPhoneDataModel::setSmsData(const std::vector<std::shared_ptr<sdl::SMSMessage>>& data){
    // clear old data
    mDateSortedSmsData.clear();
    mAddressUniqueSmsData.clear();

    for(uint32_t i=0; i<data.size();i++){
        // Put data into list
        sdl::SMSMessage smsItem(
                    data[i]->command_id_,
                    data[i]->address_,
                    data[i]->body_,
                    data[i]->date_,
                    data[i]->read_,
                    data[i]->type_
                    );
        mDateSortedSmsData.push_back(smsItem);
        mAddressUniqueSmsData.push_back(smsItem);
    }

    // keep track full list for filter by address later
    std::sort(mDateSortedSmsData.begin(), mDateSortedSmsData.end(), [](const sdl::SMSMessage& lhs, const sdl::SMSMessage& rhs) {
        return (lhs.date_ < rhs.date_);
    });

    // sort by address_ and date_ for unique
    std::sort(mAddressUniqueSmsData.begin(), mAddressUniqueSmsData.end(), [](const sdl::SMSMessage& lhs, const sdl::SMSMessage& rhs) {
        uint64_t ldate = std::stoull(lhs.date_);
        uint64_t rdate = std::stoull(rhs.date_);
        return std::tie(lhs.address_, ldate) > std::tie(rhs.address_, rdate);});

    setListOfAllSMS(mAddressUniqueSmsData);

    // make unique by address_, remove duplicating address_ from the last of list
    mAddressUniqueSmsData.erase(std::unique(mAddressUniqueSmsData.begin(), mAddressUniqueSmsData.end()), mAddressUniqueSmsData.end());

    // sort by date_
    std::sort(mAddressUniqueSmsData.begin(), mAddressUniqueSmsData.end(), [](const sdl::SMSMessage& lhs, const sdl::SMSMessage& rhs) {
        return (lhs.date_ > rhs.date_);
    });

    setDateSortedSmsDataAsQListSmSContentModel();
    setAddressUniqueSmsDataAsQListSmSContentModel();

    //        for (uint32_t i = 0; i < mDateSortedSmsData.size(); i++)
    //        {
    //            qDebug() << "###############################";
    //            qDebug() << "id:"<<mDateSortedSmsData.at(i).command_id_<<"addr:"<<mDateSortedSmsData.at(i).address_.c_str();
    //            qDebug() << "body:"<<mDateSortedSmsData.at(i).body_.c_str();
    //            qDebug() << "date:"<<mDateSortedSmsData.at(i).date_.c_str()<<"read:"<<mDateSortedSmsData.at(i).read_<<"type:"<<mDateSortedSmsData.at(i).type_;
    //        }

    //        for (uint32_t i = 0; i < mAddressUniqueSmsData.size(); i++)
    //        {
    //            qDebug() << "UNIQUE ###############################";
    //            qDebug() << "id:"<<mAddressUniqueSmsData.at(i).command_id_<<"addr:"<<mAddressUniqueSmsData.at(i).address_.c_str();
    //            qDebug() << "body:"<<mAddressUniqueSmsData.at(i).body_.c_str();
    //            qDebug() << "date:"<<mAddressUniqueSmsData.at(i).date_.c_str()<<"read:"<<mAddressUniqueSmsData.at(i).read_<<"type:"<<mAddressUniqueSmsData.at(i).type_;
    //        }
}

std::vector<sdl::SMSMessage>& GuiPhoneDataModel::getDateSortedSmsData(){
    return mDateSortedSmsData;
}

QList<sdl::SMSMessage> GuiPhoneDataModel::getDateSortedSmsDataAsQList(){
    QList<sdl::SMSMessage> myQList;
    myQList.reserve(mDateSortedSmsData.size());
    for(size_t i = 0, l = mDateSortedSmsData.size(); i < l; ++i)
        myQList << mDateSortedSmsData[i];

    return myQList;
}

void GuiPhoneDataModel::setDateSortedSmsDataAsQListSmSContentModel()
{
    for (auto iter : mDateSortedSmsDataAsQListSmsContentModel)
    {
        if(iter != nullptr)
            delete iter;
    }

    mDateSortedSmsDataAsQListSmsContentModel.clear();
    for(size_t i = 0, l = mDateSortedSmsData.size(); i < l; ++i)
    {
        SmsContent* tmp = new SmsContent();
        tmp->setAddress(mDateSortedSmsData.at(i).address_.c_str());
        tmp->setBody(mDateSortedSmsData.at(i).body_.c_str());
        tmp->setDate(convertTimestampToHumanDate(mDateSortedSmsData.at(i).date_.c_str()));
        tmp->setRead(mDateSortedSmsData.at(i).read_);
        tmp->setType(mDateSortedSmsData.at(i).type_);
        mDateSortedSmsDataAsQListSmsContentModel.push_back(tmp);
    }
}

QList<SmsContent *> GuiPhoneDataModel::getDateSortedSmsDataAsQListSmSContentModel(){
    return mDateSortedSmsDataAsQListSmsContentModel;
}

void GuiPhoneDataModel::setItemSmsContentDataAsQListSmSContentModel(const QString &address)
{
    for (auto iter : mItemSmsContentDataAsQListSmsContentModel)
    {
        if(iter != nullptr)
            delete iter;
    }
    mItemSmsContentDataAsQListSmsContentModel.clear();
    for (auto iter = m_listOfAllSMS.begin(); iter != m_listOfAllSMS.end(); ++iter){
        if(iter->first == address.toStdString())
        {
            for (auto kter = iter->second.begin(); kter != iter->second.end(); ++kter)
            {
                SmsContent* tmp = new SmsContent();
                tmp->setAddress(iter->first.c_str());
                tmp->setBody(kter->body_.c_str());
                tmp->setDate(convertTimestampToHumanDate(kter->date_.c_str()));
                tmp->setRead(kter->read_);
                tmp->setType(kter->type_);
                mItemSmsContentDataAsQListSmsContentModel.push_front(tmp);
            }
        }
    }
}

QList<SmsContent *> GuiPhoneDataModel::getItemSmsContentDataAsQListSmSContentModel(){
    return mItemSmsContentDataAsQListSmsContentModel;
}

std::vector<sdl::SMSMessage>& GuiPhoneDataModel::getAddressUniqueSmsData(){
    return mAddressUniqueSmsData;
}

QList<sdl::SMSMessage> GuiPhoneDataModel::getAddressUniqueSmsDataAsQList(){
    QList<sdl::SMSMessage> myQList;
    myQList.reserve(mAddressUniqueSmsData.size());
    for(size_t i = 0, l = mAddressUniqueSmsData.size(); i < l; ++i)
        myQList << mAddressUniqueSmsData[i];

    return myQList;
}

void GuiPhoneDataModel::setAddressUniqueSmsDataAsQListSmSContentModel()
{
    for (auto iter : mAddressUniqueSmsDataAsQListSmsContentModel)
    {
        if(iter != nullptr)
            delete iter;
    }

    mAddressUniqueSmsDataAsQListSmsContentModel.clear();
    for(size_t i = 0, l = mAddressUniqueSmsData.size(); i < l; ++i)
    {
        SmsContent* tmp = new SmsContent();
        tmp->setAddress(mAddressUniqueSmsData.at(i).address_.c_str());
        tmp->setBody(mAddressUniqueSmsData.at(i).body_.c_str());
        tmp->setDate(convertTimestampToHumanDate(mAddressUniqueSmsData.at(i).date_.c_str()));
        tmp->setRead(mAddressUniqueSmsData.at(i).read_);
        tmp->setType(mAddressUniqueSmsData.at(i).type_);
        mAddressUniqueSmsDataAsQListSmsContentModel.push_back(tmp);
    }
}

QList<SmsContent *> GuiPhoneDataModel::getAddressUniqueSmsDataAsQListSmSContentModel(){
    return mAddressUniqueSmsDataAsQListSmsContentModel;
}

void GuiPhoneDataModel::setListOfAllSMS(std::vector<sdl::SMSMessage> &data)
{
    bool isAddressExisted = false;
    std::vector<sdl::SMSMessage> tmpVec;
    m_listOfAllSMS.clear();

    for(int i = 0; i < (int)data.size(); i++)
    {
        // First insert
        if(m_listOfAllSMS.size() == 0)
        {
            tmpVec.push_back(data[i]);
            m_listOfAllSMS.insert(std::pair<std::string, std::vector<sdl::SMSMessage>>(data[i].address_, tmpVec));
        }
        else
        {
            tmpVec.clear();
            for (auto iter = m_listOfAllSMS.begin(); iter != m_listOfAllSMS.end(); ++iter){
                // If the first object was existed
                if(iter->first == data[i].address_)
                {
                    tmpVec = iter->second;
                    tmpVec.push_back(data[i]);
                    iter->second = tmpVec;
                    isAddressExisted = true;
                    break;
                }
            }

            if(!isAddressExisted)
            {
                tmpVec.push_back(data[i]);
                m_listOfAllSMS.insert(std::pair<std::string, std::vector<sdl::SMSMessage>>(data[i].address_, tmpVec));
            }
            else
            {
                isAddressExisted = false;
            }
        }
    }
}

std::map<std::string, std::vector<sdl::SMSMessage> > &GuiPhoneDataModel::getListOfAllSMS()
{
    return m_listOfAllSMS;
}

QString GuiPhoneDataModel::convertTimestampToHumanDate(std::string timestamp)
{
    qint64 timestampNumber = QString::fromStdString(timestamp).toULongLong();// + 25200000; // 7000*3600 = 7hours in Msec
    return QDateTime::fromMSecsSinceEpoch(timestampNumber).toString("dddd-dd-MM-yyyy-HH:mm");
}
