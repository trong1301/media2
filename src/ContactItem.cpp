#include "include/ContactItem.h"

ContactItemModel::ContactItemModel(QObject *parent) : QObject(parent)
{

}

ContactItemModel::ContactItemModel(const QString &contactName, const QString &contactNumber, const QString &contactImage, QObject *parent):
    QObject(parent),m_contactName(contactName),m_contactNumber(contactNumber),m_contactImage(contactImage)
{

}

QString ContactItemModel::contactName() const
{
    return m_contactName;
}

QString ContactItemModel::contactNumber() const
{
    return m_contactNumber;
}

QString ContactItemModel::contactImage() const
{
    return m_contactImage;
}

void ContactItemModel::setContactName(QString contactName)
{
    if (m_contactName == contactName)
        return;

    m_contactName = contactName;
    emit contactNameChanged(m_contactName);
}

void ContactItemModel::setcontactNumber(QString contactNumber)
{
    if (m_contactNumber == contactNumber)
        return;

    m_contactNumber = contactNumber;
    emit contactNumberChanged(m_contactNumber);
}

void ContactItemModel::setcontactImage(QString contactImage)
{
    if (m_contactImage == contactImage)
        return;

    m_contactImage = contactImage;
    emit contactImageChanged(m_contactImage);
}
