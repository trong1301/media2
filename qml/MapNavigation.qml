import QtQuick 2.10
import QtQuick.Controls 2.12

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    TWText {
        text: "Map will be implemented asap"
        color: QmlStyling.color_C01
        font.pixelSize: QmlStyling.fontPixelSize_F3
        anchors.centerIn: parent
    }
}
