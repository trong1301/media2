import QtQuick 2.10
import QtQuick.Controls 2.12
//import QtMultimedia 5.15
import QtMultimedia
import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0
Item {
    id: rootMediaPlayer
    readonly property bool isMusicMode: mediaPlaylistModel.isMusicMode
    readonly property var currentMediaPlaying: mediaPlaylistModel.currentMediaPlaying
    property bool isListView: true

    function switchBetweenPlayingScreenAndMediaList() {
        // QuanTong
        // Due to use loader could not keep the VideoOutput sync with C++
        // Have to use visible as a workaround solution :)
        if (musicAndVideoLoader.visible) {
            musicAndVideoLoader.visible = false
            mediaListAndGridItem.visible = true
        } else {
            musicAndVideoLoader.visible = true
            mediaListAndGridItem.visible = false
        }
    }

    Image {
        id: background
        anchors.fill: parent
        source: "qrc:/images/MEDIA_BACKGROUND.png"
    }

    Loader {
        id: musicAndVideoLoader
        visible: true
        objectName: "mediaLoader"
        width: QmlStyling.contentSubLeftWidth
        height: QmlStyling.contentHeight - 100
        anchors {
            top: parent.top
            left: parent.left
        }
        sourceComponent: isMusicMode ? musicPlayScreenComponent : videoPlayScreenComponent
    }

    Component {
        id: musicPlayScreenComponent
        Item {
            id: musicPlayScreenItem
            anchors.horizontalCenter: parent.horizontalCenter
            objectName: "musicPlayScreenItem"
            Item {
                id: songNameContainer
                objectName: "songNameContainer"
                width: 350
                height: QmlStyling.sIconHeight
                clip: true
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    topMargin: 25
                }

                TWText {
                    id: marqueeSongName
                    height: songNameContainer.height
                    text: currentMediaPlaying.mediaTitle ? currentMediaPlaying.mediaTitle : currentMediaPlaying.mediaFileName ? currentMediaPlaying.mediaFileName : "Unknown"
                    horizontalAlignment: Text.AlignHCenter
                    color: QmlStyling.color_C01
                    font.pixelSize: QmlStyling.fontPixelSize_F1
                    NumberAnimation on x {
                        id: marqueeTextAnimation
                        from: 350
                        to: -(marqueeSongName.width)
                        duration: 7000
                        loops: Animation.Infinite
                    }
                    onTextChanged: {
                        marqueeTextAnimation.restart()
                    }
                }
            }

            Image {
                readonly property int localMediaState: mediaPlaylistModel.mediaState
                id: diskMusic
                objectName: "diskMusic"
                width: 180
                height: 180
                source: "qrc:/images/ICN_XXLICON_MEDIADISK.png"
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: 20
                }
                onLocalMediaStateChanged: {
                    // Handle image disk rotation
                    if (localMediaState === SharedConstants.mediaPlayingState) {
                        if (imgRotation.paused) {
                            imgRotation.resume()
                        } else {
                            imgRotation.start()
                        }
                    } else {
                        if (imgRotation.running) {
                            imgRotation.pause()
                        }
                    }
                }

                RotationAnimation on rotation {
                    id: imgRotation
                    loops: Animation.Infinite
                    from: 0
                    to: 360
                    duration: 15000
                    running: false
                }
            }
        }
    }


//    Component {
//        id: videoPlayScreenComponent

//        Item {
//            id: videoPlayScreenItem
//            anchors.fill: parent
//            objectName: "videoPlayScreenItem"

//            VideoOutput {
//                id: videoOutputView
//                objectName: "videoOutputView"
//                z: 1
//                anchors.fill: parent
//                fillMode: VideoOutput.Stretch
//                flushMode: VideoOutput.FirstFrame // Avoid flick background when change between videos
//                source: mediaPlaylistModel
////                videoSink: videoOutput.videoSink

//                TWText {
//                    id: videoPlayingTitle
//                    objectName: "videoPlayingTitle"
//                    width: QmlStyling.contentSubLeftWidth
//                    text: currentMediaPlaying.mediaTitle ? currentMediaPlaying.mediaTitle : currentMediaPlaying.mediaFileName ? currentMediaPlaying.mediaFileName : "Unknown"
//                    color: QmlStyling.color_C10
//                    elide: Text.ElideRight
//                    font.pixelSize: QmlStyling.fontPixelSize_F3
//                    anchors {
//                        left: videoOutputView.left
//                        leftMargin: 10
//                        top: videoOutputView.top
//                    }
//                }
//            }

////            Component.onCompleted: player.start()


