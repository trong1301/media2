import QtQuick 2.12
import QtQuick.Layouts 1.10
import QtQuick.Controls 2.0

import TwoWheels.SharedConstantsSingleton 1.0

Text {
    id: root

    FontLoader {
        id: fontUpdate
        source: SharedConstants.settingType.fontStyle[settingHandler.fontSetting].font
    }
    font.family: fontUpdate.name

    states: [
        State {
            name: "StaticColor"
            PropertyChanges {
                target: root
                color: settingHandler.themeModel.systemTextColor
            }
        },
        State {
            name: "DynamicColor"
            PropertyChanges {
                target: root
                color: settingHandler.themeModel.appTextColor
            }
        }
    ]
}
