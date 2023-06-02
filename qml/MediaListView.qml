import QtQuick 2.10
import QtQuick.Controls 2.12

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    readonly property bool isMusicMode: mediaPlaylistModel.isMusicMode
    readonly property string mediaState: mediaPlaylistModel.mediaState

    signal switchBetweenPlayingScreenAndMediaListAction

    Loader {
        id: controlViewMedia
        width: parent.width
        height: parent.height
        anchors.fill: parent
        sourceComponent: isMusicMode ? musicListViewComponent : videoListViewComponent
    }

    Component {
        id: musicListViewComponent
        Item {
            id: musicListViewContainer
            objectName: "musicListViewContainer"
            ListView {
                id: musicListView
                clip: true
                anchors.fill: parent
                model: mediaMetaDataModel
                delegate: musicListViewDelegate
                highlight: Rectangle {
                    color: QmlStyling.color_C10
                }
                highlightFollowsCurrentItem: true
                boundsBehavior: Flickable.StopAtBounds
                currentIndex: mediaPlaylistModel.currentIndex
                Component.onCompleted: {
                    musicListView.positionViewAtIndex(
                                currentIndex, ListView.Center) // Jump to index
                }
                ScrollBar.vertical: ScrollBar {
                    objectName: "scrollBar"
                    width: 14
                    policy: ScrollBar.AlwaysOn
                    parent: musicListView
                    interactive: false
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }
                    contentItem: Rectangle {
                        radius: 20
                        color: QmlStyling.color_C08
                    }
                    visible: musicListView.contentHeight > musicListView.height
                }

                Component {
                    id: musicListViewDelegate
                    Rectangle {
                        id: itemMusic
                        objectName: String(index)
                        height: 55
                        width: 546
                        color: QmlStyling.color_transparent

                        Rectangle {
                            id: borderItem
                            anchors.fill: parent
                            border.color: QmlStyling.color_C02
                            opacity: 0.1
                        }

                        Image {
                            id: imageMusic
                            objectName: "imageMusic"
                            width: QmlStyling.sIconWidth
                            height: QmlStyling.sIconHeight
                            anchors {
                                verticalCenter: parent.verticalCenter
                                left: parent.left
                                leftMargin: 10
                            }
                            source: "qrc:/images/ICN_XLICON_MEDIADISK.png"
                        }

                        TWText {
                            id: songName
                            objectName: "songName"
                            width: parent.width - imageMusic.width
                                   - musicDuration.width - 20 // 2 margin spaces
                            height: 30
                            anchors {
                                left: imageMusic.right
                                leftMargin: 10
                                verticalCenter: parent.verticalCenter
                            }
                            text: mediaTitle ? mediaTitle : mediaFileName
                            font.pixelSize: QmlStyling.fontPixelSize_F3
                            elide: Text.ElideRight
                        }

                        TWText {
                            id: musicDuration
                            objectName: "musicDuration"
                            color: QmlStyling.color_C02
                            horizontalAlignment: Text.AlignRight
                            font.pixelSize: QmlStyling.fontPixelSize_F3
                            anchors {
                                right: parent.right
                                rightMargin: 5
                                verticalCenter: parent.verticalCenter
                            }

                            text: {
                                if (mediaDuration !== 0) {
                                    var minuteAsSec = mediaDuration
                                    var minuteTotal = ('0' + Math.floor(
                                                           minuteAsSec / 60)).slice(
                                                -2)
                                    var secondTotal = ('0' + (minuteAsSec % 60)).slice(
                                                -2)

                                    return minuteTotal + ":" + secondTotal
                                } else {
                                    return "--:--"
                                }
                            }
                        }

                        MouseArea {
                            property bool isExited: false
                            anchors.fill: parent
                            onPressed: {
                                isExited = false
                            }
                            onReleased: {
                                if (!isExited) {
                                    mediaPlaylistModel.currentIndex = index
                                    if (mediaState !== SharedConstants.mediaPlayingState) {
                                        mediaPlaylistModel.startPlaying()
                                    }
                                    itemMusic.color = QmlStyling.color_transparent
                                    root.switchBetweenPlayingScreenAndMediaListAction()
                                }
                            }
                            onExited: {
                                isExited = true
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: videoListViewComponent
        Item {
            id: videoListViewContainer
            objectName: "videoListViewContainer"
            ListView {
                id: videoListView
                clip: true
                anchors.fill: parent
                model: mediaMetaDataModel
                delegate: videoListViewDelegate
                highlight: Rectangle {
                    color: QmlStyling.color_C10
                }
                highlightFollowsCurrentItem: true
                boundsBehavior: Flickable.StopAtBounds
                currentIndex: mediaPlaylistModel.currentIndex
                Component.onCompleted: {
                    videoListView.positionViewAtIndex(
                                currentIndex, ListView.Center) // Jump to index
                }
                ScrollBar.vertical: ScrollBar {
                    objectName: "scrollBar"
                    width: 14
                    policy: ScrollBar.AlwaysOn
                    parent: videoListView
                    interactive: false
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }
                    contentItem: Rectangle {
                        radius: 20
                        color: QmlStyling.color_C08
                    }
                    visible: videoListView.contentHeight > videoListView.height
                }
                Component {
                    id: videoListViewDelegate
                    Rectangle {
                        id: itemVideo
                        objectName: String(index)
                        height: 55
                        width: 546
                        color: QmlStyling.color_transparent

                        Rectangle {
                            id: borderItem
                            anchors.fill: parent
                            border.color: QmlStyling.color_C02
                            opacity: 0.1
                        }

                        Image {
                            id: imageVideo
                            width: QmlStyling.sIconWidth
                            height: QmlStyling.sIconHeight
                            anchors {
                                verticalCenter: parent.verticalCenter
                                left: parent.left
                                leftMargin: 10
                            }
                            source: "qrc:/images/ICN_XLICON_BVIDEOICON.png"
                        }

                        TWText {
                            id: videoTitle
                            objectName: "videoTitle"
                            width: parent.width - imageVideo.width
                                   - videoDuration.width - 20 // 2 margin spaces
                            height: 30
                            color: QmlStyling.color_C02
                            horizontalAlignment: Text.AlignLeft
                            anchors {
                                left: imageVideo.right
                                leftMargin: 10
                                verticalCenter: parent.verticalCenter
                            }
                            text: mediaTitle ? mediaTitle : mediaFileName
                            font.pixelSize: QmlStyling.fontPixelSize_F3
                            elide: Text.ElideRight
                        }

                        TWText {
                            id: videoDuration
                            objectName: "videoDuration"
                            color: QmlStyling.color_C02
                            horizontalAlignment: Text.AlignRight
                            font.pixelSize: QmlStyling.fontPixelSize_F3
                            anchors {
                                right: parent.right
                                rightMargin: 5
                                verticalCenter: parent.verticalCenter
                            }

                            text: {
                                if (mediaDuration !== 0) {
                                    var minuteAsSec = mediaDuration
                                    var minuteTotal = ('0' + Math.floor(
                                                           minuteAsSec / 60)).slice(
                                                -2)
                                    var secondTotal = ('0' + (minuteAsSec % 60)).slice(
                                                -2)

                                    return minuteTotal + ":" + secondTotal
                                } else {
                                    return "--:--"
                                }
                            }
                        }

                        MouseArea {
                            property bool isExited: false
                            anchors.fill: parent
                            onPressed: {
                                isExited = false
                            }
                            onReleased: {
                                if (!isExited) {
                                    mediaPlaylistModel.currentIndex = index
                                    if (mediaState !== SharedConstants.mediaPlayingState) {
                                        mediaPlaylistModel.startPlaying()
                                    }
                                    itemVideo.color = QmlStyling.color_transparent
                                    root.switchBetweenPlayingScreenAndMediaListAction()
                                }
                            }
                            onExited: {
                                isExited = true
                            }
                        }
                    }
                }
            }
        }
    }
}
