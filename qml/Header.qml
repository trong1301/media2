import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: rootHeader
    property var currentSystemTime: systemClock !== null ? systemClock.time : null
    property string menuSource
    property int signal: 0

    function speed_toggle_func() {
        if(signal === 0) {
            speedometerModel.speed = 0
            signal = 1
        }
        else {
            speedometerModel.speed = 1
            signal = 0
        }
    }

    Button {
        id: speed_toggle
        x: 350
        y: 15
        text: "Speed toggle"
        onClicked: {
            speed_toggle_func()
        }
    }

    Item {
        id: leftHeader
        width: QmlStyling.contentSubLeftWidth
        height: parent.height
        anchors.left: parent.left

        TWText {
            property string currentViewState: viewManager.viewState
            id: viewNameID
            text: {
                var result = ""
                switch (currentViewState) {
                case SharedConstants.viewSubGauge:
                    result = SharedConstants.subGaugeTitle
                    break
                case SharedConstants.viewSubGaugeSettings:
                    result = SharedConstants.settingTitle
                    break
                case SharedConstants.viewSubGaugePhoneApplications:
                    result = SharedConstants.phoneApplicationTitle
                    break
                case SharedConstants.viewSubGaugePhoneCallLogList:
                    result = SharedConstants.callLogTitle
                    break
                case SharedConstants.viewSubGaugePhoneContactList:
                    result = SharedConstants.contactTitle
                    break
                case SharedConstants.viewSubGaugePhoneSMSList:
                    result = SharedConstants.smsTitle
                    break
                case SharedConstants.viewSubGaugePhoneSMSItem:
                    result = phoneControllerModel.smsItemSelected
                    break
                case SharedConstants.viewSubGaugePhoneMapNavigation:
                    result = SharedConstants.mapTitle
                    break
                case SharedConstants.viewTopIncomingCall:
                    result = SharedConstants.incomingCallTitle
                    break
                case SharedConstants.viewTopOutgoingCall:
                    result = SharedConstants.outgoingCallTitle
                    break
                case SharedConstants.viewSubGaugeMedia:
                    result = SharedConstants.mediaTitle
                    break
                case SharedConstants.viewSubGaugeLoadingScreen:
                    result = SharedConstants.loadingTitle
                    break
                case SharedConstants.viewSubGaugeVideo:
                    result = SharedConstants.subGaugeVideoTitle
                    break
                case SharedConstants.viewSubGaugeCamera:
                    result = SharedConstants.subGaugeCameraTitle
                    break
                case SharedConstants.viewSubGaugeGallery:
                    result = SharedConstants.subGaugeGalleryTitle
                    break
                case SharedConstants.viewSubGaugeVideomini:
                    result = SharedConstants.subGaugeVideominiTitle
                    break
                }
                return result
            }
            state: "StaticColor"
            font.pixelSize: QmlStyling.fontPixelSize_F1
            font.bold: true
            width: 298
            elide: Text.ElideRight
            anchors {
                left: menuList.visible ? menuList.right : parent.left
                leftMargin: menuList.visible ? 0 : 20
                verticalCenter: menuList.visible ? menuList.verticalCenter : parent.verticalCenter
            }
        }

        Image {
            id: menuList
            width: QmlStyling.mIconWidth
            height: QmlStyling.mIconHeight
            source: menuSource
            anchors.left: parent.left
            visible: !(viewManager.viewState === SharedConstants.viewTopIncomingCall
                       || viewManager.viewState === SharedConstants.viewTopOutgoingCall)

            MouseArea {
                anchors.left: parent.left
                width: menuList.width * 2
                height: menuList.height
                onClicked: {
                    if (viewManager.viewState === SharedConstants.viewMainGauge) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewMainGauge,
                                    SharedConstants.viewSubGauge)
                    } else if (viewManager.viewState === SharedConstants.viewSubGauge) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGauge,
                                    SharedConstants.viewMainGauge)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugeSettings) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugeSettings,
                                    SharedConstants.viewSubGauge)
                    } else if (viewManager.viewState
                               === SharedConstants.viewSubGaugePhoneApplications) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugePhoneApplications,
                                    SharedConstants.viewSubGauge)
                    } else if (viewManager.viewState
                               === SharedConstants.viewSubGaugePhoneCallLogList) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugePhoneCallLogList,
                                    SharedConstants.viewSubGaugePhoneApplications)
                    } else if (viewManager.viewState
                               === SharedConstants.viewSubGaugePhoneContactList) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugePhoneContactList,
                                    SharedConstants.viewSubGaugePhoneApplications)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneSMSList) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugePhoneSMSList,
                                    SharedConstants.viewSubGaugePhoneApplications)
                    } else if (viewManager.viewState
                               === SharedConstants.viewSubGaugePhoneMapNavigation) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugePhoneMapNavigation,
                                    SharedConstants.viewSubGaugePhoneApplications)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneSMSItem) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugePhoneSMSItem,
                                    SharedConstants.viewSubGaugePhoneSMSList)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugeMedia) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugeMedia,
                                    SharedConstants.viewSubGauge)
                    } else if (viewManager.viewState
                               === SharedConstants.viewSubGaugeLoadingScreen) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugeLoadingScreen,
                                    SharedConstants.viewSubGauge)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugeVideo) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugeVideo,
                                    SharedConstants.viewSubGauge)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugeCamera) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugeCamera,
                                    SharedConstants.viewSubGauge)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugeGallery) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugeGallery,
                                    SharedConstants.viewSubGaugeCamera)
                    } else if (viewManager.viewState === SharedConstants.viewSubGaugeVideomini) {
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewSubGaugeVideomini,
                                    SharedConstants.viewSubGaugeGallery)
                    }
                }
            }
        }

        MediaTopScreenRunning {
            id: mediaTopScreenRunning
            objectName: "mediaTopScreenRunning"
            // Minus icon of devices width when visible
            width: notiRow.width
                   > 0 ? QmlStyling.contentSubLeftWidth - menuList.width - notiRow.width
                         - 20 : QmlStyling.contentSubLeftWidth - menuList.width
            height: QmlStyling.mIconHeight
            clip: true
            active: !mediaPlaylistModel.isMediaLoading
                    && mediaPlaylistModel.isMusicMode
                    && mediaPlaylistModel.mediaState === SharedConstants.mediaPlayingState
                    && viewManager.viewState === SharedConstants.viewMainGauge
            anchors {
                verticalCenter: menuList.verticalCenter
                left: menuList.right
                leftMargin: 10
            }
        }


        Row {
            id: notiRow
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            spacing: 10
            Loader {
                active: phoneControllerModel.isPhoneConnected
                        && notificationManager.isUsbIconVisible
                sourceComponent: HeaderIcon {
                    objectName: "usbIcon"
                    anchors.verticalCenter: parent.verticalCenter
                    width: QmlStyling.sIconWidth
                    height: QmlStyling.sIconHeight
                    source: "qrc:/images/usb"
                }
            }
            Loader {
                active: phoneControllerModel.isPhoneConnected
                        && notificationManager.isWifiIconVisible
                sourceComponent: HeaderIcon {
                    objectName: "wifiIcon"
                    anchors.verticalCenter: parent.verticalCenter
                    width: QmlStyling.sIconWidth
                    height: QmlStyling.sIconHeight
                    source: "qrc:/images/wifi"
                }
            }
            Loader {
                active: phoneControllerModel.isPhoneConnected
                        && notificationManager.isMessageIconVisible
                sourceComponent: HeaderIcon {
                    objectName: "messageIcon"
                    anchors.verticalCenter: parent.verticalCenter
                    width: QmlStyling.sIconWidth
                    height: QmlStyling.sIconHeight
                    source: "qrc:/images/chat"
                }
            }
            Loader {
                active: phoneControllerModel.isPhoneConnected
                        && notificationManager.isCallIconVisible
                sourceComponent: HeaderIcon {
                    objectName: "callIcon"
                    anchors.verticalCenter: parent.verticalCenter
                    width: QmlStyling.sIconWidth
                    height: QmlStyling.sIconHeight
                    source: "qrc:/images/miss_call"
                }
            }
        }
    }

    Item {
        id: containerTime
        width: QmlStyling.contentSubRightWidth
        height: parent.height
        anchors.right: parent.right
        TWText {
            id: sysClock
            text: currentSystemTime
            state: "StaticColor"
            font.pixelSize: QmlStyling.fontPixelSize_F1
            anchors.centerIn: parent
        }

        Image {
            id: bgsvWatermark
            source: "qrc:/images/ICN_LICON_BGSV"
            width: 70
            height: 70
            opacity: 0.7
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: -5
            }
        }
    }

    PopUp {
        id: popUpMessage
        objectName: "popUpMessage"
        width: QmlStyling.displayWidth
        height: parent.height
        anchors.left: parent.left
        z: 1
        opacity: 0
        visible: phoneControllerModel.isAppActivated
        states: [
            State {
                name: "showSmsPopup"
                when: phoneControllerModel.showPopUp === true
                PropertyChanges {
                    target: popUpMessage
                    opacity: 1
                }
            },
            State {
                name: "hideSmsPopup"
                when: phoneControllerModel.showPopUp === false
                PropertyChanges {
                    target: popUpMessage
                    opacity: 0
                }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }
    }
}

