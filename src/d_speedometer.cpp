// 2W includes
#include "include/d_speedometer.h"

// Qt includes
#include <QDebug>
#include <QPainter>

d_speedometer::d_speedometer(QQuickItem* parent, std::shared_ptr<sdl::GuiController> guiCtrl)
    : QQuickPaintedItem(parent),
      //m_SpeedometerSize(250), // touch screen is 800 x 480
      m_SpeedometerSize(230),
      m_StartAngle(50),
      m_AlignAngle(260), // it should be 360 - m_StartAngle*2 for good looking
      m_LowestRange(0),
      m_HighestRange(4000),
      m_HighestSpeed(160),
      //m_Speed(2430),
      m_Speed(20),
      m_ArcWidth(3),
      //m_OuterColor(QColor(12,16,247)),
      //m_InnerColor(QColor(51,88,255,80)),
      //m_TextColor(QColor(255,255,255)),
//      m_OuterColor(QColor(160,255,0)),
      m_OuterColor(QColor(255,255,255)),
      m_InnerColor(QColor(255,255,255)),
      m_TextColor(QColor(255,255,255)),
      m_BackgroundColor(Qt::transparent)
{

}
void d_speedometer::paint(QPainter *painter)
{
    QRectF rect = this->boundingRect();
//    QRectF rect(0, 0, 230, 230);
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_StartAngle - 40;
    spanAngle = 0 - m_AlignAngle;

    //all arc
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_InnerColor);
    painter->setPen(pen);
    //painter->drawRect(rect);
    //painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, spanAngle * 16);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), 360 * 16, 360 * 16);
//    painter->drawArc(rect, 360 * 16, 360 * 16);
//    painter->drawRect(rect);
    painter->restore();

    //inner pie
//    int pieSize = m_SpeedometerSize/5;
//    painter->save();
//    pen.setWidth(m_ArcWidth/2);
//    pen.setColor(m_OuterColor);
//    painter->setBrush(m_InnerColor);
//    painter->setPen(pen);
//    painter->drawPie(rect.adjusted(pieSize, pieSize, -pieSize, -pieSize), startAngle * 16, spanAngle * 16);
//    painter->restore();

    //text which shows the value
    painter->save();
    //QFont font("Halvetica",52,QFont::Bold);
    QFont font("Halvetica", 45, QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    //painter->drawText(rect.adjusted(m_SpeedometerSize/30, m_SpeedometerSize/30, -m_SpeedometerSize/30, -m_SpeedometerSize/4), Qt::AlignCenter  ,QString::number((m_Speed/40),'f',1));
    painter->drawText(rect.adjusted(m_SpeedometerSize/30, m_SpeedometerSize/5, -m_SpeedometerSize/30, -m_SpeedometerSize/4), Qt::AlignCenter, QString::number(m_Speed,'f',0));
    painter->restore();

    //text which shows unit
    painter->save();
    QFont unit_font("Halvetica", 11, QFont::Bold);
    painter->setFont(unit_font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_SpeedometerSize/30, m_SpeedometerSize/2, -m_SpeedometerSize/30, -m_SpeedometerSize/4), Qt::AlignCenter, tr("km/h"));
    painter->restore();

    //current active progress
    painter->save();
    pen.setWidth(m_ArcWidth * 11);
    if(m_Speed >= 60){
        m_OuterColor = "red";
    }
    else if(m_Speed >= 40){
        m_OuterColor = "yellow";
    }
    else{
        m_OuterColor = QColor(160,255,0);
    }
    pen.setColor(m_OuterColor);
    pen.setCapStyle(Qt::RoundCap);
    //qreal valueToAngle = ((m_Speed - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    qreal value = (m_Speed * m_HighestRange) / m_HighestSpeed;
    qreal valueToAngle = ((value - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    qreal progress_ArcWitdth = m_ArcWidth * 8;
    painter->setPen(pen);
    //painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, valueToAngle * 16);
    painter->drawArc(rect.adjusted(progress_ArcWitdth, progress_ArcWitdth, -progress_ArcWitdth, -progress_ArcWitdth), startAngle * 16, valueToAngle * 16);
    painter->restore();
}

qreal d_speedometer::getSpeedometerSize()
{
    return m_SpeedometerSize;
}
qreal d_speedometer::getStartAngle()
{
    return m_StartAngle;
}
qreal d_speedometer::getAlignAngle()
{
    return m_AlignAngle;
}
qreal d_speedometer::getLowestRange()
{
    return m_LowestRange;
}
qreal d_speedometer::getHighestRange()
{
    return m_HighestRange;
}
qreal d_speedometer::getSpeed()
{
    return m_Speed;
}
int d_speedometer::getArcWidth()
{
    return m_ArcWidth;
}
QColor d_speedometer::getOuterColor()
{
    return m_OuterColor;
}
QColor d_speedometer::getInnerColor()
{
    return m_InnerColor;
}
QColor d_speedometer::getTextColor()
{
    return m_TextColor;
}
QColor d_speedometer::getBackgroundColor()
{
    return m_BackgroundColor;
}

void d_speedometer::setSpeedometerSize(qreal size)
{
    m_SpeedometerSize = size;
    emit speedometerSizeChanged();
}
void d_speedometer::setStartAngle(qreal startAngle)
{
    m_StartAngle = startAngle;
    emit startAngleChanged();
}
void d_speedometer::setAlignAngle(qreal angle)
{
    m_StartAngle = angle;
    emit alignAngleChanged();
}

void d_speedometer::setLowestRange(qreal lowestRange)
{
    m_LowestRange = lowestRange;
    emit lowestRangeChanged();
}

void d_speedometer::setHighestRange(qreal highestRange)
{
    m_HighestRange = highestRange;
    emit highestRangeChanged();
}

void d_speedometer::setSpeed(qreal speed)
{
    m_Speed = speed;
    update();
    emit speedChanged();
}

void d_speedometer::setArcWidth(int arcWidth)
{
    m_ArcWidth = arcWidth;
    emit arcWidthChanged();
}

void d_speedometer::setOuterColor(QColor outerColor)
{
    m_OuterColor = outerColor;
    emit outerColorChanged();
}

void d_speedometer::setInnerColor(QColor innerColor)
{
    m_InnerColor = innerColor;
    emit innerColorChanged();
}

void d_speedometer::setTextColor(QColor textColor)
{
    m_TextColor = textColor;
    emit textColorChanged();
}

void d_speedometer::setBackgroundColor(QColor backgroundColor)
{
    m_BackgroundColor = backgroundColor;
    emit backgroundColorChanged();
}
