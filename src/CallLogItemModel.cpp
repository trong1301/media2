#include "include/CallLogItemModel.h"

CallLogItemModel::CallLogItemModel(QObject *parent) : QObject(parent)
{

}

QString CallLogItemModel::getCallLogName() const
{
    return m_callLogName;
}

QString CallLogItemModel::getCallLogNumber() const
{
    return m_callLogNumber;
}

QString CallLogItemModel::getCallLogDate() const
{
    return m_callLogDate;
}

QString CallLogItemModel::getCallLogDuration() const
{
    return m_callLogDuration;
}

int CallLogItemModel::getCallLogType() const
{
    return m_callLogType;
}

void CallLogItemModel::setCallLogName(QString callLogName)
{
    if (m_callLogName == callLogName)
        return;

    m_callLogName = callLogName;
    emit callLogNameChanged(m_callLogName);
}

void CallLogItemModel::setCallLogNumber(QString callLogNumber)
{
    if (m_callLogNumber == callLogNumber)
        return;

    m_callLogNumber = callLogNumber;
    emit callLogNumberChanged(m_callLogNumber);
}

void CallLogItemModel::setCallLogDate(QString callLogDate)
{
    if (m_callLogDate == callLogDate)
        return;

    m_callLogDate = callLogDate;
    emit callLogDateChanged(m_callLogDate);
}

void CallLogItemModel::setCallLogDuration(QString callLogDuration)
{
    if (m_callLogDuration == callLogDuration)
        return;

    m_callLogDuration = callLogDuration;
    emit callLogDurationChanged(m_callLogDuration);
}

void CallLogItemModel::setCallLogType(int callLogType)
{
    if (m_callLogType == callLogType)
        return;

    m_callLogType = callLogType;
    emit callLogTypeChanged(m_callLogType);
}

