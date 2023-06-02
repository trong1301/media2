import QtQuick 2.10
import QtQuick.Controls 2.12

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    readonly property int appIcon: settingHandler.themeModel.appIconTheme
    function requestShowAppData(app) {
        var result = ""
        switch (app) {
        case SharedConstants.appApplication:
            viewManager.requestChangeViewState(
                        SharedConstants.viewSubGauge,
                        SharedConstants.viewSubGaugePhoneApplications)
            break
//Media
        case SharedConstants.appMedia:
            if (mediaPlaylistModel.isMediaLoading) {
                viewManager.requestChangeViewState(
                            SharedConstants.viewSubGauge,
                            SharedConstants.viewSubGaugeLoadingScreen)
            } else {
                viewManager.requestChangeViewState(
                            SharedConstants.viewSubGauge,
                            SharedConstants.viewSubGaugeMedia)
            }
            break
        case SharedConstants.appSettings:
            viewManager.requestChangeViewState(
                        SharedConstants.viewSubGauge,
                        SharedConstants.viewSubGaugeSettings)
            break
        case SharedConstants.appVideo:
            break
        case SharedConstants.appMusic:
            break
        case SharedConstants.appCamera:
            viewManager.requestChangeViewState(
                        SharedConstants.viewSubGauge,
                        SharedConstants.viewSubGaugeCamera)
            break
        case SharedConstants.appMap:
            break
        case SharedConstants.appDemo3:
            break
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
                                "appname": SharedConstants.appApplication,
                                "appcolor": "blue",
                                "source": "qrc:/images/Icon-Application_" + (appIcon + 1)
                            })

            appModel.append({
                                "appname": SharedConstants.appSettings,
                                "appcolor": "red",
                                "source": "qrc:/images/Icon-Setting_" + (appIcon + 1)
                            })

            appModel.append({
                                "appname": SharedConstants.appMedia,
                                "appcolor": "purple",
                                "source": "qrc:/images/Icon-Music_" + (appIcon + 1)
                            })

            appModel.append({
                                "appname": SharedConstants.appVideo,
                                "appcolor": "light blue",
                                "source": "qrc:/images/Icon-Video_" + (appIcon + 1)
                            })

            appModel.append({
                                "appname": SharedConstants.appMusic,
                                "appcolor": "purple",
                                "source": "qrc:/images/Icon-Music_" + (appIcon + 1)
                            })

            appModel.append({
                                "appname": SharedConstants.appCamera,
                                "appcolor": "lightgreen",
                                "source": "qrc:/images/Icon-Camera_" + (appIcon + 1)
                            })

            appModel.append({
                                "appname": SharedConstants.appMap,
                                "appcolor": "magenta",
                                "source": "qrc:/images/Icon-Map_" + (appIcon + 1)
                            })

            appModel.append({
                                "appname": SharedConstants.appDemo3,
                                "appcolor": "orange",
                                "source": "qrc:/images/Icon-Video_" + (appIcon + 1)
                            })
        }
    }

    Component {
        id: comDelegate
        Item {
            property real opacityApp: phoneControllerModel.isAppActivated ? 1 : 0.3
            id: delegateElementsContainer
            objectName: "gridviewDelegateContainer"
            width: gridView.cellWidth
            height: gridView.cellHeight
            opacity: (model.appname === SharedConstants.appApplication) ? opacityApp : 1

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
                enabled: true
                onClicked: {
                    requestShowAppData(appModel.get(index).appname)
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
        id: gridContainer
        anchors.left: parent.left
        width: QmlStyling.contentSubLeftWidth
        height: QmlStyling.contentHeight
        readonly property int roundUpNumberOfGridView: (gridView.count % 3 === 0) ? gridView.count : (gridView.count % 2 === 0) ? gridView.count + 1 : gridView.count + 2

        GridView {
            id: gridView
            model: appModel
            delegate: comDelegate
            anchors.centerIn: parent
            height: QmlStyling.contentHeight
            width: cellWidth * 3
            cellHeight: QmlStyling.contentHeight / 2
            cellWidth: 170
            clip: true
            interactive: gridView.count > 6 // If only has 6 items, disable scroll interaction
            boundsBehavior: Flickable.StopAtBounds
        }

        Rectangle {
            id: scrollbar
            radius: 20
            anchors.left: gridView.right
            visible: gridView.count > 6 // If only has 6 items, no need to show the scroll bar


            /*
                TODO: Accept binding loop until find better solution
                Math.max(x,Math.min(y,z))
                x: When scroll to top, always margin top x pixels
                y: The dynamic pixel of the top of scroll bar
                z: When scroll to bottom, always margin bottom z pixels, minus 15 due to plus 15 at x
            */
            y: Math.max(15, Math.min(
                            gridView.visibleArea.yPosition * gridView.height,
                            gridContainer.height - scrollbar.height - 15))
            width: 10
            height: (gridContainer.height / (gridContainer.roundUpNumberOfGridView / 6))
            color: QmlStyling.color_C08
        }
    }
}
