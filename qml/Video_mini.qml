import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.folderlistmodel
import QtMultimedia

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: video_mini
    Button {
        id: backGallery
        anchors.top: parent.top
        anchors.left: parent.left
        onClicked: {
            video_mini.visible = false
            gallery_page.visible = true
        }
    }
}
