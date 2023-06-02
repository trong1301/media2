// 2W include
#include "include/SystemClock.h"
#include "include/MagicNumbers.h"

// Qt include
#include <QDebug>

SystemClock::SystemClock(QObject* parent, std::shared_ptr<SettingHandler> settingHandler)
    : QObject(parent)
    , DUMMY_SET_7_GMT{0}
    , TIME_FORMAT_24H{"hh:mm"}
    , TIME_FORMAT_12H{"hh:mm AP"}
    , m_DateTime{QDateTime::currentDateTime().addSecs(DUMMY_SET_7_GMT)} // Workaround to set GMT+7
    , m_timeFormat(TIME_FORMAT_12H)
    , m_settingHandler(settingHandler)
{
    m_date = m_DateTime.date();
    m_time = m_DateTime.time();

    // Signal to change systemClock every sec
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &SystemClock::emitTimeChanged);
    m_timer->start();

    // Signal to change time format
    connect(m_settingHandler.get(), &SettingHandler::onTimeSettingChanged, this, &SystemClock::timeFormatChanged);
}

SystemClock::~SystemClock()
{
    disconnect(m_timer, &QTimer::timeout, this, nullptr);
    disconnect(m_settingHandler.get(), &SettingHandler::onTimeSettingChanged, this, nullptr);
}

QString SystemClock::getDate()
{
    m_date = m_DateTime.date();
    return m_date.toString();
}

QString SystemClock::getTime()
{
    m_time = m_DateTime.time();
    return m_time.toString(m_timeFormat);
}

void SystemClock::emitTimeChanged()
{
    // Workaround to set GMT+7
    m_DateTime = QDateTime::currentDateTime().addSecs(DUMMY_SET_7_GMT);

    // Avoid emit too much time
    if (m_date != m_DateTime.date()) {
        emit getDateChanged();
    }
    if(m_time.minute() != m_DateTime.time().minute()) {
        emit getTimeChanged();
    }
}

void SystemClock::timeFormatChanged()
{
    QString resultFormat{m_timeFormat};
    const int enumTimeFormat = m_settingHandler->getTimeSetting();
    using namespace TwoWheelsTypes;

    switch (enumTimeFormat)
    {
        case static_cast<int>(SettingTimes::FORMAT_12H): resultFormat = TIME_FORMAT_12H; break;
        case static_cast<int>(SettingTimes::FORMAT_24H): resultFormat = TIME_FORMAT_24H; break;
        default: break;
    }
    setTimeFormat(resultFormat);
}

void SystemClock::setTimeFormat(const QString& timeFormat)
{
    if(m_timeFormat == timeFormat)
        return;
    m_timeFormat = timeFormat;

    qDebug() << "Time format change to " << m_timeFormat;
    emit getTimeChanged();
}
