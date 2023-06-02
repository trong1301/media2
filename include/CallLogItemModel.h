#ifndef CALLLOGITEMMODEL_H
#define CALLLOGITEMMODEL_H

// Qt include
#include <QObject>

class CallLogItemModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString callLogName READ getCallLogName WRITE setCallLogName NOTIFY callLogNameChanged)
    Q_PROPERTY(QString callLogNumber READ getCallLogNumber WRITE setCallLogNumber NOTIFY callLogNumberChanged)
    Q_PROPERTY(QString callLogDate READ getCallLogDate WRITE setCallLogDate NOTIFY callLogDateChanged)
    Q_PROPERTY(QString callLogDuration READ getCallLogDuration WRITE setCallLogDuration NOTIFY callLogDurationChanged)
    Q_PROPERTY(int callLogType READ getCallLogType WRITE setCallLogType NOTIFY callLogTypeChanged)

public:
    //!
    //! \brief CallLogItem
    //! \param parent
    //!
    explicit CallLogItemModel(QObject *parent = nullptr);

    //!
    //! \brief getCallLogName
    //! \return
    //!
    QString getCallLogName() const;

    //!
    //! \brief getCallLogNumber
    //! \return
    //!
    QString getCallLogNumber() const;

    //!
    //! \brief getCallLogDate
    //! \return
    //!
    QString getCallLogDate() const;

    //!
    //! \brief getCallLogDuration
    //! \return
    //!
    QString getCallLogDuration() const;

    //!
    //! \brief getCallLogType
    //! \return
    //!
    int getCallLogType() const;

public slots:
    //!
    //! \brief setCallLogName
    //! \param callLogName
    //!
    void setCallLogName(QString callLogName);

    //!
    //! \brief setCallLogNumber
    //! \param callLogNumber
    //!
    void setCallLogNumber(QString callLogNumber);

    //!
    //! \brief setCallLogDate
    //! \param callLogDate
    //!
    void setCallLogDate(QString callLogDate);

    //!
    //! \brief setCallLogDuration
    //! \param callLogDuration
    //!
    void setCallLogDuration(QString callLogDuration);

    //!
    //! \brief setCallLogType
    //! \param callLogType
    //!
    void setCallLogType(int callLogType);

signals:
    //!
    //! \brief callLogNameChanged
    //! \param callLogName
    //!
    void callLogNameChanged(QString callLogName);

    //!
    //! \brief callLogNumberChanged
    //! \param callLogNumber
    //!
    void callLogNumberChanged(QString callLogNumber);

    //!
    //! \brief callLogDateChanged
    //! \param callLogDate
    //!
    void callLogDateChanged(QString callLogDate);

    //!
    //! \brief callLogDurationChanged
    //! \param callLogDuration
    //!
    void callLogDurationChanged(QString callLogDuration);

    //!
    //! \brief callLogTypeChanged
    //! \param callLogType
    //!
    void callLogTypeChanged(int callLogType);

private:
    //!
    //! \brief m_callLogName
    //!
    QString m_callLogName;

    //!
    //! \brief m_callLogNumber
    //!
    QString m_callLogNumber;

    //!
    //! \brief m_callLogDate
    //!
    QString m_callLogDate;

    //!
    //! \brief m_callLogDuration
    //!
    QString m_callLogDuration;

    //!
    //! \brief m_callLogType
    //!
    int m_callLogType;
};

#endif // CALLLOGITEMMODEL_H
