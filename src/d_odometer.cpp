#include "include/d_odometer.h"

#include <QDebug>
#include <QPainter>

d_odometer::d_odometer(QQuickPaintedItem *parent, std::shared_ptr<sdl::GuiController> guiCtrl)
    : QQuickPaintedItem(parent),
      m_TripSize(170),
      m_StartAngle(50),
      m_AlignAngle(260), // it should be 360 - m_StartAngle*2 for good looking
      m_LowestRange(0),
      m_HighestRange(360),
      m_HighestTrip(100),
      m_Trip(547.9),
      m_ArcWidth(3),
      m_OuterColor(QColor(23,246,246)),
      m_InnerColor(QColor(160,255,0)),
      m_TextColor(QColor(255,255,255)),
      m_BackgroundColor(Qt::transparent)
{

}
void d_odometer::paint(QPainter *painter)
{
    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

//    startAngle = m_StartAngle - 100;
//    spanAngle = 0 - m_AlignAngle;

    //all arc
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_InnerColor);
    painter->setPen(pen);
    //painter->drawRect(rect);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), 360 * 16, 360 * 16);
    painter->restore();

    //text which shows title
    painter->save();
    QFont title_font("Halvetica", 12, QFont::Bold);
    painter->setFont(title_font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_TripSize/30, m_TripSize/30, -m_TripSize/30, -m_TripSize/2.5), Qt::AlignCenter, tr("TRIP"));
    painter->restore();

    //text which shows the value
    painter->save();
    QFont font("Halvetica", 30, QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_TripSize/30, m_TripSize/30, -m_TripSize/30, -m_TripSize/100), Qt::AlignCenter, QString::number(m_Trip,'f',1));
    painter->restore();

    //text which shows unit
    painter->save();
    QFont unit_font("Halvetica", 12, QFont::Bold);
    painter->setFont(unit_font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_TripSize/30, m_TripSize/2, -m_TripSize/30, -m_TripSize/10), Qt::AlignCenter, tr("Km"));
    painter->restore();
}

qreal d_odometer::getTripSize()
{
    return m_TripSize;
}

qreal d_odometer::getStartAngle()
{
    return m_StartAngle;
}

qreal d_odometer::getAlignAngle()
{
    return m_AlignAngle;
}

qreal d_odometer::getLowestRange()
{
    return m_LowestRange;
}

int d_odometer::getHighestRange()
{
    return m_HighestRange;
}

int d_odometer::getHighestTrip()
{
    return m_HighestTrip;
}

qreal d_odometer::getTrip()
{
    return m_Trip;
}

int d_odometer::getArcWidth()
{
    return m_ArcWidth;
}

QColor d_odometer::getOuterColor()
{
    return m_OuterColor;
}

QColor d_odometer::getInnerColor()
{
    return m_InnerColor;
}

QColor d_odometer::getTextColor()
{
    return m_TextColor;
}

QColor d_odometer::getBackgroundColor()
{
    return m_BackgroundColor;
}

void d_odometer::setTripSize(qreal size)
{
    m_TripSize = size;
    emit tripSizeChanged();
}

void d_odometer::setStartAngle(qreal startAngle)
{
    m_StartAngle = startAngle;
    emit startAngleChanged();
}

void d_odometer::setAlignAngle(qreal angle)
{
    m_AlignAngle = angle;
    emit alignAngleChanged();
}

void d_odometer::setLowestRange(qreal losbwestRange)
{
    m_LowestRange = losbwestRange;
    emit lowestRangeChanged();
}

void d_odometer::setHighestRange(int highestRange)
{
    m_HighestRange = highestRange;
    emit highestRangeChanged();
}

void d_odometer::setHighestTrip(int highestTrip)
{
    m_HighestTrip = highestTrip;
    emit highestTripChanged();
}

void d_odometer::setTrip(qreal trip)
{
    m_Trip = trip;
    emit tripChanged();
}

void d_odometer::setArcWidth(int arcWidth)
{
    m_ArcWidth = arcWidth;
    emit arcWidthChanged();
}

void d_odometer::setOuterColor(QColor outerColor)
{
    m_OuterColor = outerColor;
    emit outerColorChanged();
}

void d_odometer::setInnerColor(QColor innerColor)
{
    m_InnerColor = innerColor;
    emit innerColorChanged();
}

void d_odometer::setTextColor(QColor textColor)
{
    m_TextColor = textColor;
    emit textColorChanged();
}

void d_odometer::setBackgroundColor(QColor backgroundColor)
{
    m_BackgroundColor = backgroundColor;
    emit backgroundColorChanged();
}
