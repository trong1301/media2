#ifndef NOTIFICATIONSMANAGER_H
#define NOTIFICATIONSMANAGER_H

// 2W include
#include "GuiController.h"
#include "PhoneController.h"

class NotificationsManager : public QObject {
    Q_OBJECT

    //!
    //! \brief Expose the m_usbIconVisible member to qml
    //!
    Q_PROPERTY(bool isUsbIconVisible MEMBER m_usbIconVisible NOTIFY onUsbIconVisibilityChanged)

    //!
    //! \brief Expose the m_wifiIconVisible member to qml
    //!
    Q_PROPERTY(bool isWifiIconVisible MEMBER m_wifiIconVisible NOTIFY onWifiIconVisibilityChanged)

    //!
    //! \brief Expose the m_messageIconVisible member to qml
    //!
    Q_PROPERTY(bool isMessageIconVisible MEMBER m_messageIconVisible NOTIFY onMessageIconVisibilityChanged)

    //!
    //! \brief Expose the m_callIconVisible member to qml
    //!
    Q_PROPERTY(bool isCallIconVisible MEMBER m_callIconVisible NOTIFY onCallIconVisibilityChanged)

public:
    //!
    //! \brief NotificationsManager
    //! \param parent
    //! \param phoneCtrl
    //!
    explicit NotificationsManager(QObject* parent = nullptr, std::shared_ptr<PhoneController> phoneCtrl = nullptr);

    //!
    //! \brief ~NotificationsManager
    //!
    ~NotificationsManager();

signals:
    //!
    //! \brief onUsbIconVisibilityChanged
    //!
    void onUsbIconVisibilityChanged();

    //!
    //! \brief onWifiIconVisibilityChanged
    //!
    void onWifiIconVisibilityChanged();

    //!
    //! \brief onMessageIconVisibilityChanged
    //!
    void onMessageIconVisibilityChanged();

    //!
    //! \brief onCallIconVisibilityChanged
    //!
    void onCallIconVisibilityChanged();

private:
    //!
    //! \brief m_usbIconVisible
    //!
    bool m_usbIconVisible;

    //!
    //! \brief m_wifiIconVisible
    //!
    bool m_wifiIconVisible;

    //!
    //! \brief m_messageIconVisible
    //!
    bool m_messageIconVisible;

    //!
    //! \brief m_callIconVisible
    //!
    bool m_callIconVisible;

    //!
    //! \brief setUsbIconVisible
    //!
    void setUsbIconVisible(const bool&);

    //!
    //! \brief setWifiIconVisible
    //!
    void setWifiIconVisible(const bool&);

    //!
    //! \brief setMessageIconVisible
    //!
    void setMessageIconVisible(const bool&);

    //!
    //! \brief setCallIconVisible
    //!
    void setCallIconVisible(const bool&);

    //!
    //! \brief m_guiController
    //!
    std::shared_ptr<PhoneController> m_phoneController;
};

#endif // NOTIFICATIONSMANAGER_H
