import QtQuick 2.2
import Qt5Compat.GraphicalEffects

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    property int spd: 1
    property int sta: 0
    property int speedValue: speedometerModel.speed
    property var settingUnit: settingHandler.unitSetting

    MouseArea {
        id: backToMainGauge
        propagateComposedEvents: true
        anchors.fill: parent
        onClicked: {
            if (viewManager.viewState !== SharedConstants.viewTopIncomingCall
                    && viewManager.viewState !== SharedConstants.viewTopOutgoingCall)
                viewManager.requestChangeViewState(
                            SharedConstants.viewSubGauge,
                            SharedConstants.viewMainGauge)
        }
    }

    IndicatorBar {
        id: indicatorBar
        width: QmlStyling.contentSubRightWidth
        anchors.top: parent.top
        height: 58
        iconSpacing: 5
    }

    Item {
        id: speedContainer
        width: parent.width
        height: 210
        anchors {
            top: indicatorBar.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }

        Item {
            id: speedFrame
            width: 210
            height: 210
            anchors.centerIn: parent
            Rectangle {
                radius: width * 0.5
                anchors.fill: parent
                color: "transparent"
                RadialGradient {
                    anchors.fill: parent
                    gradient: Gradient {
                        GradientStop { position: 0.3; color: "transparent" }
                        GradientStop {
                            position: 0.49;
                            color: {
                                var result = "#a4a4a4"
                                if (speedValue !== 0) {
                                    if (speedValue >= 60) {
                                        result = "#C9050B"
                                    } else if (speedValue >= 40) {
                                        result = "#F6E200"
                                    } else {
                                        result = "#6EB325"
                                    }
                                }
                                return result
                            }
                        }
                        GradientStop { position: 0.5; color: "transparent" }
                    }
                }
                opacity: 0.8
            }

            TWText {
                id: speedText
                width: 210
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                state: "StaticColor"
                text: speedValue
                font.pixelSize: 80
                font.bold: true
            }
            TWText {
                id: speedUnit
                width: 71
                height: 29
                text: settingUnit ? qsTr("mph") : qsTr("km/h")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: QmlStyling.fontPixelSize_F2
                color: speedText.color
                anchors {
                    top: speedText.bottom
                    horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }

    Item {
        id: batteryContainer
        width: batteryBar.width + batIcon.width + 10 // 10 is distance between icon and bat level
        anchors {
            top: speedContainer.bottom
            topMargin: 60
            horizontalCenter: parent.horizontalCenter
        }
        BatteryLevels {
            id: batteryBar
            width: 180
            height: 30
            anchors.verticalCenterOffset: -7
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
        }
        Image {
            id: batIcon
            source: "qrc:/images/ICN_SICON_BATTICON1"
            width: QmlStyling.sIconWidth
            height: QmlStyling.sIconHeight
            anchors {
                left: batteryBar.right
                leftMargin: 10
                verticalCenter: batteryBar.verticalCenter
            }
        }

        TWText {
            id: endbat
            width: 6
            height: 14
            text: SharedConstants.emptyBattery
            font.pixelSize: QmlStyling.fontPixelSize_F4
            state: "StaticColor"
            anchors {
                top: batteryBar.bottom
                left: batteryBar.left
                leftMargin: 16
            }
        }
        TWText {
            id: fullbat
            width: 6
            height: 14
            text: SharedConstants.fullBattery
            font.pixelSize: QmlStyling.fontPixelSize_F4
            color: endbat.color
            anchors {
                top: batteryBar.bottom
                right: batteryBar.right
                rightMargin: 4
            }
        }
    }
}
