import QtQuick 2.2
//import QtGraphicalEffects 1.12
import Qt5Compat.GraphicalEffects
import TwoWheels.QmlStylingSingleton 1.0
Item {
    id: root
    property string source
    Image {
        id: iconImage
        anchors.fill: parent
        source: root.source
        layer {
            enabled: true
            effect: ColorOverlay {
                color: QmlStyling.color_C01
            }
        }
    }
}
