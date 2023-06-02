#ifndef SMSCONTENT_H
#define SMSCONTENT_H

// Qt includes
#include <QObject>
#include <QVector>

class SmsContent: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address NOTIFY addressChanged)
    Q_PROPERTY(QString body READ body NOTIFY bodyChanged)
    Q_PROPERTY(QString date READ date NOTIFY dateChanged)
    Q_PROPERTY(int read READ read NOTIFY readChanged)
    Q_PROPERTY(int type READ type NOTIFY typeChanged)
public:
    explicit SmsContent(QObject *parent = nullptr);
    QString address() const;
    QString body() const;
    QString date() const;
    uint32_t read() const;
    uint32_t type() const;

    void setAddress(const QString &address);
    void setBody(const QString &body);
    void setDate(const QString &date);
    void setRead(const uint32_t &read);
    void setType(const uint32_t &type);

signals:
    void addressChanged();
    void bodyChanged();
    void dateChanged();
    void readChanged();
    void typeChanged();

private:
    QString m_address;
    QString m_body;
    QString m_date;
    uint32_t m_read;
    uint32_t m_type;
    explicit SmsContent(const SmsContent& rhs) = delete;
    SmsContent& operator = (const SmsContent& rhs) = delete;
};

#endif // SMSCONTENT_H
