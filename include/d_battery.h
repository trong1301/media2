#ifndef D_BATTERY_H
#define D_BATTERY_H

#include "GuiController.h"

#include <QObject>
#include <QQuickPaintedItem>

class d_battery : public QQuickPaintedItem
{
    qreal m_BatterySize;
    qreal m_StartAngle;
    qreal m_AlignAngle;
    qreal m_LowestRange;
    int m_HighestRange;
    int m_HighestBattery;
    int m_BatteryLevel;
    int m_ArcWidth;
    QColor m_OuterColor;
    QColor m_InnerColor;
    QColor m_TextColor;
    QColor m_BackgroundColor;

    Q_OBJECT

    Q_PROPERTY(qreal batterySize READ getBatterySize WRITE setBatterySize NOTIFY batterySizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal alignAngle READ getAlignAngle WRITE setAlignAngle NOTIFY alignAngleChanged)
    Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(int highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(int highestBattery READ getHighestBattery WRITE setHighestBattery NOTIFY highestBatteryChanged)
    Q_PROPERTY(int batteryLevel READ getBatteryLevel WRITE setBatteryLevel NOTIFY batteryLevelChanged)
    Q_PROPERTY(int arcWidth READ getArcWidth WRITE setArcWidth NOTIFY arcWidthChanged)
    Q_PROPERTY(QColor outerColor READ getOuterColor WRITE setOuterColor NOTIFY outerColorChanged)
    Q_PROPERTY(QColor innerColor READ getInnerColor WRITE setInnerColor NOTIFY innerColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    explicit d_battery(QQuickPaintedItem* parent = 0, std::shared_ptr<sdl::GuiController> guiCtrl = nullptr);
    void paint(QPainter *painter);

    qreal getBatterySize();
    qreal getStartAngle();
    qreal getAlignAngle();
    qreal getLowestRange();
    int getHighestRange();
    int getHighestBattery();
    int getBatteryLevel();
    int getArcWidth();
    QColor getOuterColor();
    QColor getInnerColor();
    QColor getTextColor();
    QColor getBackgroundColor();

    void setBatterySize(qreal size);
    void setStartAngle(qreal startAngle);
    void setAlignAngle(qreal angle);
    void setLowestRange(qreal losbwestRange);
    void setHighestRange(int highestRange);
    void setHighestBattery(int highestBattery);
    void setBatteryLevel(int batteryLevel);
    void setArcWidth(int arcWidth);
    void setOuterColor(QColor outerColor);
    void setInnerColor(QColor innerColor);
    void setTextColor(QColor textColor);
    void setBackgroundColor(QColor backgroundColor);

signals:
    void batterySizeChanged();
    void startAngleChanged();
    void alignAngleChanged();
    void lowestRangeChanged();
    void highestRangeChanged();
    void highestBatteryChanged();
    void batteryLevelChanged();
    void arcWidthChanged();
    void outerColorChanged();
    void innerColorChanged();
    void textColorChanged();
    void backgroundColorChanged();

};

#endif // D_BATTERY_H
