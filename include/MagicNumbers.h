#ifndef MAGICNUMBERS_H
#define MAGICNUMBERS_H

// Qt include
#include <memory>
#include <QString>

namespace Helper {
namespace MagicNumbers {

namespace TransportType {
static const std::string USB_AOA("USB_AOA");
static const std::string USB_IOS("USB_IOS");
static const std::string BLUETOOTH("BLUETOOTH");
static const std::string BLUETOOTH_IOS("BLUETOOTH_IOS");
static const std::string WIFI("WIFI");
static const std::string USB_IOS_HOST_MODE("USB_IOS_HOST_MODE");
static const std::string USB_IOS_DEVICE_MODE("USB_IOS_DEVICE_MODE");
static const std::string CARPLAY_WIRELESS_IOS("CARPLAY_WIRELESS_IOS");
static const std::string CLOUD_WEBSOCKET("CLOUD_WEBSOCKET");
static const std::string WEBENGINE_WEBSOCKET("WEBENGINE_WEBSOCKET");
}

namespace ViewScreen {
static const std::string MAINGAUGE("MainGauge");
static const std::string SUBGAUGE("SubGauge");
static const std::string ANYWHERE("AnyWhere");
static const std::string SUBGAUGE_SETTINGS("SubGaugeSettings");
static const std::string SUBGAUGE_PHONE("SubGaugePhone");
static const std::string SUBGAUGE_PHONE_APPLICATIONS("SubGaugePhoneApplications");
static const std::string SUBGAUGE_PHONE_CALL_LOG("SubGaugePhoneCallLog");
static const std::string SUBGAUGE_PHONE_CALL_LOG_LIST("SubGaugePhoneCallLogList");
static const std::string SUBGAUGE_PHONE_CALL_LOG_ITEM("SubGaugePhoneCallLogItem");
static const std::string SUBGAUGE_PHONE_CONTACT("SubGaugePhoneContact");
static const std::string SUBGAUGE_PHONE_CONTACT_LIST("SubGaugePhoneContactList");
static const std::string SUBGAUGE_PHONE_CONTACT_ITEM("SubGaugePhoneContactItem");
static const std::string SUBGAUGE_PHONE_SMS("SubGaugePhoneSMS");
static const std::string SUBGAUGE_PHONE_SMS_LIST("SubGaugePhoneSMSList");
static const std::string SUBGAUGE_PHONE_SMS_ITEM("SubGaugePhoneSMSItem");
static const std::string SUBGAUGE_PHONE_MAP_NAVIGATION("SubGaugePhoneMapNavigation");
static const std::string TOP_INCOMING_CALL("TopIncomingCall");
static const std::string TOP_OUTGOING_CALL("TopOutgoingCall");
static const std::string SUBGAUGE_MEDIA("SubGaugeMedia");
static const std::string SUBGAUGE_LOADING_SCREEN("SubGaugeLoadingScreen");
static const std::string SUBGAUGE_VIDEO("SubGaugeVideo");
static const std::string SUBGAUGE_CAMERA("SubGaugeCamera");
static const std::string SUBGAUGE_GALLERY("SubGaugeGallery");
static const std::string SUBGAUGE_VIDEOmini("SubGaugeVideomini");
}

} /* namespace MagicNumbers */
} /* namespace Helper */

namespace TwoWheelsTypes {
struct Speedo {
    float speed;
    float mileage;
    QString speed_status;

    Speedo()
    {
        speed = 0;
        mileage = 0;
        speed_status = "";
    }
};
typedef struct Speedo Speedo;

struct Battery {
    int voltage;
    int soc_display;

    Battery()
    {
        voltage = 0;
        soc_display = 0;
    }
};
typedef struct Battery Battery;

struct Indicators {
    uint8_t turn_left;
    uint8_t side_stand;
    uint8_t reverse_mode;
    uint8_t head_light;
    uint8_t engine_trouble;
    uint8_t oil_lower;
    uint8_t coolant_tempt;
    uint8_t abs;
    uint8_t turn_right;

    Indicators()
    {
        turn_left = 0;
        side_stand = 0;
        reverse_mode = 0;
        head_light = 0;
        engine_trouble = 0;
        oil_lower = 0;
        coolant_tempt = 0;
        abs = 0;
        turn_right = 0;
    }
};
typedef struct Indicators Indicators;

// SMSMessage struct
struct SMSMessage {
    QString address_;
    QString body_;
    QString date_;
    uint32_t read_;
    uint32_t type_;

    SMSMessage()
    {
        address_ = "";
        body_ = "";
        date_ = "";
        read_ = 0;
        type_ = 1;
    }
};
typedef struct SMSMessage SMSMessage;

enum SettingTypes{
    SettingTimes = 0,
    SettingBackGrounds,
    SettingUnits,
    SettingFonts,
    SettingTheme
};

enum class SettingTimes{
    FORMAT_12H = 0,
    FORMAT_24H,
    NUM_OF_SETTING = 2
};

enum class SettingBackGrounds{
    BG1 = 0,
    BG2,
    NUM_OF_SETTING = 3
};

enum class SettingUnits{
    KILOMETERS = 0,
    MILES,
    NUM_OF_SETTING = 2,
};

enum class SettingFonts{
    FONT1 = 0,
    FONT2,
    NUM_OF_SETTING = 7
};

enum class SettingTheme{
    THEME1 = 0,
    THEME2,
    THEME3,
    NUM_OF_SETTING = 3
};


static const QString UNKNOWN_USER_CALLING("Unknown");

}/* namespace TwoWheelsTypes */
#endif // MAGICNUMBERS_H
