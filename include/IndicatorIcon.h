#ifndef INDICATORICON_H
#define INDICATORICON_H

// Qt includes
#include <QObject>
#include <QString>
#include <QColor>

#define DISPLAY_BOTH_SCREENS 1
#define DISPLAY_ONE_SCREEN 0
#define TURN_LEFT_LIMIT 10
#define FUEL_LIMIT 10
#define HEAD_LIGHT_LIMIT 10
#define ENGINE_TROUBLE_LIMIT 10
#define OIL_LOWER_LIMIT 10
#define COOLANT_TEMP_LIMIT 10
#define ABS_LIMIT 10
#define TURN_RIGHT_LIMIT 10
#define  COLOR_BG_ICON_INACTIVE1 "#003300"
#define  COLOR_BG_ICON_INACTIVE2 "#483504"
#define  COLOR_BORDER_BG_ICON "#cccc00"
#define  COLOR_BG_ICON_ACTIVE1 "#52cc00"
#define  COLOR_BG_ICON_ACTIVE2 "#ffab09"
#define  COLOR_SHADOW_BORDER_BG_ICON "#e6e600"

class IndicatorIcon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nameIcon READ nameIcon WRITE setNameIcon NOTIFY nameIconChanged)
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourcChanged)
    Q_PROPERTY(QColor colorBgIconInactive READ colorBgIconInactive WRITE setColorBgIconInactive NOTIFY colorBgIconInactiveChanged)
    Q_PROPERTY(QColor colorBorderBgIconInactive READ colorBorderBgIconInactive WRITE setColorBorderBgIconInactive NOTIFY colorBorderBgIconInactiveChanged)
    Q_PROPERTY(QColor colorBgIconActive READ colorBgIconActive WRITE setColorBgIconActive NOTIFY colorBgIconActiveChanged)
    Q_PROPERTY(QColor colorBorderBgIconActive READ colorBorderBgIconActive WRITE setColorBorderBgIconActive NOTIFY colorBorderBgIconActiveChanged)
    Q_PROPERTY(QColor colorShadowBorderBgIcon READ colorShadowBorderBgIcon WRITE setColorShadowBorderBgIcon NOTIFY colorShadowBorderBgIconChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString stateIcon READ stateIcon WRITE setStateIcon NOTIFY stateIconChanged)

public:

    explicit IndicatorIcon(QObject *parent=nullptr);

    //~IndicatorData();

    QString nameIcon() const;
    QString imageSource() const;
    QColor colorBgIconInactive() const;
    QColor colorBorderBgIconInactive() const;
    QColor colorBgIconActive() const;
    QColor colorBorderBgIconActive() const;
    QColor colorShadowBorderBgIcon() const;
    bool visible() const;
    QString stateIcon() const;

public slots:
    void setNameIcon(QString nameIcon);

    void setImageSource(QString imageSource);

    void setColorBgIconInactive(QColor colorBgIconInactive);

    void setColorBorderBgIconInactive(QColor colorBorderBgIconInactive);

    void setColorBgIconActive(QColor colorBgIconActive);

    void setColorBorderBgIconActive(QColor colorBorderBgIconActive);

    void setColorShadowBorderBgIcon(QColor colorShadowBorderBgIcon);

    void setVisible(bool visible);

    void setStateIcon(QString stateIcon);

signals:
    void nameIconChanged(QString nameIcon);

    void imageSourcChanged(QString imageSource);

    void colorBgIconInactiveChanged(QColor colorBgIconInactive);

    void colorBorderBgIconInactiveChanged(QColor colorBorderBgIconInactive);

    void colorBgIconActiveChanged(QColor colorBgIconActive);

    void colorBorderBgIconActiveChanged(QColor colorBorderBgIconActive);

    void colorShadowBorderBgIconChanged(QColor colorShadowBorderBgIcon);

    void visibleChanged(bool visible);

    void stateIconChanged(QString stateIcon);

private:
    QString m_nameIcon;
    QString m_imageSource;
    QColor m_colorBgIconInactive;
    QColor m_colorBorderBgIconInactive;
    QColor m_colorBgIconActive;
    QColor m_colorBorderBgIconActive;
    QColor m_colorShadowBorderBgIcon;
    bool m_visible;
    QString m_stateIcon;

    explicit IndicatorIcon(const IndicatorIcon& rhs) = delete;
    IndicatorIcon& operator= (const IndicatorIcon& rhs) = delete;

};

#endif // INDICATORICON_H
