#ifndef D_ODOMETER_H
#define D_ODOMETER_H

#include "GuiController.h"

#include <QObject>
#include <QQuickPaintedItem>

class d_odometer : public QQuickPaintedItem
{
    qreal m_TripSize;
    qreal m_StartAngle;
    qreal m_AlignAngle;
    qreal m_LowestRange;
    int m_HighestRange;
    int m_HighestTrip;
    qreal m_Trip;
    int m_ArcWidth;
    QColor m_OuterColor;
    QColor m_InnerColor;
    QColor m_TextColor;
    QColor m_BackgroundColor;

    Q_OBJECT

    Q_PROPERTY(qreal tripSize READ getTripSize WRITE setTripSize NOTIFY tripSizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal alignAngle READ getAlignAngle WRITE setAlignAngle NOTIFY alignAngleChanged)
    Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(int highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(int highestTrip READ getHighestTrip WRITE setHighestTrip NOTIFY highestTripChanged)
    Q_PROPERTY(qreal trip READ getTrip WRITE setTrip NOTIFY tripChanged)
    Q_PROPERTY(int arcWidth READ getArcWidth WRITE setArcWidth NOTIFY arcWidthChanged)
    Q_PROPERTY(QColor outerColor READ getOuterColor WRITE setOuterColor NOTIFY outerColorChanged)
    Q_PROPERTY(QColor innerColor READ getInnerColor WRITE setInnerColor NOTIFY innerColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    explicit d_odometer(QQuickPaintedItem *parent = nullptr, std::shared_ptr<sdl::GuiController> guiCtrl = nullptr);
    void paint(QPainter *painter);

    qreal getTripSize();
    qreal getStartAngle();
    qreal getAlignAngle();
    qreal getLowestRange();
    int getHighestRange();
    int getHighestTrip();
    qreal getTrip();
    int getArcWidth();
    QColor getOuterColor();
    QColor getInnerColor();
    QColor getTextColor();
    QColor getBackgroundColor();

    void setTripSize(qreal size);
    void setStartAngle(qreal startAngle);
    void setAlignAngle(qreal angle);
    void setLowestRange(qreal losbwestRange);
    void setHighestRange(int highestRange);
    void setHighestTrip(int highestBattery);
    void setTrip(qreal trip);
    void setArcWidth(int arcWidth);
    void setOuterColor(QColor outerColor);
    void setInnerColor(QColor innerColor);
    void setTextColor(QColor textColor);
    void setBackgroundColor(QColor backgroundColor);

signals:
    void tripSizeChanged();
    void startAngleChanged();
    void alignAngleChanged();
    void lowestRangeChanged();
    void highestRangeChanged();
    void highestTripChanged();
    void tripChanged();
    void arcWidthChanged();
    void outerColorChanged();
    void innerColorChanged();
    void textColorChanged();
    void backgroundColorChanged();

};

#endif // D_ODOMETER_H
