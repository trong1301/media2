#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

// Qt include
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

// 2W include
#include "BatteryHandler.h"
#include "IndicatorIcon.h"
#include "IndicatorListModel.h"
#include "Speedometer.h"
#include "SystemClock.h"
#include "ViewManager.h"
#include "SettingHandler.h"
#include "NotificationsManager.h"
#include "ContactModel.h"
#include "GuiPhoneDataModel.h"
#include "PhoneController.h"
#include "Smscontentmodel.h"
#include "SmsListModel.h"
#include "CallLogListItemModel.h"
#include "SocketManager.h"
#include "d_speedometer.h"
#include "d_odometer.h"
#include "d_battery.h"
#include "MediaDataModel.h"
#include "MediaPlayListModel.h"

// SDL include
#include "GuiController.h"

//!
//! \brief The GuiApplication class contain invoke function, init component,...
//!
class GuiApplication : public QGuiApplication {
public:
    //!
    //! \brief GuiApplication
    //!
    GuiApplication(int& argc, char** argv);

    //!
    //! \brief ~GuiApplication
    //!
    ~GuiApplication();

    //!
    //! \brief Called from main
    //!
    int exec();

private:
    //!
    //! \brief Init components
    //!
    void init();

    //!
    //! \brief Init 2W logging pattern
    //!
    void initTWLog();

    //!
    //! \brief Set system font
    //!
    void initTWFont();

    //!
    //! \brief Init root contexts to expose them to Qml
    //!
    void initContexts();

    //!
    //! \brief Init SDL Components
    //!
    void initSDLComponents();

    //!
    //! \brief Fetch and display current system information
    //!
    std::string fetchtSystemInfo();

    //!
    //! \brief initSocketConnection, use when some signals of vehicle not from CAN
    //!
    void initSocketConnection();

private:
    //!
    //! \brief m_engine
    //!
    QQmlApplicationEngine m_engine;

    //!
    //! \brief m_viewManager
    //!
    std::shared_ptr<ViewManager> m_viewManager;

    //!
    //! \brief m_guiPhoneDataModel
    //!
    std::shared_ptr<GuiPhoneDataModel> m_guiPhoneDataModel;

    //!
    //! \brief m_setting
    //!
    std::shared_ptr<SettingHandler> m_setting;

    //!
    //! \brief m_phoneController
    //!
    std::shared_ptr<PhoneController> m_phoneController;

    //!
    //! \brief m_guiController
    //!
    std::shared_ptr<sdl::GuiController> m_guiController;

    //!
    //! \brief m_systemClock
    //!
    std::shared_ptr<SystemClock> m_systemClock;

    //!
    //! \brief m_speedometer
    //!
    std::shared_ptr<d_speedometer> m_speedometer;

    //!
    //! \brief m_battery
    //!
    std::shared_ptr<BatteryHandler> m_battery;

    //!
    //! \brief m_socketManager
    //!
    std::shared_ptr<SocketManager> m_socketManager;

    //!
    //! \brief m_indicatorListModel
    //!
    std::shared_ptr<IndicatorListModel> m_indicatorListModel;

    //!
    //! \brief m_notificationManager
    //!
    std::shared_ptr<NotificationsManager> m_notificationManager;

    //!
    //! \brief m_contactModel
    //!
    std::shared_ptr<ContactModel> m_contactModel;

    //!
    //! \brief m_smsContentModel
    //!
    std::shared_ptr<SmsContentModel> m_smsContentModel;

    //!
    //! \brief m_smsListModel
    //!
    std::shared_ptr<SmsListModel> m_smsListModel;

    //!
    //! \brief m_callLogModel
    //!
    std::shared_ptr<CallLogListItemModel> m_callLogModel;

    //!
    //! \brief m_mediaDataModel
    //!
    std::shared_ptr<MediaDataModel> m_mediaDataModel;


    //!
    //! \brief m_mediaPlaylistModel
    //!
    std::shared_ptr<MediaPlayListModel> m_mediaPlaylistModel;


};

#endif // GUIAPPLICATION_H
