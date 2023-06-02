#include "include/d_battery.h"

#include <QDebug>
#include <QPainter>

d_battery::d_battery(QQuickPaintedItem *parent, std::shared_ptr<sdl::GuiController> guiCtrl)
    : QQuickPaintedItem(parent),
      m_BatterySize(170),
      m_StartAngle(50),
      m_AlignAngle(260), // it should be 360 - m_StartAngle*2 for good looking
      m_LowestRange(0),
      m_HighestRange(360),
      m_HighestBattery(100),
      m_BatteryLevel(80),
      m_ArcWidth(3),
      m_OuterColor(QColor(23,246,246)),
      m_InnerColor(QColor(160,255,0)),
      m_TextColor(QColor(255,255,255)),
      m_BackgroundColor(Qt::transparent)
{

}

void d_battery::paint(QPainter *painter)
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
    painter->drawText(rect.adjusted(m_BatterySize/30, m_BatterySize/30, -m_BatterySize/30, -m_BatterySize/2.5), Qt::AlignCenter, tr("BATTERY"));
    painter->restore();

    //text which shows the value
    painter->save();
    QFont font("Halvetica", 30, QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_BatterySize/30, m_BatterySize/30, -m_BatterySize/30, -m_BatterySize/100), Qt::AlignCenter, QString::number(m_BatteryLevel,'f',0));
    painter->restore();

    //text which shows unit
    painter->save();
    QFont unit_font("Halvetica", 12, QFont::Bold);
    painter->setFont(unit_font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_BatterySize/30, m_BatterySize/2, -m_BatterySize/30, -m_BatterySize/10), Qt::AlignCenter, tr("%"));
    painter->restore();

    //current active progress
    painter->save();
    pen.setWidth(m_ArcWidth * 6);
    pen.setColor(m_OuterColor);
    int batteryPercent_value = (m_BatteryLevel * m_HighestRange)/m_HighestBattery;
    qreal progress_ArcWitdth = m_ArcWidth * 5.5;
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(progress_ArcWitdth, progress_ArcWitdth, -progress_ArcWitdth, -progress_ArcWitdth), 270 * 16, -batteryPercent_value * 16);
    painter->restore();
}

qreal d_battery::getBatterySize()
{
    return m_BatterySize;
}

qreal d_battery::getStartAngle()
{
    return m_StartAngle;
}

qreal d_battery::getAlignAngle()
{
    return m_AlignAngle;
}

qreal d_battery::getLowestRange()
{
    return m_LowestRange;
}

int d_battery::getHighestRange()
{
    return m_HighestRange;
}

int d_battery::getHighestBattery()
{
    return m_HighestBattery;
}

int d_battery::getBatteryLevel()
{
    return m_BatteryLevel;
}

int d_battery::getArcWidth()
{
    return m_ArcWidth;
}

QColor d_battery::getOuterColor()
{
    return m_OuterColor;
}

QColor d_battery::getInnerColor()
{
    return m_InnerColor;
}

QColor d_battery::getTextColor()
{
    return m_TextColor;
}

QColor d_battery::getBackgroundColor()
{
    return m_BackgroundColor;
}

void d_battery::setBatterySize(qreal size)
{
    m_BatterySize = size;
    emit batterySizeChanged();
}

void d_battery::setStartAngle(qreal startAngle)
{
    m_StartAngle = startAngle;
    emit startAngleChanged();
}

void d_battery::setAlignAngle(qreal angle)
{
    m_AlignAngle = angle;
    emit alignAngleChanged();
}

void d_battery::setLowestRange(qreal losbwestRange)
{
    m_LowestRange = losbwestRange;
    emit lowestRangeChanged();
}

void d_battery::setHighestRange(int highestRange)
{
    m_HighestRange = highestRange;
    emit highestRangeChanged();
}

void d_battery::setHighestBattery(int highestBattery)
{
    m_HighestBattery = highestBattery;
    emit highestBatteryChanged();
}

void d_battery::setBatteryLevel(int batteryLevel)
{
    m_BatteryLevel = batteryLevel;
    emit batteryLevelChanged();
}

void d_battery::setArcWidth(int arcWidth)
{
    m_ArcWidth = arcWidth;
    emit arcWidthChanged();
}

void d_battery::setOuterColor(QColor outerColor)
{
    m_OuterColor = outerColor;
    emit outerColorChanged();
}

void d_battery::setInnerColor(QColor innerColor)
{
    m_InnerColor = innerColor;
    emit innerColorChanged();
}

void d_battery::setTextColor(QColor textColor)
{
    m_TextColor = textColor;
    emit textColorChanged();
}

void d_battery::setBackgroundColor(QColor backgroundColor)
{
    m_BackgroundColor = backgroundColor;
    emit backgroundColorChanged();
}
