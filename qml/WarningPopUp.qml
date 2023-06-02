import QtQuick 2.2
import QtQuick.Window 2.1

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    objectName: "warningPopupScreen"
    width: parent.width
    height: parent.height
    property bool isTapped: false
    visible: speedometerModel.speed >= 10 && !isTapped

    Rectangle {
        id: warningBgContainer
        anchors.fill: parent
        color: QmlStyling.color_C01

        Item {
            id: warningContentContainer
            anchors.centerIn: parent
            width: warningIncomingImg.width + warningIncomingText.implicitWidth + 20
            height: parent.height
            Image {
                id: warningIncomingImg
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                width: 80 //QmlStyling.mIconWidth
                height: 80 //QmlStyling.mIconHeight
                source: "qrc:/images/ICN_LICON_WARNING"
            }

            Text {
                id: warningIncomingText
                text: "No calling while riding.\nTap to close this warning!"
                color: QmlStyling.color_C02
                anchors {
                    left: warningIncomingImg.right
                    leftMargin: 20
                    verticalCenter: parent.verticalCenter
                }
                font.pixelSize: QmlStyling.fontPixelSize_F2
                elide: Text.ElideRight
            }
        }
    }
    MouseArea {
        id: warningPopupMA
        anchors.fill: parent
        enabled: root.visible
        onClicked: {
            isTapped = true
        }
    }
}
