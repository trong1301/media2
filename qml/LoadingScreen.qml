import QtQuick 2.10
import QtQuick.Controls 2.12

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    Rectangle {
        id: loadingContainer
        objectName: "loadingContainer"
        anchors.fill: parent
        color: QmlStyling.color_C02
        z: 1

        BusyIndicator {
            id: loadingScreen
            objectName: "loadingScreen"
            anchors.centerIn: parent
            width: QmlStyling.contentSubLeftWidth / 2
            height: QmlStyling.contentHeight / 2
            palette.dark: QmlStyling.color_C01
            running: loadingContainer.visible
            TWText {
                id: loadingText
                objectName: "loadingText"
                anchors.centerIn: parent
                color: QmlStyling.color_C01
                text: "Loading data...!"
            }
        }

        TWText {
            id: closeButton
            objectName: "closeButton"
            font.pixelSize: QmlStyling.fontPixelSize_F0
            color: QmlStyling.color_C01
            text: "X"
            anchors {
                right: parent.right
                rightMargin: 22
                top: parent.top
                topMargin: 15
            }
            MouseArea {
                anchors.centerIn: parent
                width: QmlStyling.xsIconWidth
                height: QmlStyling.xsIconHeight
                onClicked: {
                    viewManager.requestChangeViewState(
                                SharedConstants.viewSubGaugeLoadingScreen,
                                SharedConstants.viewSubGauge)
                }
            }
        }
    }
}
