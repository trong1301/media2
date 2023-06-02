import QtQuick 2.10
import QtQuick.Controls 2.12

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    property bool isMusicMode: mediaPlaylistModel.isMusicMode
    readonly property string twJsonFolder: mediaPlaylistModel.twMediaDataFolder
    readonly property string mediaState: mediaPlaylistModel.mediaState

    signal switchBetweenPlayingScreenAndMediaListAction

    // Load image to show in thumbnail
    function loadVideoImage(fileName) {
        if (fileName.includes(
                    '.mp4') || fileName.includes('.MP4') || fileName.includes(
                    '.wmv') || fileName.includes('.WMV') || fileName.includes(
                    '.avi') || fileName.includes('.AVI') || fileName.includes(
                    '.ogg') || fileName.includes('.OGG') || fileName.includes(
                    '.ogv') || fileName.includes('.OGV') || fileName.includes(
                    '.mkv') || fileName.includes('.MKV') || fileName.includes(
                    '.mov') || fileName.includes('.MOV')) {
            let name = fileName.split('.')
            let tempName = ("file:" + twJsonFolder + "images/" + name[0] + ".png").toString()
            return tempName
        } else {
            return "qrc:/images/ICN_XLICON_VIDEOICON.png"
        }
    }

    Loader {
        id: controlViewMedia
        width: parent.width
        height: parent.height
        anchors.fill: parent
        sourceComponent: isMusicMode ? musicGridViewComponent : videoGridViewComponent
    }

    Component {
        id: musicGridViewComponent
        Item {
            id: musicGridViewContainer
            objectName: "musicGridViewContainer"
            GridView {
                id: musidGridView
                clip: true
                cellWidth: 183
                cellHeight: (QmlStyling.contentHeight - 146) / 2
                anchors.fill: parent
                model: mediaMetaDataModel
                delegate: musicGridViewDelegate
                highlight: Rectangle {
                    opacity: 0.5
                    color: QmlStyling.color_C10
                }
                highlightFollowsCurrentItem: true
                boundsBehavior: Flickable.StopAtBounds
                currentIndex: mediaPlaylistModel.currentIndex
                Component.onCompleted: {
                    musidGridView.positionViewAtIndex(
                                currentIndex,
                                GridView.Beginning) // Jump to index
                }
                ScrollBar.vertical: ScrollBar {
                    objectName: "scrollBar"
                    width: 14
                    policy: ScrollBar.AlwaysOn
                    parent: musidGridView
                    interactive: false
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }
                    contentItem: Rectangle {
                        radius: 20
                        color: QmlStyling.color_C08
                    }
                    visible: musidGridView.contentHeight > musidGridView.height
                }
            }
            Component {
                id: musicGridViewDelegate
                Rectangle {
                    id: itemMusic
                    objectName: String(index)
                    height: musidGridView.cellHeight - 1
                    width: musidGridView.cellWidth - 1
                    color: QmlStyling.color_transparent
                    Rectangle {
                        id: borderItem
                        anchors.fill: parent
                        border.color: QmlStyling.color_C02
                        opacity: 0.1
                    }

                    TWText {
                        id: musicDuration
                        objectName: "musicDuration"
                        color: QmlStyling.color_C02
                        font.pixelSize: QmlStyling.fontPixelSize_F4_5
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                        anchors {
                            left: parent.left
                            bottom: musicName.top
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

                    Image {
                        id: diskImageIcon
                        objectName: "diskImageIcon"
                        width: 85
                        height: width
                        anchors {
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -5
                            horizontalCenter: parent.horizontalCenter
                        }
                        source: "qrc:/images/ICN_XLICON_MEDIADISK1.png"
                    }

                    TWText {
                        id: musicName
                        width: parent.width
                        anchors {
                            left: parent.left
                            bottom: parent.bottom
                        }
                        text: mediaTitle ? mediaTitle : mediaFileName
                        color: QmlStyling.color_C02
                        font.pixelSize: QmlStyling.fontPixelSize_F4_5
                        elide: Text.ElideRight
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
                            }
                            root.switchBetweenPlayingScreenAndMediaListAction()
                        }
                        onExited: {
                            isExited = true
                        }
                    }
                }
            }
        }
    }

    Component {
        id: videoGridViewComponent
        Item {
            id: videoGridViewContainer
            objectName: "videoGridViewContainer"
            GridView {
                id: videoGridView
                clip: true
                cellWidth: 183
                cellHeight: (QmlStyling.contentHeight - 146) / 2
                anchors.fill: parent
                model: mediaMetaDataModel
                delegate: videoGridViewDelegate
                highlight: Rectangle {
                    opacity: 0.5
                    color: QmlStyling.color_C10
                }
                highlightFollowsCurrentItem: true
                boundsBehavior: Flickable.StopAtBounds
                currentIndex: mediaPlaylistModel.currentIndex
                Component.onCompleted: {
                    videoGridView.positionViewAtIndex(
                                currentIndex,
                                GridView.Beginning) // Jump to index
                }
                ScrollBar.vertical: ScrollBar {
                    objectName: "scrollBar"
                    width: 14
                    policy: ScrollBar.AlwaysOn
                    parent: videoGridView
                    interactive: false
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }
                    contentItem: Rectangle {
                        radius: 20
                        color: QmlStyling.color_C08
                    }
                    visible: videoGridView.contentHeight > videoGridView.height
                }

                Component {
                    id: videoGridViewDelegate
                    Rectangle {
                        id: itemVideoContainer
                        objectName: String(index)
                        height: videoGridView.cellHeight - 1
                        width: videoGridView.cellWidth - 1
                        color: QmlStyling.color_transparent
                        Image {
                            id: itemVideo
                            objectName: String(index)
                            source: loadVideoImage(mediaFileName)
                            width: parent.width - 10
                            height: parent.height - 10
                            anchors.centerIn: parent
                            onStatusChanged: {
                                // Handle when add new video at runtime
                                if (itemVideo.status === Image.Error) {
                                    source = loadVideoImage("")
                                }
                            }

                            TWText {
                                id: videoTitle
                                objectName: "videoTitle"
                                width: parent.width - videoDuration.width - 10
                                color: QmlStyling.color_C01
                                anchors {
                                    bottom: parent.bottom
                                    left: parent.left
                                }
                                font {
                                    bold: true
                                    pixelSize: QmlStyling.fontPixelSize_F4
                                }
                                text: mediaTitle ? mediaTitle : mediaFileName
                                elide: Text.ElideRight
                            }

                            TWText {
                                id: videoDuration
                                objectName: "videoDuration"
                                horizontalAlignment: Text.AlignRight
                                verticalAlignment: Text.AlignVCenter
                                color: QmlStyling.color_C01
                                anchors {
                                    bottom: parent.bottom
                                    right: parent.right
                                }

                                font {
                                    bold: true
                                    pixelSize: QmlStyling.fontPixelSize_F4
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
                        }

                        Rectangle {
                            id: borderItem
                            anchors.fill: parent
                            border.color: QmlStyling.color_C02
                            opacity: 0.1
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
                                    itemVideoContainer.color = QmlStyling.color_transparent
                                }
                                root.switchBetweenPlayingScreenAndMediaListAction()
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
