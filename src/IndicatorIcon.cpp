#include "include/IndicatorIcon.h"
#include <QDebug>

IndicatorIcon::IndicatorIcon(QObject* parent)
    : QObject(parent)
    , m_nameIcon("Name Icon")
    , m_imageSource("Source imgae")
    , m_colorBgIconInactive("#ffffff")
    , m_colorBorderBgIconInactive("#ffffff")
    , m_colorBgIconActive("#ffffff")
    , m_colorBorderBgIconActive("#ffffff")
    , m_colorShadowBorderBgIcon("#ffffff")
    , m_visible(false)
    , m_stateIcon("Inactive")
{
}

QColor IndicatorIcon::colorBgIconInactive() const
{
    return m_colorBgIconInactive;
}

QColor IndicatorIcon::colorBorderBgIconInactive() const
{
    return m_colorBorderBgIconInactive;
}

QColor IndicatorIcon::colorBgIconActive() const
{
    return m_colorBgIconActive;
}

QColor IndicatorIcon::colorBorderBgIconActive() const
{
    return m_colorBorderBgIconActive;
}

QColor IndicatorIcon::colorShadowBorderBgIcon() const
{
    return m_colorShadowBorderBgIcon;
}

bool IndicatorIcon::visible() const
{
    return m_visible;
}

QString IndicatorIcon::stateIcon() const
{
    return m_stateIcon;
}

QString IndicatorIcon::nameIcon() const
{
    return m_nameIcon;
}

QString IndicatorIcon::imageSource() const
{
    return m_imageSource;
}

void IndicatorIcon::setNameIcon(QString nameIcon)
{
    if (m_nameIcon == nameIcon)
        return;

    m_nameIcon = nameIcon;
    emit nameIconChanged(m_nameIcon);
}

void IndicatorIcon::setImageSource(QString imageSource)
{
    if (m_imageSource == imageSource)
        return;

    m_imageSource = imageSource;
    emit imageSourcChanged(m_imageSource);
}

void IndicatorIcon::setColorBgIconInactive(QColor colorBgIconInactive)
{
    if (m_colorBgIconInactive == colorBgIconInactive)
        return;

    m_colorBgIconInactive = colorBgIconInactive;
    emit colorBgIconInactiveChanged(m_colorBgIconInactive);
}

void IndicatorIcon::setColorBorderBgIconInactive(QColor colorBorderBgIconInactive)
{
    if (m_colorBorderBgIconInactive == colorBorderBgIconInactive)
        return;

    m_colorBorderBgIconInactive = colorBorderBgIconInactive;
    emit colorBorderBgIconInactiveChanged(m_colorBorderBgIconInactive);
}

void IndicatorIcon::setColorBgIconActive(QColor colorBgIconActive)
{
    if (m_colorBgIconActive == colorBgIconActive)
        return;

    m_colorBgIconActive = colorBgIconActive;
    emit colorBgIconActiveChanged(m_colorBgIconActive);
}

void IndicatorIcon::setColorBorderBgIconActive(QColor colorBorderBgIconActive)
{
    if (m_colorBorderBgIconActive == colorBorderBgIconActive)
        return;

    m_colorBorderBgIconActive = colorBorderBgIconActive;
    emit colorBorderBgIconActiveChanged(m_colorBorderBgIconActive);
}

void IndicatorIcon::setColorShadowBorderBgIcon(QColor colorShadowBorderBgIcon)
{
    if (m_colorShadowBorderBgIcon == colorShadowBorderBgIcon)
        return;

    m_colorShadowBorderBgIcon = colorShadowBorderBgIcon;
    emit colorShadowBorderBgIconChanged(m_colorShadowBorderBgIcon);
}

void IndicatorIcon::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;
    emit visibleChanged(m_visible);
}

void IndicatorIcon::setStateIcon(QString stateIcon)
{
    if (m_stateIcon == stateIcon)
        return;

    m_stateIcon = stateIcon;
    emit stateIconChanged(m_stateIcon);
}
