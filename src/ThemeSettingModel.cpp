// 2W includes
#include "include/ThemeSettingModel.h"

// Qt includes
#include <QDebug>

ThemeSettingModel::ThemeSettingModel(QObject *parent) : QObject(parent)
{
    setTheme1();
    setAppIconTheme(static_cast<int>(APP_ICON_THEMES::ICON_THEME1));

}

void ThemeSettingModel::setThemeSettingModel(const QString &themeName,
                                             const QString &background,
                                             const QString &systemTextColor,
                                             const QString &appTextColor,
                                             const QStringList &settingListColorModel,
                                             const QStringList &smsColorModel,
                                             const QString &appBackground,
                                             const int &appIconTheme)
{
    m_themeName = themeName;
    m_background = background;
    m_systemTextColor = systemTextColor;
    m_appTextColor = appTextColor;
    m_settingListColorModel = settingListColorModel;
    m_smsColorModel = smsColorModel;
    m_appBackGround = appBackground;
    m_appIconTheme = appIconTheme;
}

QString ThemeSettingModel::getThemeName() const
{
    return m_themeName;
}

QString ThemeSettingModel::getBackground() const
{
    return m_background;
}

QString ThemeSettingModel::getSystemTextColor() const
{
    return m_systemTextColor;
}

QString ThemeSettingModel::getAppTextColor() const
{
    return m_appTextColor;
}

QStringList ThemeSettingModel::getSettingListColorModel() const
{
    return m_settingListColorModel;
}

QStringList ThemeSettingModel::getSmsColorModel() const
{
    return m_smsColorModel;
}

QString ThemeSettingModel::getAppBackGround() const
{
    return m_appBackGround;
}

void ThemeSettingModel::setThemeName(const QString& themeName)
{
    if (m_themeName == themeName)
        return;

    m_themeName = themeName;
    emit themeNameChanged();
}

void ThemeSettingModel::setBackground(const QString& background)
{
    if (m_background == background)
        return;

    m_background = background;
    emit backgroundChanged();
}

void ThemeSettingModel::setSystemTextColor(const QString& systemTextColor)
{
    if (m_systemTextColor == systemTextColor)
        return;

    m_systemTextColor = systemTextColor;
    emit systemTextColorChanged();
}

void ThemeSettingModel::setAppTextColor(const QString& appTextColor)
{
    if (m_appTextColor == appTextColor)
        return;

    m_appTextColor = appTextColor;
    emit appTextColorChanged();
}

void ThemeSettingModel::setSettingListColorModel(const QStringList& settingListColorModel)
{
    m_settingListColorModel.clear();
    if (m_settingListColorModel == settingListColorModel)
        return;

    m_settingListColorModel = settingListColorModel;
    emit settingListColorModelChanged();
}

void ThemeSettingModel::setSmsColorModel(const QStringList& smsColorModel)
{
    m_smsColorModel.clear();
    if (m_smsColorModel == smsColorModel)
        return;

    m_smsColorModel = smsColorModel;
    emit smsColorModelChanged();
}

void ThemeSettingModel::setAppBackGround(const QString& appBackGround)
{
    if (m_appBackGround == appBackGround)
        return;

    m_appBackGround = appBackGround;
    emit appBackGroundChanged();
}


int ThemeSettingModel::getAppIconTheme() const
{
    return m_appIconTheme;
}

void ThemeSettingModel::setAppIconTheme(int appIconTheme)
{
    if (appIconTheme == m_appIconTheme)
        return;
    if (appIconTheme < static_cast<int>(APP_ICON_THEMES::NUM_OF_ICON_THEME))
    {
        m_appIconTheme = appIconTheme;
    } else {
        m_appIconTheme = static_cast<int>(APP_ICON_THEMES::ICON_THEME1);
    }
    emit appIconThemeChanged();
}

