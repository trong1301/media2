import QtQuick 2.10
import QtQuick.Controls 2.12

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    readonly property int appIcon: settingHandler.themeModel.appIconTheme
    function loadAppData(app) {
        var result = ""
        switch (app) {
        case SharedConstants.appCall:
            phoneControllerModel.requestCallLogData()
            viewManager.requestChangeViewState(
                        SharedConstants.viewSubGaugePhoneApplications,
                        SharedConstants.viewSubGaugePhoneCallLogList)
            break
        case SharedConstants.appContact:
            phoneControllerModel.requestContactData()
            viewManager.requestChangeViewState(
                        SharedConstants.viewSubGaugePhoneApplications,
                        SharedConstants.viewSubGaugePhoneContactList)
            break
        case SharedConstants.appSMS:
            phoneControllerModel.requestMessageData()
            viewManager.requestChangeViewState(
                        SharedConstants.viewSubGaugePhoneApplications,
                        SharedConstants.viewSubGaugePhoneSMSList)
            break
            //        case SharedConstants.appMap:
            //            viewManager.requestChangeViewState(
            //                        SharedConstants.viewSubGaugePhoneApplications,
            //                        SharedConstants.viewSubGaugePhoneMapNavigation)
            //            break
        default:
            console.log("Invalid load view")
            break
        }
        return result
    }

    ListModel {
        id: appModel
        Component.onCompleted: {
            appModel.append({
                                "appname": SharedConstants.appCall,
                                "appcolor": "green",
                                "source": "qrc:/images/Icon-CallLogs_" + (appIcon + 1)
                            })
            appModel.append({
                                "appname": SharedConstants.appContact,
                                "appcolor": "green",
                                "source": "qrc:/images/Icon-Contact_" + (appIcon + 1)
                            })
            appModel.append({
                                "appname": SharedConstants.appSMS,
                                "appcolor": "green",
                                "source": "qrc:/images/Icon-SMS_" + (appIcon + 1)
                            })
            appModel.append({
                                "appname": SharedConstants.appMap,
                                "appcolor": "green",
                                "source": "qrc:/images/Icon-Map_" + (appIcon + 1)
                            })
        }
    }

    Component {
        id: comDelegate
        Item {
            id: delegateElementsContainer
            objectName: "listViewDelegateContainer"
            width: 170
            height: QmlStyling.contentHeight / 2

            Image {
                id: appImages
                anchors {
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: -20
                    horizontalCenter: parent.horizontalCenter
                }
                source: model.source
                width: 140
                height: 140
                mipmap: true
                fillMode: Image.PreserveAspectFit
                Rectangle {
                    anchors.fill: parent
                    color: "white"
                    opacity: 0.5
                    radius: 100
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var getRequestApp = loadAppData(appModel.get(index).appname)
                    if (getRequestApp !== "") {
                        appListLoader.source = getRequestApp
                    }
                }
            }

            TWText {
                anchors {
                    top: appImages.bottom
                    topMargin: 10
                    horizontalCenter: parent.horizontalCenter
                }
                text: model.appname
                state: "DynamicColor"
                font.pixelSize: QmlStyling.fontPixelSize_F4_5
            }
        }
    }

    Item {
        id: listViewContainer
        anchors {
            left: parent.left
            leftMargin: 12
        }
        width: QmlStyling.contentSubLeftWidth
        height: QmlStyling.contentHeight

        ListView {
            id: phoneApplicationList
            model: appModel
            delegate: comDelegate
            orientation: ListView.Horizontal
            anchors.centerIn: parent
            width: 534
            height: QmlStyling.contentHeight
            clip: true
            boundsBehavior: Flickable.StopAtBounds
        }
    }
}
