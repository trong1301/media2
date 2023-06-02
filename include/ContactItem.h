#ifndef CONTACTITEM_H
#define CONTACTITEM_H

#include <QObject>

class ContactItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString contactName READ contactName WRITE setContactName NOTIFY contactNameChanged)
    Q_PROPERTY(QString contactNumber READ contactNumber WRITE setcontactNumber NOTIFY contactNumberChanged)
    Q_PROPERTY(QString contactImage READ contactImage WRITE setcontactImage NOTIFY contactImageChanged)

public:
    explicit ContactItemModel(QObject *parent = nullptr);
    ContactItemModel(const QString &contactName, const QString &contactNumber, const QString &contactImage, QObject * parent = nullptr);

    QString contactName() const;
    QString contactNumber() const;
    QString contactImage() const;
    void setContactName(QString contactName);
    void setcontactNumber(QString contactNumber);
    void setcontactImage(QString contactImage);

signals:
    void contactNameChanged(QString contactName);
    void contactNumberChanged(QString contactNumber);
    void contactImageChanged(QString contactImage);

private:
    QString m_contactName;
    QString m_contactNumber;
    QString m_contactImage;
};

#endif // CONTACTITEM_H
