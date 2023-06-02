// 2W includes
#include "include/Speedometer.h"

// Qt includes
#include <QDebug>

Speedometer::Speedometer(QObject* parent, std::shared_ptr<sdl::GuiController> guiCtrl)
    : QObject(parent)
    , KM_TO_MILE_RATIO(0.621371)
    , m_speed(0)
    , m_guiController(guiCtrl)
    , m_mileAge(0)
    , m_speedUnit(static_cast<int>(TwoWheelsTypes::SettingUnits::KILOMETERS))
    , m_settingHandler{m_guiController->getSettingHandler()}
{
    connect(m_guiController.get(), &sdl::GuiController::onSpeedDataStructureChanged, this, [&](const TwoWheelsTypes::Speedo& speedoModel) {
        m_speedo = speedoModel;
        switch(m_speedUnit)
        {
        case static_cast<int>(TwoWheelsTypes::SettingUnits::KILOMETERS):
            setSpeed(m_speedo.speed);
            break;
        case static_cast<int>(TwoWheelsTypes::SettingUnits::MILES):
            setSpeed(m_speedo.speed * KM_TO_MILE_RATIO);
            break;
        default: break;
        }
        setMileAge(m_speedo.mileage);
        setSpeedStatus(m_speedo.speed_status);
    });

    connect(m_settingHandler.get(), &SettingHandler::onUnitSettingChanged, this, [&](const int& unitSetting)
    {
        setSpeedUnit(unitSetting);
        switch(m_speedUnit)
        {
        case static_cast<int>(TwoWheelsTypes::SettingUnits::KILOMETERS):
            setSpeed(m_speedo.speed);
            break;
        case static_cast<int>(TwoWheelsTypes::SettingUnits::MILES):
            setSpeed(m_speedo.speed * KM_TO_MILE_RATIO);
            break;
        default: break;
        }
    });
}

Speedometer::~Speedometer()
{
    disconnect(m_guiController.get(), &sdl::GuiController::onSpeedDataStructureChanged, this, nullptr);
    disconnect(m_settingHandler.get(), &SettingHandler::onUnitSettingChanged, this, nullptr);
}

int Speedometer::speed() const
{
    return m_speed;
}

float Speedometer::getMileAge() const
{
    return m_mileAge;
}

QString Speedometer::getSpeedStatus() const
{
    return m_speedStatus;
}

void Speedometer::setSpeed(const float& newSpeed)
{
    if (m_speed == newSpeed)
        return;
    m_speed = newSpeed;
    emit speedChanged();
}

void Speedometer::setMileAge(const float &mileAge)
{
    if (m_mileAge == mileAge)
        return;
    m_mileAge = mileAge;
    emit mileAgeChanged();
}

void Speedometer::setSpeedUnit(const int &speedUnit)
{
    if (m_speedUnit == speedUnit)
        return;
    m_speedUnit = speedUnit;
}

void Speedometer::setSpeedStatus(const QString &speedStatus)
{
    if(m_speedStatus == speedStatus)
        return;

    m_speedStatus = speedStatus;
    emit speedStatusChanged();
}
