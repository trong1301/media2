import QtQuick 2.2
import QtQuick.Layouts 1.1
//import QtGraphicalEffects 1.12

import TwoWheels.QmlStylingSingleton 1.0

Item {
    id: root
    objectName: "popUpScreen"
    width: parent.width
    height: parent.height

    Rectangle {
        id: popUpMessage
        objectName: "popUpMessage"
        anchors.fill: parent
        color: QmlStyling.color_C01
    }

    Image {
        id: msgIcon
        objectName: "msgIcon"
        width: QmlStyling.sIconWidth
        height: QmlStyling.sIconHeight
        source: "qrc:/images/chat"
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
//        layer {
//            enabled: true
//            effect: ColorOverlay {
//                color: QmlStyling.color_C02
//            }
//        }
    }

    TWText {
        id: thumbnailUser
        width: thumbnailUser.implicitWidth > 300 ? 300 : thumbnailUser.implicitWidth
        anchors {
            left: msgIcon.right
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        elide: Text.ElideRight
        text: phoneControllerModel.smsPopUp.address
        color: QmlStyling.color_C02
        font.pixelSize: QmlStyling.fontPixelSize_F1
    }

    TWText {
        id: thumbnailText
        width: parent.width - msgIcon.width - thumbnailUser.width - 40
        anchors {
            left: thumbnailUser.right
            verticalCenter: parent.verticalCenter
        }
        elide: Text.ElideRight
        text: ": " + phoneControllerModel.smsPopUp.body

        color: QmlStyling.color_C02
        font.pixelSize: QmlStyling.fontPixelSize_F1
    }
}
