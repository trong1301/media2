// Qt include
#include <QQmlContext>
#include <QtGlobal>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QTimer>

// 2W include
#include "include/GuiApplication.h"
#include "include/Log.h"

GuiApplication::GuiApplication(int& argc, char** argv)
    : QGuiApplication(argc, argv)
    , m_viewManager{ std::make_shared<ViewManager>()}
    , m_guiPhoneDataModel { std::make_shared<GuiPhoneDataModel>()}
    , m_setting { std::make_shared<SettingHandler>()}
    , m_phoneController{ std::make_shared<PhoneController>(nullptr, m_viewManager, m_guiPhoneDataModel, m_setting)}
    , m_guiController{ m_phoneController.get()}
    , m_systemClock{ std::make_shared<SystemClock>(nullptr, m_setting)}
    , m_speedometer{ std::make_shared<d_speedometer>(nullptr, m_guiController)}
    , m_battery { std::make_shared<BatteryHandler>(nullptr, m_guiController)}
    , m_socketManager {std::make_shared<SocketManager>(nullptr)}
    , m_indicatorListModel{ std::make_shared<IndicatorListModel>(nullptr, m_guiController
                                                                 , m_socketManager
                                                                 )}
    , m_notificationManager { std::make_shared<NotificationsManager>(nullptr, m_phoneController)}
    , m_contactModel {std::make_shared<ContactModel>(nullptr, m_phoneController)}
    , m_smsContentModel {std::make_shared<SmsContentModel>(nullptr, m_phoneController)}
    , m_smsListModel {std::make_shared<SmsListModel>(nullptr, m_phoneController)}
    , m_callLogModel {std::make_shared<CallLogListItemModel>(nullptr, m_phoneController)}
    , m_mediaDataModel { std::make_shared<MediaDataModel>(nullptr) }
    , m_mediaPlaylistModel { std::make_shared<MediaPlayListModel>(nullptr, m_mediaDataModel.get(), m_viewManager) }
{
}

GuiApplication::~GuiApplication()
{
    qDebug() << "DESTRUCTOR";
    m_viewManager->~ViewManager();
    m_guiPhoneDataModel->~GuiPhoneDataModel();
    m_setting->~SettingHandler();
    m_phoneController->~PhoneController();
    m_guiController->~GuiController();
    m_systemClock->~SystemClock();
    m_speedometer->~d_speedometer();
    m_battery->~BatteryHandler();
    m_socketManager->~SocketManager();
    m_indicatorListModel->~IndicatorListModel();
    m_notificationManager->~NotificationsManager();
    m_contactModel->~ContactModel();
    m_smsContentModel->~SmsContentModel();
    m_smsListModel->~SmsListModel();
    m_callLogModel->~CallLogListItemModel();
    m_mediaDataModel->~MediaDataModel();
    m_mediaPlaylistModel->~MediaPlayListModel();
}

void GuiApplication::init()
{
//    initTWLog();
    // initTWFont(); // Keep here to refer due to now we change font from QML side
//    qInfo() << fetchtSystemInfo().c_str();
    initContexts();
//    initSDLComponents();

#ifdef USE_SOCKET_GPIO
    initSocketConnection();
#endif
}

int GuiApplication::exec()
{
    init();

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&m_engine, &QQmlApplicationEngine::objectCreated, this,
                     [url](QObject* obj, const QUrl& objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
    m_engine.load(url);

    return QGuiApplication::exec();
}

void GuiApplication::initTWLog()
{
    qInstallMessageHandler(utils::tWLogHandler);
}

void GuiApplication::initTWFont()
{
    // Load font from Default or Load the font file from assets.qrc

    /* For custom Font file (.ttf, .otf,...) use the following codes to upload the file to
       QtFont library then reload it from the QtFont library
       REMEMBER TO CHECK THE COPIED PATH OF FONT FILE
    */

    qint32 fontId = QFontDatabase::addApplicationFont(":/fonts/SFNText-Semibold.otf");
    QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);

    QString family = fontList.first();
    setFont(QFont(family));

    /* For defaut fonts of Qt. Just use "setFont(QFont("name-of-font")"
       Available default fonts I found are: "AnyStyle" (default),
       "Serif", "Montserrat", "Courier"

       There are more to research!
    */

    //setFont(QFont("Serif"));
    //setFont(QFont("Courier"));
}

