import QtQuick 2.10
import QtQuick.Layouts 1.1

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Loader {
    id: root
    width: parent.width
    height: parent.height
    readonly property bool isMusicMode: mediaPlaylistModel.isMusicMode
    readonly property var currentMediaPlaying: mediaPlaylistModel.currentMediaPlaying

    sourceComponent: Item {
        anchors.fill: parent
        Image {
            id: musicIconTopScreen
            objectName: "musicIconTopScreen"
            width: QmlStyling.sIconWidth
            height: QmlStyling.sIconHeight
            source: "qrc:/images/ICN_SICON_MUSIC_WHITE.png"
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
        }

        Item {
            id: songNameContainer
            objectName: "songNameContainer"
            width: root.width - musicIconTopScreen.width
            height: musicIconTopScreen.height
            clip: true
            anchors {
                verticalCenter: parent.verticalCenter
                left: musicIconTopScreen.right
                leftMargin: 10
            }

            TWText {
                id: songName
                objectName: "songName"
                height: parent.height
                width: parent.width

                text: currentMediaPlaying.mediaTitle ? currentMediaPlaying.mediaTitle : currentMediaPlaying.mediaFileName ? currentMediaPlaying.mediaFileName : "Unknown"
                horizontalAlignment: Text.AlignLeft
                color: QmlStyling.color_C01
                font.pixelSize: QmlStyling.fontPixelSize_F2
                anchors.verticalCenter: parent.verticalCenter

                NumberAnimation on x {
                    running: true
                    from: songName.width
                    to: -(songName.width)
                    duration: 10000
                    loops: Animation.Infinite
                    alwaysRunToEnd: true
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                viewManager.requestChangeViewState(
                            SharedConstants.viewSubGauge,
                            SharedConstants.viewSubGaugeMedia)
            }
        }
    }
}
