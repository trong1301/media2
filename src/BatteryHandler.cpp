#include "include/BatteryHandler.h"
#include <QDebug>
#include <QTimer>

BatteryHandler::BatteryHandler(QObject* parent, std::shared_ptr<sdl::GuiController> guiCtrl)
    : QObject(parent)
    , m_batteryLevel(0)
    , m_guiController(guiCtrl)
{
    connect(m_guiController.get(), &sdl::GuiController::onBatteryDataStructureChanged, this, [&](const TwoWheelsTypes::Battery& batteryModel){
        m_batteryLevel = batteryModel.voltage;
        setBatteryLevel(m_batteryLevel);
    });
}

BatteryHandler::~BatteryHandler()
{
    disconnect(m_guiController.get(), &sdl::GuiController::onBatteryDataStructureChanged, this, nullptr);
}

void BatteryHandler::setBatteryLevel(int pinLevel)
{
    m_batteryLevel = pinLevel;
    emit batteryLevelChanged();
}

int BatteryHandler::getBatteryLevel()
{
    return m_batteryLevel;
}
