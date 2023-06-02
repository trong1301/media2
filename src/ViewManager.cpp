// 2W include
#include "include/ViewManager.h"
#include "include/Log.h"
#include "include/MagicNumbers.h"

// Qt include
#include "QDebug"
#include <QStandardPaths>

ViewManager::ViewManager(QObject* parent)
    : QObject(parent)
    , m_viewState(Helper::MagicNumbers::ViewScreen::MAINGAUGE.c_str())
    , m_lastViewState(Helper::MagicNumbers::ViewScreen::MAINGAUGE.c_str())
    , IMG_PATH{QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)
   [0].toStdString()}
{
}

ViewManager::~ViewManager() {}

QString ViewManager::getViewState()
{
    return m_viewState;
}

void ViewManager::setViewState(const QString& viewState)
{
    if (m_viewState == viewState)
        return;

    m_viewState = viewState;
    emit viewStateChanged(m_viewState);
}

QString ViewManager::getLastViewState()
{
    return m_lastViewState;
}

void ViewManager::setLastViewState(const QString& viewState)
{
    if (m_lastViewState == viewState)
        return;

    m_lastViewState = viewState;
    qDebug() << "Last view state saved:" << m_lastViewState;
    emit lastViewStateChanged(m_viewState);
}

void ViewManager::requestChangeViewState(QString from, QString to)
{
    std::string result = "";
    std::string stdFrom = from.toStdString();
    std::string stdTo = to.toStdString();

    using namespace Helper::MagicNumbers;

    if (stdFrom == ViewScreen::MAINGAUGE
            && stdTo == ViewScreen::SUBGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE
               && stdTo == ViewScreen::MAINGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE
               && stdTo == ViewScreen::SUBGAUGE_SETTINGS) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_SETTINGS
               && stdTo == ViewScreen::SUBGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE
               && stdTo == ViewScreen::SUBGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE
               && stdTo == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS
               && stdTo == ViewScreen::SUBGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS
               && stdTo == ViewScreen::SUBGAUGE_PHONE_CALL_LOG_LIST) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_CALL_LOG_LIST
               && stdTo == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS
               && stdTo == ViewScreen::SUBGAUGE_PHONE_CONTACT_LIST) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_CONTACT_LIST
               && stdTo == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS
               && stdTo == ViewScreen::SUBGAUGE_PHONE_SMS_LIST) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_SMS_LIST
               && stdTo == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_SMS_LIST
               && stdTo == ViewScreen::SUBGAUGE_PHONE_SMS_ITEM) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_SMS_ITEM
               && stdTo == ViewScreen::SUBGAUGE_PHONE_SMS_LIST) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS
               && stdTo == ViewScreen::SUBGAUGE_PHONE_MAP_NAVIGATION) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_PHONE_MAP_NAVIGATION
               && stdTo == ViewScreen::SUBGAUGE_PHONE_APPLICATIONS) {
        result = stdTo;
    } else if ((stdFrom == ViewScreen::ANYWHERE
                && stdTo == ViewScreen::TOP_INCOMING_CALL)
               || (stdFrom == ViewScreen::ANYWHERE
                   && stdTo == ViewScreen::TOP_OUTGOING_CALL)) {
        result = stdTo;
    } else if ((stdFrom == ViewScreen::TOP_INCOMING_CALL
                && stdTo == ViewScreen::ANYWHERE)
               || (stdFrom == ViewScreen::TOP_OUTGOING_CALL
                   && stdTo == ViewScreen::ANYWHERE)) {
        result = m_lastViewState.toStdString();
    }
    else if (stdFrom == ViewScreen::TOP_INCOMING_CALL
             && stdTo == ViewScreen::TOP_OUTGOING_CALL) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE
               && stdTo == ViewScreen::SUBGAUGE_CAMERA) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_CAMERA
               && stdTo == ViewScreen::SUBGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_CAMERA
               && stdTo == ViewScreen::SUBGAUGE_GALLERY) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_GALLERY
               && stdTo == ViewScreen::SUBGAUGE_CAMERA) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_GALLERY
               && stdTo == ViewScreen::SUBGAUGE_VIDEOmini) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_VIDEOmini
               && stdTo == ViewScreen::SUBGAUGE_GALLERY) {
        result = stdTo;

    } else if (stdFrom == ViewScreen::SUBGAUGE
           && stdTo == ViewScreen::SUBGAUGE_MEDIA) {
    result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_MEDIA
               && stdTo == ViewScreen::SUBGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::SUBGAUGE_MEDIA
               && stdTo == ViewScreen::MAINGAUGE) {
        result = stdTo;
    } else if (stdFrom == ViewScreen::MAINGAUGE
               && stdTo == ViewScreen::SUBGAUGE_MEDIA) {
        result = stdTo;
    }

    if (result != ""){
        qDebug() << "Change view from" << from << "to" << result.c_str();
        setViewState(result.c_str());
    }
}

bool ViewManager::isNativeBuild()
{
#ifdef NATIVE_BUILD
    return true;
#else
    return false;
#endif
}

bool ViewManager::isRotated180()
{
#ifdef ROTATED_180
    return true;
#else
    return false;
#endif
}

//Media Player
QString ViewManager::getSystemPicturesPath()
{
    return "file://" + QString::fromStdString(IMG_PATH) + "/";
}
