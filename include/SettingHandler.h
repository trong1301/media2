#ifndef SETTINGHANDLER_H
#define SETTINGHANDLER_H

// 2W includes
#include "MagicNumbers.h"
#include "ThemeSettingModel.h"

// C++ includes
#include <memory>

// Qt includes
#include <QObject>

class SettingHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int backgroundSetting READ getBackGroundSetting WRITE setBackGroundSetting NOTIFY onBackGroundSettingChanged)
    Q_PROPERTY(int timeSetting READ getTimeSetting WRITE setTimeSetting NOTIFY onTimeSettingChanged)
    Q_PROPERTY(int unitSetting READ getUnitSetting WRITE setUnitSetting NOTIFY onUnitSettingChanged)
    Q_PROPERTY(int fontSetting READ getFontSetting WRITE setFontSetting NOTIFY onFontSettingChanged)
    Q_PROPERTY(int themeSetting READ getThemeSetting WRITE setThemeSetting NOTIFY themeSettingChanged)
    Q_PROPERTY(ThemeSettingModel* themeModel READ getThemeModel NOTIFY onThemeModelChanged)
public:
    //!
    //! \brief SettingHandler
    //! \param parent
    //!
    SettingHandler(QObject* parent = nullptr);

    //!
    //! \brief getBackGround
    //! \return
    //!
    int getBackGroundSetting() const;

    //!
    //! \brief setBackGround
    //! \param bg
    //!
    void setBackGroundSetting(int bg);

    //!
    //! \brief getTimeSetting
    //! \return
    //!
    int getTimeSetting() const;

    //!
    //! \brief setTimeSetting
    //! \param time
    //!
    void setTimeSetting(int time);

    //!
    //! \brief getUnitSetting
    //! \return
    //!
    int getUnitSetting() const;

    //!
    //! \brief setUnitSetting
    //! \param unit
    //!
    void setUnitSetting(int unit);

    //!
    //! \brief getFontSetting
    //! \return
    //!
    int getFontSetting() const;

    //!
    //! \brief setFontSetting
    //! \param font
    //!
    void setFontSetting(int font);

    //!
    //! \brief getThemeModel
    //! \return
    //!
    ThemeSettingModel* getThemeModel() const;

    //!
    //! \brief getThemeSetting
    //! \return
    //!
    int getThemeSetting() const;

    //!
    //! \brief setThemeSetting
    //! \param themeSetting
    //!
    void setThemeSetting(int themeSetting);

    //!
    //! \brief setTheme
    //!
    void setTheme();

signals:
    //!
    //! \brief onBackGroundChanged
    //!
    void onBackGroundSettingChanged();

    //!
    //! \brief onTimeSettingChanged
    //!
    void onTimeSettingChanged();

    //!
    //! \brief onUnitSettingChanged
    //!
    void onUnitSettingChanged(const int& unitSetting);

    //!
    //! \brief onFontSettingChanged
    //! \param fontSetting
    //!
    void onFontSettingChanged();

    //!
    //! \brief onThemeModelChanged
    //!
    void onThemeModelChanged();

    //!
    //! \brief themeSettingChanged
    //!
    void themeSettingChanged();

private:
    int m_backgroundSetting;
    int m_timeSetting;
    int m_unitSetting;
    int m_fontSetting;
    int m_themeSetting;

    std::shared_ptr<ThemeSettingModel> m_themeModel;
};

#endif // SETTINGHANDLER_H
