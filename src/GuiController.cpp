// Qt include
#include "QDebug"
#include <QTimer>

// C++ include
#include <cstdint>

// 2W include
#include "include/GuiController.h"
#include "include/Log.h"

using namespace Helper::MagicNumbers;

namespace sdl {

GuiController::GuiController(QObject* parent, std::shared_ptr<SettingHandler> settingHandler)
    : QObject(parent)
    , m_settingHandler(settingHandler)
{
    auto m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
#ifdef NATIVE_BUILD
    m_timer->setInterval(5000);
#else
    m_timer->setInterval(100);
#endif
    connect(m_timer, &QTimer::timeout, this, &GuiController::dummyRandomData);
    m_timer->start();

    setIndicators("turnLeft", "qrc:/images/ICN_SICON_SIGNALLEFT.png", DISPLAY_BOTH_SCREENS);
    setIndicators("sideStand", "qrc:/images/ICN_SICON_SIDESTAND_1.png", DISPLAY_BOTH_SCREENS);
    setIndicators("reverse_mode", "qrc:/images/ICN_SICON_REVERSE_SPEED.png", DISPLAY_ONE_SCREEN);
    setIndicators("headLight", "qrc:/images/ICN_SICON_HEADLIGHT.png", DISPLAY_BOTH_SCREENS);
    setIndicators("engineTrouble", "qrc:/images/ICN_SICON_ENGINETROUBLE.png", DISPLAY_ONE_SCREEN);
    setIndicators("oil", "qrc:/images/ICN_SICON_OILLOWER.png", DISPLAY_ONE_SCREEN);
    setIndicators("coolLant", "qrc:/images/ICN_SICON_COOLANTTEMP.png", DISPLAY_ONE_SCREEN);
    setIndicators("abs", "qrc:/images/ICN_SICON_BRAKE.png", DISPLAY_ONE_SCREEN);
    setIndicators("turnRight", "qrc:/images/ICN_SICON_SIGNALRIGHT.png", DISPLAY_BOTH_SCREENS);
}

GuiController::~GuiController()
{
    shutdown();
}

void GuiController::init(void)
{
}

TwoWheelsTypes::Speedo GuiController::getSpeedDataStructure()
{
    return mSpeedo;
}

TwoWheelsTypes::Battery GuiController::getBatteryDataStructure()
{
    return mBattery;
}

TwoWheelsTypes::Indicators GuiController::getIndicatorDataStructure()
{
    return mIndicators;
}

QList<IndicatorIcon *> GuiController::getIndicatorList()
{
    return m_indicatorIconList;
}

std::shared_ptr<SettingHandler> GuiController::getSettingHandler() const
{
    return m_settingHandler;
}

//int GuiController::randomSeed(int number)
//{
//    srand(time(nullptr));
//    int randomData = qrand() % number + 1;
//    return randomData;
//}

void GuiController::dummyRandomData()
{
    m_isSideStandDown = true;
    m_isBrakeActive = true;
    m_isReversedSpeed = false;
    m_isPositionSensorFault = true;
    m_speedStatus = 0;

    m_speedStructure.speed = 7;
    m_speedStructure.mileage = 77;
    mBattery.voltage = 27;
    mBattery.soc_display = 7;

    switch(m_speedStatus){
    case 0:m_speedStatusString = "Neutral";break;
    case 1:m_speedStatusString = "Low speed";break;
    case 2:m_speedStatusString = "Medium speed";break;
    case 3:m_speedStatusString = "High speed";break;
    default: m_speedStatusString = "";break;
    }

    if(m_isReversedSpeed)
    {
        m_speedStatusString = "Reverse";
    }

    m_speedStructure.speed_status = m_speedStatusString;

    TwoWheelsTypes::Indicators indicators;
    /* Get from GPIO
    * indicators.turn_left
    * indicators.head_light
    * indicators.turn_right
    */
    indicators.side_stand = m_isSideStandDown;
    indicators.reverse_mode = m_isReversedSpeed;
    indicators.engine_trouble = m_isPositionSensorFault;
    //    indicators.oil_lower = randomSeed(15);
    //    indicators.coolant_tempt = randomSeed(16);
    indicators.abs = m_isBrakeActive;  // temporary use abs variable -> need change to brake
    setIndicatorsDataStructure(indicators);
    setSpeedDataStructure(m_speedStructure);
    setBatteryDataStructure(mBattery);
}

void GuiController::setIndicators(const QString& name, const QString& img, const bool& isDisplayBothScreens)
{
    IndicatorIcon* item = new IndicatorIcon();
    item->setNameIcon(name);
    item->setImageSource(img);
    item->setVisible(true);
    item->setStateIcon("Inactive");
    item->setColorShadowBorderBgIcon(COLOR_SHADOW_BORDER_BG_ICON);
    item->setColorBorderBgIconActive(COLOR_BORDER_BG_ICON);
    item->setColorBorderBgIconInactive(COLOR_BORDER_BG_ICON);
    if(isDisplayBothScreens)
    {
        item->setColorBgIconActive(COLOR_BG_ICON_ACTIVE1);
        item->setColorBgIconInactive(COLOR_BG_ICON_INACTIVE1);
    }
    else
    {
        item->setColorBgIconActive(COLOR_BG_ICON_ACTIVE2);
        item->setColorBgIconInactive(COLOR_BG_ICON_INACTIVE2);
    }
    m_indicatorIconList.append(item);
}

void GuiController::setSpeedDataStructure(TwoWheelsTypes::Speedo& spdo)
{
    mSpeedo = spdo;
    emit onSpeedDataStructureChanged(mSpeedo);
}

void GuiController::setBatteryDataStructure(TwoWheelsTypes::Battery& bat)
{
    mBattery = bat;
    emit onBatteryDataStructureChanged(mBattery);
}

void GuiController::setIndicatorsDataStructure(TwoWheelsTypes::Indicators& indctor)
{
    mIndicators = indctor;
    emit onIndicatorsDataStructureChanged(mIndicators);
}

void GuiController::shutdown(void) {

}
}
