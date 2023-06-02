import QtQuick 2.10
import QtQuick.Controls 2.12

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Rectangle {
    id: root
    readonly property int mediaState: mediaPlaylistModel.mediaState
    readonly property bool isMusicMode: mediaPlaylistModel.isMusicMode
    readonly property int mediaDuration: mediaPlaylistModel.duration
    readonly property int mediaPosition: mediaPlaylistModel.position
    readonly property string minuteTotal: ('0' + Math.floor(
                                               mediaDuration / 60)).slice(-2)
    readonly property string secondTotal: ('0' + (mediaDuration % 60)).slice(-2)
    readonly property string runTimeMinute: ('0' + Math.floor(
                                                 mediaPosition / 60)).slice(-2)
    readonly property string runTimeSecond: ('0' + (mediaPosition % 60)).slice(
                                                -2)
    readonly property var currentMediaPlaying: mediaPlaylistModel.currentMediaPlaying
    property bool isPlayScreen

    signal switchBetweenPlayingScreenAndMediaListAction

    Item {
        id: durationContainer
        objectName: "durationContainer"
        width: QmlStyling.contentSubLeftWidth
        height: 10
        visible: isPlayScreen
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: isPlayScreen ? 7 : 0
        }
        TWText {
            id: runTimeDuration
            objectName: "runTimeDuration"
            anchors {
                verticalCenter: parent.verticalCenter
                right: durationSlider.left
                rightMargin: 10
            }
            width: 80
            text: root.runTimeMinute + ":" + root.runTimeSecond
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            color: QmlStyling.color_C01
            font.pixelSize: QmlStyling.fontPixelSize_F5
        }

        Slider {
            id: durationSlider
            width: 300
            height: 4
            value: mediaPosition
            from: 0
            to: mediaDuration
            anchors.centerIn: parent
            background: null
            handle: null
            snapMode: Slider.NoSnap

            onValueChanged: {
                // TODO: Change position from QML while playing music
                mediaPlaylistModel.position = value
            }
            Rectangle {
                id: behindPortionDuration
                objectName: "behindPortionDuration"
                color: QmlStyling.color_C08
                anchors.left: parent.left
                width: parent.width
                height: parent.height
            }
            Rectangle {
                id: frontPortionDuration
                objectName: "frontPortionDuration"
                color: QmlStyling.color_C01
                anchors.left: parent.left
                width: mediaPosition * (parent.width / mediaDuration)
                height: parent.height
            }
            Rectangle {
                id: dotHandleDuration
                x: {
                    var widthWithoutDot = parent.width - width
                    var result = 0
                    if (mediaPosition * (widthWithoutDot / mediaDuration) > widthWithoutDot) {
                        result = widthWithoutDot
                    } else {
                        result = mediaPosition * (widthWithoutDot / mediaDuration)
                    }
                    return result
                }
                objectName: "dotHandleDuration"
                anchors.verticalCenter: parent.verticalCenter
                width: 22
                height: 22
                radius: 10
                color: parent.pressed ? QmlStyling.color_C09 : QmlStyling.color_C01
                border.color: QmlStyling.color_C04
            }
        }

        TWText {
            id: totalDuration
            objectName: "totalDuration"
            width: 80
            text: root.minuteTotal + ":" + root.secondTotal
            anchors {
                verticalCenter: parent.verticalCenter
                left: durationSlider.right
                leftMargin: 10
            }
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            color: QmlStyling.color_C01
            font.pixelSize: QmlStyling.fontPixelSize_F5
        }
    }

    Item {
        id: buttonControlContainer
        objectName: "buttonControlContainer"
        width: QmlStyling.contentSubLeftWidth
        height: 64
        anchors {
            left: parent.left
            top: durationContainer.bottom
            topMargin: 12
        }

        Loader {
            id: playListAndDiskChange
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 5
            }
            MouseArea {
                anchors.centerIn: parent
                width: isPlayScreen ? 100 : 200
                height: 64
                onClicked: root.switchBetweenPlayingScreenAndMediaListAction()
            }
            sourceComponent: isPlayScreen ? playListButton : diskMusicInControl
        }

        Component {
            id: playListButton
            Image {
                width: QmlStyling.sIconWidth
                height: QmlStyling.sIconHeight
                source: "qrc:/images/ICN_SICON_PLAYLISTMEDIA.png"
                anchors {
                    left: parent.left
                    leftMargin: 10
                }
            }
        }
        Component {
            id: diskMusicInControl
            Row {
                height: 100
                width: diskMusic.width + songNameAndArtist.width
                spacing: 5

                Image {
                    readonly property int localMediaState: mediaState
                    id: diskMusic
                    width: QmlStyling.xsIconWidth
                    height: QmlStyling.xsIconHeight
                    anchors.verticalCenter: parent.verticalCenter
                    source: isMusicMode ? "qrc:/images/ICN_XLICON_MEDIADISK.png" : "qrc:/images/ICN_XLICON_BVIDEOICON.png"
                    onSourceChanged: {
                        // Avoid image stop at old rotation position when change between music and video icons
                        imgRotation.complete()
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

                Column {
                    id: songNameAndArtist
                    objectName: "songNameAndArtist"
                    width: 170
                    anchors.verticalCenter: parent.verticalCenter

                    TWText {
                        width: songNameAndArtist.width
                        text: currentMediaPlaying.mediaTitle ? currentMediaPlaying.mediaTitle : currentMediaPlaying.mediaFileName ? currentMediaPlaying.mediaFileName : "Unknown"
                        color: QmlStyling.color_C01
                        elide: Text.ElideRight
                        font {
                            pixelSize: QmlStyling.fontPixelSize_F3
                            bold: true
                        }
                    }
                    TWText {
                        width: songNameAndArtist.width
                        text: {
                            let result = ""
                            if (isMusicMode) {
                                result = currentMediaPlaying.mediaSinger ? currentMediaPlaying.mediaSinger : "Unknown"
                            } else {
                                result = totalDuration.text
                            }
                            return result
                        }
                        color: QmlStyling.color_C01
                        elide: Text.ElideRight
                        font {
                            pixelSize: QmlStyling.fontPixelSize_F4_5
                            bold: true
                        }
                    }
                }
            }
        }

        Image {
            id: playAndPauseButton
            width: 70
            height: width
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: isPlayScreen ? 0 : 55 // Minimize control icons
            }

            source: mediaState === SharedConstants.mediaPlayingState ? "qrc:/images/ICN_SICON_PAUSEMEDIA.png" : "qrc:/images/ICN_LICON_PLAYMEDIA.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (mediaState === SharedConstants.mediaPlayingState) {
                        mediaPlaylistModel.pausePlaying()
                    } else {
                        mediaPlaylistModel.startPlaying()
                    }
                }
            }
        }
        Image {
            id: preButton
            width: QmlStyling.sIconWidth
            height: width
            anchors {
                verticalCenter: playAndPauseButton.verticalCenter
                right: playAndPauseButton.left
                rightMargin: isPlayScreen ? 45 : 25 // Minimize control icons
            }
            source: "qrc:/images/ICN_SICON_PREMEDIA.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mediaPlaylistModel.playPrevious()
                }
            }
        }
        Image {
            id: nextButton
            width: QmlStyling.sIconWidth
            height: width
            anchors {
                verticalCenter: playAndPauseButton.verticalCenter
                left: playAndPauseButton.right
                leftMargin: isPlayScreen ? 45 : 25 // Minimize control icons
            }
            source: "qrc:/images/ICN_SICON_NEXTMEDIA.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mediaPlaylistModel.playNext()
                }
            }
        }
        Image {
            id: playBackButton
            width: 35
            height: width
            anchors {
                verticalCenter: playAndPauseButton.verticalCenter
                left: nextButton.right
                leftMargin: isPlayScreen ? 40 : 25 // Minimize control icons
            }
            source: {
                var result = "qrc:/images/ICN_SICON_REPEATMEDIAONE.png"

                // It should be display icon of NEXT mode, not current one
                switch (mediaPlaylistModel.playBackMode) {
                case SharedConstants.mediaPlayBackLoop:
                    result = "qrc:/images/ICN_SICON_REPEATMEDIAONE.png"
                    break
                case SharedConstants.mediaPlayBackCurrentItemInLoop:
                    result = "qrc:/images/ICN_SICON_RANDOM.png"
                    break
                case SharedConstants.mediaPlayBackRandom:
                    result = "qrc:/images/ICN_SICON_NOREPEATMEDIA.png"
                    break
                default:
                    result = "qrc:/images/ICN_SICON_REPEATMEDIAONE.png"
                }

                return result
            }

            MouseArea {
                anchors.fill: parent
                onClicked: mediaPlaylistModel.playBackMode++
            }
        }
        Image {
            id: volumeButton
            width: 35
            height: width
            source: mediaPlaylistModel.volume <= 2 ? "qrc:/images/ICN_SICON_MUTEVOLUMEMEDIA.png" : "qrc:/images/ICN_SICON_VOLUMEMEDIA.png"
            anchors {
                verticalCenter: playAndPauseButton.verticalCenter
                left: playBackButton.right
                leftMargin: isPlayScreen ? 40 : 25 // Minimize control icons
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    volumeControl.visible = !volumeControl.visible
                }
            }
        }
        Slider {
            id: volumeControl
            width: 100
            height: 5
            visible: false
            anchors {
                right: parent.right
                rightMargin: isPlayScreen ? -20 : -25 // Minimize control icons
                bottom: volumeButton.top
                bottomMargin: 55
            }
            rotation: 270
            from: 1
            value: mediaPlaylistModel.volume
            to: 100
            stepSize: 1
            background: null
            handle: null
            onValueChanged: {
                mediaPlaylistModel.volume = value
            }
            Rectangle {
                id: behindPortionVolume
                objectName: "behindPortionVolume"
                anchors.left: parent.left
                width: parent.width
                height: parent.height
                color: QmlStyling.color_C08
            }
            Rectangle {
                id: frontPortionVolume
                objectName: "frontPortionVolume"
                anchors.left: parent.left
                width: volumeControl.value
                height: parent.height
                color: QmlStyling.color_C01
            }
            Rectangle {
                id: dotHandleVolume
                x: {
                    // -2 is ratio help slider beautiful
                    var widthWithoutDot = parent.width - width
                    var result = 0
                    if ((volumeControl.value - 2) > widthWithoutDot) {
                        result = widthWithoutDot
                    } else {
                        result = (volumeControl.value - 2)
                    }
                    return result
                }
                objectName: "dotHandleVolume"
                anchors {
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: -1
                }
                width: 22
                height: 22
                radius: 10
                color: parent.pressed ? QmlStyling.color_C09 : QmlStyling.color_C01
                border.color: QmlStyling.color_C04
            }
        }
    }
}