void ThemeSettingModel::setTheme1()
{
    QString settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::NUM_OF_ITEMS)];
    QStringList settingListColorsList;
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::LEFT_TEXT)] ="#FFFFFF";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::RIGHT_TEXT_INSIDE_BOX)] ="#000000";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::RIGHT_BOX)] ="#B5E39F";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::SPLIT_LINE)] ="#000000";

    for (auto iter : settingListColorsArr) {
        settingListColorsList.push_back(iter);
    }

    QString smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::NUM_OF_ITEMS)];
    QStringList smsColorList;
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_LEFT_BOX)] ="#B5E39F";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_LEFT_TEXT)] ="#000000";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_RIGHT_BOX)] ="#FFFFFF";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_RIGHT_TEXT)] ="#000000";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_DATE)] ="#FFFFFF";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::PRESS_ITEM)] ="#79A2A1";
    for (auto iter : smsColorModelArr) {
        smsColorList << iter;
    }

    setThemeName("Theme 1");
    setBackground("qrc:/images/background2"); // Not support yet
    setSystemTextColor("#FFFFFF");
    setAppTextColor("#FFFFFF");
    setAppBackGround("#3B9EA8C1");
    setSettingListColorModel(settingListColorsList);
    setSmsColorModel(smsColorList);
    setAppIconTheme(static_cast<int>(APP_ICON_THEMES::ICON_THEME1));

}

void ThemeSettingModel::setTheme2()
{
    QString settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::NUM_OF_ITEMS)];
    QStringList settingListColorsList;
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::LEFT_TEXT)] ="#FFFFFF";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::RIGHT_TEXT_INSIDE_BOX)] ="#000000";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::RIGHT_BOX)] ="#FFE5E5";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::SPLIT_LINE)] ="#FFFFFF";

    for (auto iter : settingListColorsArr) {
        settingListColorsList << iter;
    }

    QString smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::NUM_OF_ITEMS)];
    QStringList smsColorList;
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_LEFT_BOX)] ="#FFE5E5";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_LEFT_TEXT)] ="#000000";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_RIGHT_BOX)] ="#FFFFFF";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_RIGHT_TEXT)] ="#000000";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_DATE)] ="#FFFFFF";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::PRESS_ITEM)] ="#79A2A1";

    for (auto iter : smsColorModelArr) {
        smsColorList << iter;
    }

    setThemeName("Theme 2");
    setBackground("qrc:/images/road"); // Not support yet
    setSystemTextColor("#FFFFFF");
    setAppTextColor("#FFFFFF");
    setAppBackGround("#3B9EA8C1");
    setSettingListColorModel(settingListColorsList);
    setSmsColorModel(smsColorList);
    setAppIconTheme(static_cast<int>(APP_ICON_THEMES::ICON_THEME2));
}

void ThemeSettingModel::setTheme3()
{
    QString settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::NUM_OF_ITEMS)];
    QStringList settingListColorsList;
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::LEFT_TEXT)] ="#FFFFFF";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::RIGHT_TEXT_INSIDE_BOX)] ="#000000";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::RIGHT_BOX)] ="#9ADEF5";
    settingListColorsArr[static_cast<int>(SETTING_LIST_COLOR_ITEMS::SPLIT_LINE)] ="#808080";

    for (auto iter : settingListColorsArr) {
        settingListColorsList << iter;
    }

    QString smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::NUM_OF_ITEMS)];
    QStringList smsColorList;
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_LEFT_BOX)] ="#9ADEF5";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_LEFT_TEXT)] ="#000000";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_RIGHT_BOX)] ="#FFFFFF";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_RIGHT_TEXT)] ="#000000";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::CONTENT_DATE)] ="#FFFFFF";
    smsColorModelArr[static_cast<int>(SMS_COLOR_ITEMS::PRESS_ITEM)] ="#79A2A1";

    for (auto iter : smsColorModelArr) {
        smsColorList << iter;
    }

    setThemeName("Theme 3");
    setBackground(""); // Not support yet
    setSystemTextColor("#FFFFFF");
    setAppTextColor("#FFFFFF");
    setAppBackGround("#7F0C375A");
    setSettingListColorModel(settingListColorsList);
    setSmsColorModel(smsColorList);
    setAppIconTheme(static_cast<int>(APP_ICON_THEMES::ICON_THEME1));
}