//        }
//    }

    Item {
        id: mediaListAndGridItem
        visible: false
        anchors.fill: parent
        Item {
            id: topItems
            objectName: "topItems"
            width: QmlStyling.contentSubLeftWidth
            height: 46
            anchors {
                top: parent.top
                left: parent.left
            }

            Item {
                id: leftItems
                objectName: "leftItems"
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                width: playListMediaIcon.width + playListText.width
                height: parent.height
                Image {
                    id: playListMediaIcon
                    objectName: "playListMediaIcon"
                    width: QmlStyling.sIconWidth
                    height: QmlStyling.sIconHeight
                    source: "qrc:/images/ICN_SICON_PLAYLISTMEDIA.png"
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                }

                TWText {
                    id: playListText
                    objectName: "playListText"
                    text: SharedConstants.mediaPlaylistTitle
                    color: QmlStyling.color_C01
                    font {
                        bold: true
                        pixelSize: QmlStyling.fontPixelSize_F3
                    }
                    anchors {
                        left: playListMediaIcon.right
                        leftMargin: 5
                        verticalCenter: parent.verticalCenter
                    }
                }
            }

            Item {
                id: rightItems
                objectName: "rightItems"
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
                width: iconViewType.width + comboBoxViewType.width
                height: parent.height

                Image {
                    id: iconViewType
                    objectName: "iconViewType"
                    width: QmlStyling.sIconWidth
                    height: QmlStyling.sIconHeight
                    source: isListView ? "qrc:/images/ICN_SICON_GRIDICON.png" : "qrc:/images/ICN_SICON_LISTICON.png"
                    anchors {
                        right: comboBoxViewType.left
                        rightMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: isListView = !isListView
                    }
                }

                ComboBox {
                    id: comboBoxViewType
                    objectName: "comboBoxViewType"
                    width: 120
                    height: iconViewType.height
                    currentIndex: isMusicMode ? 0 : 1
                    font.pixelSize: QmlStyling.fontPixelSize_F4
                    anchors {
                        right: parent.right
                        rightMargin: 13
                        verticalCenter: parent.verticalCenter
                    }
                    background: Rectangle {
                        anchors.fill: parent
                        border.color: QmlStyling.color_C02
                    }
                    delegate: ItemDelegate {
                        width: comboBoxViewType.width
                        contentItem: Rectangle {
                            anchors.fill: parent
                            border.color: QmlStyling.color_C02
                            border.width: 1
                            TWText {
                                color: QmlStyling.color_C02
                                font.pixelSize: QmlStyling.fontPixelSize_F4
                                text: modelData

                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                    leftMargin: 12
                                }
                            }
                        }
                    }

                    model: [SharedConstants.mediaMusicModeTitle, SharedConstants.mediaVideoModeTitle]

                    onActivated: {
                        if (textAt(index) === SharedConstants.mediaMusicModeTitle) {
                            mediaPlaylistModel.isMusicMode = true
                        } else {
                            mediaPlaylistModel.isMusicMode = false
                        }
                    }
                    // Stop bounds of combobox
                    Component.onCompleted: {
                        comboBoxViewType.popup.contentItem.boundsBehavior = Flickable.StopAtBounds
                    }
                }
            }
        }

        Loader {
            id: mediaListAndGridLoader
            objectName: "mediaListAndGridLoader"
            anchors {
                left: parent.left
                top: topItems.bottom
            }
            width: QmlStyling.contentSubLeftWidth
            height: QmlStyling.contentHeight - topItems.height - mediaControlBottomBar.height
            sourceComponent: isListView ? mediaListViewComponent : mediaGridViewComponent
        }

        Component {
            id: mediaListViewComponent
            MediaListView {
                id: mediaListView
                objectName: "mediaListView"
                anchors.fill: parent
                onSwitchBetweenPlayingScreenAndMediaListAction: switchBetweenPlayingScreenAndMediaList()
            }
        }

        Component {
            id: mediaGridViewComponent
            MediaGridView {
                id: mediaGridView
                objectName: "mediaGridView"
                anchors.fill: parent
                onSwitchBetweenPlayingScreenAndMediaListAction: switchBetweenPlayingScreenAndMediaList()
            }
        }
    }

    MediaControlBottombar {
        id: mediaControlBottomBar
        objectName: "mediaControlBottomBar"
        width: QmlStyling.contentSubLeftWidth
        height: 100
        color: "transparent"
        isPlayScreen: musicAndVideoLoader.visible
        anchors {
            left: parent.left
            bottom: parent.bottom
        }
        onSwitchBetweenPlayingScreenAndMediaListAction: switchBetweenPlayingScreenAndMediaList()
    }

    Component.onDestruction: {
        if (!isMusicMode) {
            mediaPlaylistModel.resetMedia()
        }
    }
}
