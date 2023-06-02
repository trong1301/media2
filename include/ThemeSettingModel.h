#ifndef THEMESETTINGMODEL_H
#define THEMESETTINGMODEL_H

// Qt includes
#include <QObject>
#include <QVector>
#include <QString>

class ThemeSettingModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString themeName READ getThemeName NOTIFY themeNameChanged)
    Q_PROPERTY(QString background READ getBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QString systemTextColor READ getSystemTextColor NOTIFY systemTextColorChanged)
    Q_PROPERTY(QString appTextColor READ getAppTextColor NOTIFY appTextColorChanged)
    Q_PROPERTY(QStringList settingListColorModel READ getSettingListColorModel NOTIFY settingListColorModelChanged)
    Q_PROPERTY(QStringList smsColorModel READ getSmsColorModel NOTIFY smsColorModelChanged)
    Q_PROPERTY(QString appBackGround READ getAppBackGround NOTIFY appBackGroundChanged)
    Q_PROPERTY(int appIconTheme READ getAppIconTheme WRITE setAppIconTheme NOTIFY appIconThemeChanged)

public:
    explicit ThemeSettingModel(QObject *parent = nullptr);

    //!
    //! \brief setThemeSettingModel
    //! \param themeName
    //! \param background
    //! \param systemTextColor
    //! \param appTextColor
    //! \param settingListColorModel
    //! \param smsColorModel
    //! \param appBackground
    //!
    void setThemeSettingModel(const QString& themeName,
                              const QString& background,
                              const QString& systemTextColor,
                              const QString& appTextColor,
                              const QStringList& settingListColorModel,
                              const QStringList& smsColorModel,
                              const QString& appBackground,
                              const int& appIconTheme);

    //!
    //! \brief getThemeName
    //! \return
    //!
    QString getThemeName() const;

    //!
    //! \brief getBackground
    //! \return
    //!
    QString getBackground() const;

    //!
    //! \brief getSystemTextColor
    //! \return
    //!
    QString getSystemTextColor() const;

    //!
    //! \brief getAppTextColor
    //! \return
    //!
    QString getAppTextColor() const;

    //!
    //! \brief getSettingListColorModel
    //! \return
    //!
    QStringList getSettingListColorModel() const;

    //!
    //! \brief getSmsColorModel
    //! \return
    //!
    QStringList getSmsColorModel() const;

    //!
    //! \brief getAppBackGround
    //! \return
    //!
    QString getAppBackGround() const;

    //!
    //! \brief setThemeName
    //! \param themeName
    //!
    void setThemeName(const QString& themeName);

    //!
    //! \brief setBackground
    //! \param background
    //!
    void setBackground(const QString& background);

    //!
    //! \brief setSystemTextColor
    //! \param systemTextColor
    //!
    void setSystemTextColor(const QString& systemTextColor);

    //!
    //! \brief setAppTextColor
    //! \param appTextColor
    //!
    void setAppTextColor(const QString& appTextColor);

    //!
    //! \brief setSettingListColorModel
    //! \param settingListColorModel
    //!
    void setSettingListColorModel(const QStringList& settingListColorModel);

    //!
    //! \brief setSmsColorModel
    //! \param smsColorModel
    //!
    void setSmsColorModel(const QStringList& smsColorModel);

    //!
    //! \brief setAppBackGround
    //! \param appBackGround
    //!
    void setAppBackGround(const QString& appBackGround);

    // TODO: Temporary, need to be loaded from config files
    //!
    //! \brief setTheme1
    //!
    void setTheme1();

    //!
    //! \brief setTheme2
    //!
    void setTheme2();

    //!
    //! \brief setTheme3
    //!
    void setTheme3();

    int getAppIconTheme() const;
    void setAppIconTheme(int appIconTheme);

signals:

    //!
    //! \brief themeNameChanged
    //! \param themeName
    //!
    void themeNameChanged();

    //!
    //! \brief backgroundChanged
    //!
    void backgroundChanged();

    //!
    //! \brief systemTextColorChanged
    //!
    void systemTextColorChanged();

    //!
    //! \brief appTextColorChanged
    //!
    void appTextColorChanged();

    //!
    //! \brief settingListColorModelChanged
    //!
    void settingListColorModelChanged();

    //!
    //! \brief smsColorModelChanged
    //!
    void smsColorModelChanged();

    //!
    //! \brief appBackGroundChanged
    //!
    void appBackGroundChanged();

    //!
    //! \brief appIconThemeChanged
    //!
    void appIconThemeChanged();

private:

    enum class SETTING_LIST_COLOR_ITEMS{
        LEFT_TEXT = 0,
        RIGHT_TEXT_INSIDE_BOX,
        RIGHT_BOX,
        SPLIT_LINE,
        NUM_OF_ITEMS = 4
    };

    enum class SMS_COLOR_ITEMS{
        CONTENT_LEFT_BOX = 0,
        CONTENT_LEFT_TEXT,
        CONTENT_RIGHT_BOX,
        CONTENT_RIGHT_TEXT,
        CONTENT_DATE,
        PRESS_ITEM,
        NUM_OF_ITEMS = 6
    };

    enum class APP_ICON_THEMES {
        ICON_THEME1 = 0,
        ICON_THEME2,
        NUM_OF_ICON_THEME = 2
    };

    //!
    //! \brief m_themeName
    //!
    QString m_themeName;

    //!
    //! \brief m_background
    //!
    QString m_background;

    //!
    //! \brief m_systemTextColor
    //!
    QString m_systemTextColor;

    //!
    //! \brief m_appTextColor
    //!
    QString m_appTextColor;

    //!
    //! \brief m_settingListColorModel
    //!
    QStringList m_settingListColorModel;

    //!
    //! \brief m_smsColorModel
    //!
    QStringList m_smsColorModel;

    //!
    //! \brief m_appBackGround
    //!
    QString m_appBackGround;

    //!
    //! \brief m_appIconTheme
    //!
    int m_appIconTheme;

};

#endif // THEMESETTINGMODEL_H
