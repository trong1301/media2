import QtQuick 2.12
import QtQuick.Layouts 1.10
import QtQuick.Controls 2.0

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    objectName: "appSettingScreen"

    ListView {
        id: settingList
        objectName: "settingList"
        width: 534
        height: QmlStyling.contentHeight
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: 13
        }

        ScrollBar.vertical: ScrollBar {
            objectName: "scrollBar"
            width: 14
            policy: ScrollBar.AlwaysOn
            parent: settingList
            interactive: false
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            contentItem: Rectangle {
                radius: 20
                color: QmlStyling.color_C08
            }
            visible: settingList.contentHeight > settingList.height
        }

        model: 1
        delegate: Item {
            objectName: "settingItemListContainer"
            width: 534
            height: 86 * 5 // Remember change the number of setting here to caculate the height of list
            Column {
                id: settingColumnOptions
                objectName: "settingColumnOptions"
                width: 510
                height: 400
                anchors {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                }

                ItemSettingOptions {
                    id: backgroundSetting
                    objectName: "backgroundSetting"
                    itemText: qsTr("Background")
                    optionsText: SharedConstants.settingType.background[settingHandler.backgroundSetting].name
                    onChangeSettingAction: {
                        settingHandler.backgroundSetting++
                    }
                }

                ItemSettingOptions {
                    id: timeFormatSetting
                    objectName: "timeFormatSetting"
                    itemText: qsTr("Time Format")
                    optionsText: SharedConstants.settingType.time[settingHandler.timeSetting].name
                    onChangeSettingAction: {
                        settingHandler.timeSetting++
                    }
                }

                ItemSettingOptions {
                    id: speedUnitSetting
                    objectName: "speedUnitSetting"
                    itemText: qsTr("Speed Unit")
                    optionsText: SharedConstants.settingType.speedUnit[settingHandler.unitSetting].name
                    onChangeSettingAction: {
                        settingHandler.unitSetting++
                    }
                }

                ItemSettingOptions {
                    id: fontSetting
                    objectName: "fontSetting"
                    itemText: qsTr("Font Style")
                    optionsText: SharedConstants.settingType.fontStyle[settingHandler.fontSetting].name
                    onChangeSettingAction: {
                        settingHandler.fontSetting++
                    }
                }

                ItemSettingOptions {
                    id: themeSetting
                    objectName: "themeSetting"
                    itemText: qsTr("Themes")
                    optionsText: settingHandler.themeModel.themeName
                    onChangeSettingAction: {
                        settingHandler.themeSetting++
                    }
                }
            }
        }
    }
}
