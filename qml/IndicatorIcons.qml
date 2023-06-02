import QtQuick 2.2
//import QtGraphicalEffects 1.12
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts 1.3

import TwoWheels.QmlStylingSingleton 1.0

Rectangle {
    property var listModel

    id: bgIconId

    width: QmlStyling.xsIconWidth
    height: QmlStyling.xsIconHeight
    radius: QmlStyling.xsIconHeight / 2
    visible: listModel.visible
    border.color: listModel.colorBorderBgIconInactive
    border.width: 1
    state: stateIcon

    gradient: Gradient {
        GradientStop {
            id: gradient1Id
            position: 0.0
            color: "#ffffff"
        }
        GradientStop {
            id: gradient2Id
            position: 0.5
            color: listModel.colorBorderBgIconInactive
        }
    }

    layer.enabled: false
//    layer.effect: DropShadow {
//        id: layershadowId
//        transparentBorder: true
//        horizontalOffset: 0
//        verticalOffset: 0
//        color: listModel.colorShadowBorderBgIcon
//        radius: 8
//        samples: 9
//    }

    IconsOverLay {
        id: iconsOverlayId
        color: "#bfbfbf"
        anchors.centerIn: bgIconId
        source: listModel.imageSource
    }

    states: [
        State {
            name: "Inactive"
            PropertyChanges {
                target: bgIconId
                border.color: listModel.colorBorderBgIconInactive
                border.width: 1
                layer.enabled: false
            }
            PropertyChanges {
                target: gradient2Id
                color: listModel.colorBgIconInactive
            }
        },
        State {
            name: "Active"
            PropertyChanges {
                target: bgIconId
                border.color: listModel.colorBorderBgIconActive
                border.width: 2
                layer.enabled: true
            }
            PropertyChanges {
                target: iconsOverlayId
                color: "#ffffff"
            }
            PropertyChanges {
                target: gradient2Id
                color: listModel.nameIcon === "sideStand" ? "#da382e" : listModel.colorBgIconActive
            }
        }
    ]
}
