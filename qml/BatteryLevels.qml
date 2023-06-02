import QtQuick 2.2
import TwoWheels.QmlStylingSingleton 1.0

Item {
    id: batContainer
    property int batteryValue: batteryViewModel.batteryLevel

    Image {
        id: batImage
        source: "qrc:/images/ICN_HOR_BATLEVEL3"
        width: 200
        height: 30
        anchors {
            bottom: parent.bottom
            left: parent.left
        }
        Rectangle {
            id: batStatus
            color: {
                var colorResult = "transparent"
                if (batteryValue > 50) {
                    colorResult = "#6EB325"
                } else if (batteryValue > 30) {
                    colorResult = "#F67600"
                } else {
                    colorResult = "#C9050B"
                }
                return colorResult
            }
            width: batteryValue * 1.52
            height: 22
            z: -1
            anchors {
                bottom: parent.bottom
                bottomMargin: 4
                left: parent.left
                leftMargin: 20
            }
        }
    }
}
