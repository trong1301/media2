#include "include/Smscontent.h"

SmsContent::SmsContent(QObject *parent)
    : QObject{parent}
    , m_address("123456")
    ,m_body("content of message")
    ,m_date("2022-02-10")
    ,m_read(1)
    ,m_type(1)
{

}

QString SmsContent::address() const
{
    return m_address;
}

void SmsContent::setAddress(const QString &address)
{
    m_address = address;
    emit addressChanged();
}

QString SmsContent::body() const
{
    return m_body;
}

void SmsContent::setBody(const QString &body)
{
    m_body = body;
    emit bodyChanged();
}

QString SmsContent::date() const
{
    return m_date;
}

void SmsContent::setDate(const QString &date)
{
    m_date = date;
    emit dateChanged();
}

uint32_t SmsContent::read() const
{
    return m_read;
}

void SmsContent::setRead(const uint32_t &read)
{
    m_read = read;
    emit readChanged();
}

uint32_t SmsContent::type() const
{
    return m_type;
}

void SmsContent::setType(const uint32_t &type)
{
    m_type = type;
    emit typeChanged();
}