void GuiApplication::initContexts()
{
    qmlRegisterSingletonType(QUrl("qrc:/styling/QmlStyling.qml"),
                             "TwoWheels.QmlStylingSingleton", 1, 0, "QmlStyling");

    qmlRegisterSingletonType(QUrl("qrc:/styling/SharedConstants.qml"),
                             "TwoWheels.SharedConstantsSingleton", 1, 0, "SharedConstants");

    //To connect qml you have to REGISTER type
    qmlRegisterType<d_speedometer>("speedometer",1,0,"Speedometer");
    qmlRegisterType<d_odometer>("odometer",1,0,"Odometer");
    qmlRegisterType<d_battery>("battery",1,0,"Battery");

    m_engine.rootContext()->setContextProperty("viewManager", m_viewManager.get());
    m_engine.rootContext()->setContextProperty("systemClock", m_systemClock.get());
    m_engine.rootContext()->setContextProperty("speedometerModel", m_speedometer.get());
    m_engine.rootContext()->setContextProperty("indicatorListModel", m_indicatorListModel.get());
    m_engine.rootContext()->setContextProperty("batteryViewModel", m_battery.get());
    m_engine.rootContext()->setContextProperty("settingHandler", m_setting.get());
    m_engine.rootContext()->setContextProperty("notificationManager", m_notificationManager.get());
    m_engine.rootContext()->setContextProperty("phoneControllerModel", m_phoneController.get());
    m_engine.rootContext()->setContextProperty("contactModel",m_contactModel.get());
    m_engine.rootContext()->setContextProperty("smsContentModel",m_smsContentModel.get());
    m_engine.rootContext()->setContextProperty("smsListModel",m_smsListModel.get());
    m_engine.rootContext()->setContextProperty("callLogListModel",m_callLogModel.get());
    m_engine.rootContext()->setContextProperty("mediaMetaDataModel", m_mediaDataModel.get());
    m_engine.rootContext()->setContextProperty("mediaPlaylistModel", m_mediaPlaylistModel.get());
}

void GuiApplication::initSDLComponents()
{
    m_guiController->init();
}

std::string GuiApplication::fetchtSystemInfo()
{
    std::string systemInfo{ "\nSystem - information\n" };
    systemInfo += "--------------------\n";
    systemInfo += "\tBuild-System:\n";
    systemInfo += "\t\tBuild architecture\t";
    systemInfo += QSysInfo::buildCpuArchitecture().toStdString() + "\n";

    systemInfo += "\tCurrent-System:\n";
    systemInfo += "\t\tUnique boot ID\t";
    systemInfo += QSysInfo::bootUniqueId().toStdString() + "\n";
    systemInfo += "\t\tUnique machine ID\t";
    systemInfo += QSysInfo::machineUniqueId().toStdString() + "\n";
    systemInfo += "\t\tCPU architecture\t";
    systemInfo += QSysInfo::currentCpuArchitecture().toStdString() + "\n";
    systemInfo += "\t\tKernel type\t";
    systemInfo += QSysInfo::kernelType().toStdString() + "\n";
    systemInfo += "\t\tKernel version\t";
    systemInfo += QSysInfo::kernelVersion().toStdString() + "\n";
    systemInfo += "\t\tMachine host name\t";
    systemInfo += QSysInfo::machineHostName().toStdString() + "\n";

    systemInfo += "\tQt:\n";
    systemInfo += "\t\tQt version\t";
    systemInfo += std::string(qVersion()) + "\n";

    systemInfo += "\tProduct:\n";
    systemInfo += "\t\tProduct name\t";
    systemInfo += QSysInfo::prettyProductName().toStdString() + "\n";
    systemInfo += "\t\tProduct type\t";
    systemInfo += QSysInfo::productType().toStdString() + "\n";
    systemInfo += "\t\tProduct version\t";
    systemInfo += QSysInfo::productVersion().toStdString() + "\n";
    systemInfo += "--------------------";

    return systemInfo;
}

void GuiApplication::initSocketConnection()
{
    m_socketManager->doConnect();
}
