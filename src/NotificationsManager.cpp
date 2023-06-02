// Qt includes
#include <QDebug>

// 2W includes
#include "include/NotificationsManager.h"

NotificationsManager::NotificationsManager(QObject* parent, std::shared_ptr<PhoneController> phoneCtrl)
    : QObject(parent)
    , m_usbIconVisible(false)
    , m_wifiIconVisible(false)
    , m_messageIconVisible(false)
    , m_callIconVisible(false)
    , m_phoneController(phoneCtrl)
{

    connect(m_phoneController.get(), &PhoneController::IsPhoneConnectedChanged, this, [&](const bool& isPhoneConntected){
        if(isPhoneConntected == false)
        {
            setUsbIconVisible(false);
            setWifiIconVisible(false);
            setMessageIconVisible(false);
            setCallIconVisible(false);
        }
    });

    connect(m_phoneController.get(), &PhoneController::onUsbIconVisibilityChanged, this, [&](const bool& visible) {
        setUsbIconVisible(visible);
    });
    connect(m_phoneController.get(), &PhoneController::onWifiIconVisibilityChanged, this, [&](const bool& visible) {
        setWifiIconVisible(visible);
    });
    connect(m_phoneController.get(), &PhoneController::onMessageIconVisibilityChanged, this, [&](const bool& visible) {
        setMessageIconVisible(visible);
    });
    connect(m_phoneController.get(), &PhoneController::onCallIconVisibilityChanged, this, [&](const bool& visible) {
        setCallIconVisible(visible);
    });
}

NotificationsManager::~NotificationsManager()
{
    disconnect(m_phoneController.get(), &PhoneController::IsPhoneConnectedChanged, this, nullptr);
    disconnect(m_phoneController.get(), &PhoneController::onUsbIconVisibilityChanged, this, nullptr);
    disconnect(m_phoneController.get(), &PhoneController::onWifiIconVisibilityChanged, this, nullptr);
    disconnect(m_phoneController.get(), &PhoneController::onMessageIconVisibilityChanged, this, nullptr);
    disconnect(m_phoneController.get(), &PhoneController::onCallIconVisibilityChanged, this, nullptr);
}

void NotificationsManager::setUsbIconVisible(const bool &visible)
{
    if (m_usbIconVisible == visible)
        return;
    m_usbIconVisible = visible;
    emit onUsbIconVisibilityChanged();
}

void NotificationsManager::setWifiIconVisible(const bool &visible)
{
    if (m_wifiIconVisible == visible)
        return;
    m_wifiIconVisible = visible;
    emit onWifiIconVisibilityChanged();
}

void NotificationsManager::setMessageIconVisible(const bool &visible)
{
    if (m_messageIconVisible == visible)
        return;
    m_messageIconVisible = visible;
    emit onMessageIconVisibilityChanged();
}

void NotificationsManager::setCallIconVisible(const bool &visible)
{
    if (m_callIconVisible == visible)
        return;
    m_callIconVisible = visible;
    emit onCallIconVisibilityChanged();
}
