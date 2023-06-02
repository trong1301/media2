import QtQuick 2.2
//import QtGraphicalEffects 1.12

Item {
    id: root
    property color color: "#ffffff"
    property string source
    Image {
        id: iconImage
        anchors.centerIn: parent
        source: root.source
    }
//    ColorOverlay {
//        anchors.fill: iconImage
//        source: iconImage
//        color: root.color
//    }
}
