#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H

// 2W include
#include "SettingHandler.h"

// C++ include
#include <memory>

// Qt include
#include <QDateTime>
#include <QObject>
#include <QString>
#include <QTimer>

//!
//! \brief The SystemClock class expose system clock to qml every sec
//!
class SystemClock : public QObject {

    Q_OBJECT

    //!
    //! \brief Expose the m_date member to qml
    //!
    Q_PROPERTY(QString date READ getDate NOTIFY getDateChanged)

    //!
    //! \brief Expose the m_time member to qml
    //!
    Q_PROPERTY(QString time READ getTime NOTIFY getTimeChanged)

public:
    //!
    //! \brief SystemClock
    //! \param parent
    //!
    explicit SystemClock(QObject* parent = nullptr, std::shared_ptr<SettingHandler> settingHandler = nullptr);
    ~SystemClock();

    //!
    //! \brief getDate()
    //!
    QString getDate();

    //!
    //! \brief getTime()
    //!
    QString getTime();

public slots:
    //!
    //! \brief emitTimeChanged() signal to emit other signals
    //!
    void emitTimeChanged();

    //!
    //! \brief timeFormatChanged() signal
    //!
    void timeFormatChanged();

signals:
    //!
    //! \brief Emit this signal in order to inform QML about changes
    //!
    QString getDateChanged();

    //!
    //! \brief Emit this signal in order to inform QML about changes
    //!
    QString getTimeChanged();

private:
    //!
    //! \brief DUMMY_SET_7_GMT const uint16_t
    //!
    const uint16_t DUMMY_SET_7_GMT;

    //!
    //! \brief TIME_FORMAT_24H const string
    //!
    const QString TIME_FORMAT_24H;

    //!
    //! \brief TIME_FORMAT_24H const string
    //!
    const QString TIME_FORMAT_12H;

    //!
    //! \brief m_date stores the date
    //!
    QDate m_date;

    //!
    //! \brief m_DateTime stores the date and time
    //!
    QDateTime m_DateTime;

    //!
    //! \brief m_time stores the time
    //!
    QTime m_time;

    //!
    //! \brief m_timer stores the timer to trigger every sec
    //!
    QTimer* m_timer;

    //!
    //! \brief m_timeFormat
    //!
    QString m_timeFormat;

    //!
    //! \brief m_settingHandler
    //!
    std::shared_ptr<SettingHandler> m_settingHandler;

private:
    //!
    //! \brief setTimeFormat
    //! \param timeFormat
    //!
    void setTimeFormat(const QString& timeFormat);
};

#endif // SYSTEMCLOCK_H
