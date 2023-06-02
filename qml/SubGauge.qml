import QtQuick 2.2
import QtQuick.Controls 2.12
import Qt5Compat.GraphicalEffects

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: rootSubGauge
    property var viewScreen: viewManager.viewState

    onViewScreenChanged: {
        if (viewManager.viewState === SharedConstants.viewSubGauge) {
            appListLoader.source = "AppListContainer.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugeSettings) {
            appListLoader.source = "AppSettingScreen.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneApplications) {
            appListLoader.source = "PhoneApplications.qml"
        } else if (viewManager.viewState === SharedConstants.viewTopIncomingCall) {
            appListLoader.source = "IncomingCall.qml"
        } else if (viewManager.viewState === SharedConstants.viewTopOutgoingCall) {
            appListLoader.source = "OutgoingCall.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneCallLogList) {
            appListLoader.source = "CallLogListScreen.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneContactList) {
            appListLoader.source = "ContactList.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneSMSList) {
            appListLoader.source = "SmsListScreen.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneSMSItem) {
            appListLoader.source = "SmsContentScreen.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugePhoneMapNavigation) {
            appListLoader.source = "MapNavigation.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugeMedia) {
            appListLoader.source = "MediaPlayerHalfScreen.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugeLoadingScreen) {
            appListLoader.source = "LoadingScreen.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugeVideo) {
            appListLoader.source = "Video.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugeCamera) {
            quickGaugeContainer.visible = true
            appListLoader.source = "Camera.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugeGallery) {
            appListLoader.source = "Gallery.qml"
        } else if (viewManager.viewState === SharedConstants.viewSubGaugeVideomini) {
            appListLoader.source = "Video_mini.qml"
        }
    }

    Rectangle {
        id: appListContainer
        width: QmlStyling.contentSubLeftWidth
        height: QmlStyling.contentHeight
        anchors {
            top: parent.top
            left: parent.left
        }

        Rectangle {
            id: blurMask
            width: QmlStyling.displayWidth
            height: QmlStyling.displayHeight
            clip: true

            BackGround {
                id: scaleBGImage
                anchors.fill: parent
                smooth: true
                visible: true
                anchors {
                    top: parent.top
                    topMargin: -60 // find fit background position
                    left: parent.left
                }
            }
        }
        Loader {
            id: appListLoader
            anchors.fill: parent
            source: "AppListContainer.qml"
        }
    }

    Item {
        id: quickGaugeContainer
        width: QmlStyling.contentSubRightWidth
        height: QmlStyling.contentHeight
        visible: true
        anchors {
            top: parent.top
            right: parent.right
        }
        SubGaugeQuickContainer {
            width: QmlStyling.contentSubRightWidth
            height: QmlStyling.contentHeight
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
