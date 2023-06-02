import QtQuick 2.2
import QtQuick.Layouts 1.1
import Qt5Compat.GraphicalEffects
import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Rectangle {
    id: root
    anchors.fill: parent

    Loader {
        id: backgroundLoader
        anchors.fill: parent
        sourceComponent: {
            var result = componenBG1
            var currentId = settingHandler.backgroundSetting
            switch (currentId) {
            case SharedConstants.settingType.background[0].id:
                result = componenBG1
                break
            case SharedConstants.settingType.background[1].id:
                result = componenBG2
                break
            case SharedConstants.settingType.background[2].id:
                result = componenBG3
                break
            default:
                break
            }
            return result
        }
    }

    Component {
        id: componenBG1
        Image {
            id: bgImageId
            anchors.top: parent.top
            width: QmlStyling.displayWidth
            height: QmlStyling.displayHeight
            source: "qrc:/images/road"

            Image {
                id: bgLeftImageId
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    horizontalCenterOffset: -227
                }
                source: "qrc:/images/left-lines"
                transformOrigin: Item.Center
                rotation: 70
            }

            Image {
                id: bgRightImageId
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    horizontalCenterOffset: 229
                }
                source: "qrc:images/right-lines"
                transformOrigin: Item.Center
                rotation: 111
            }
        }
    }

    Component {
        id: componenBG2
        Image {
            id: bgImageId
            anchors.top: parent.top
            width: QmlStyling.displayWidth
            height: QmlStyling.displayHeight
            source: "qrc:/images/background2"
        }
    }

    Component {
        id: componenBG3
        RadialGradient {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#15609e"
                }
                GradientStop {
                    position: 0.3
                    color: "#0c375a"
                }
                GradientStop {
                    position: 0.6
                    color: "#000000"
                }
            }
        }
    }
}
