// 2W includes
#include "include/SettingHandler.h"

// Qt includes
#include "QDebug"

using namespace TwoWheelsTypes;

SettingHandler::SettingHandler(QObject* parent)
    : QObject(parent)
    , m_backgroundSetting(static_cast<int>(SettingBackGrounds::BG1))
    , m_timeSetting(static_cast<int>(SettingTimes::FORMAT_12H))
    , m_unitSetting(static_cast<int>(SettingUnits::KILOMETERS))
    , m_fontSetting(static_cast<int>(SettingFonts::FONT1))
    , m_themeSetting(static_cast<int>(SettingTheme::THEME1))
    , m_themeModel(std::make_shared<ThemeSettingModel>(nullptr))
{
}

int SettingHandler::getBackGroundSetting() const
{
    return m_backgroundSetting;
}

void SettingHandler::setBackGroundSetting(int bg)
{
    if (m_backgroundSetting == bg)
        return;

    if (static_cast<int>(SettingBackGrounds::NUM_OF_SETTING) > bg)
        m_backgroundSetting = bg;
    else
        m_backgroundSetting = static_cast<int>(SettingBackGrounds::BG1);

    emit onBackGroundSettingChanged();
}


int SettingHandler::getTimeSetting() const
{
    return m_timeSetting;
}

void SettingHandler::setTimeSetting(int time)
{
    if (m_timeSetting == time)
        return;

    if (static_cast<int>(SettingTimes::NUM_OF_SETTING) > time)
        m_timeSetting = time;
    else
        m_timeSetting = static_cast<int>(SettingTimes::FORMAT_12H);

    emit onTimeSettingChanged();
}

int SettingHandler::getUnitSetting() const
{
    return m_unitSetting;
}

void SettingHandler::setUnitSetting(int unit)
{
    if (m_unitSetting == unit)
        return;

    if (static_cast<int>(SettingUnits::NUM_OF_SETTING) > unit)
        m_unitSetting = unit;
    else
        m_unitSetting = static_cast<int>(SettingUnits::KILOMETERS);

    emit onUnitSettingChanged(m_unitSetting);
}

int SettingHandler::getFontSetting() const
{
    return m_fontSetting;
}

void SettingHandler::setFontSetting(int font)
{
    if (m_fontSetting == font)
        return;

    if (static_cast<int>(SettingFonts::NUM_OF_SETTING) > font)
        m_fontSetting = font;
    else
        m_fontSetting = static_cast<int>(SettingFonts::FONT1);

    emit onFontSettingChanged();
}

int SettingHandler::getThemeSetting() const
{
    return m_themeSetting;
}

void SettingHandler::setThemeSetting(int themeSetting)
{
    if (m_themeSetting == themeSetting)
        return;

    if (static_cast<int>(SettingTheme::NUM_OF_SETTING) > themeSetting)
        m_themeSetting = themeSetting;
    else
        m_themeSetting = static_cast<int>(SettingTheme::THEME1);

    emit themeSettingChanged();
    setTheme();
}

void SettingHandler::setTheme()
{
    switch(m_themeSetting)
    {
    case static_cast<int>(SettingTheme::THEME1):
        getThemeModel()->setTheme1();
        break;
    case static_cast<int>(SettingTheme::THEME2):
        getThemeModel()->setTheme2();
        break;
    case static_cast<int>(SettingTheme::THEME3):
        getThemeModel()->setTheme3();
        break;
    default: break;
    }
    emit onThemeModelChanged();
}

ThemeSettingModel *SettingHandler::getThemeModel() const
{
    return m_themeModel.get();
}
