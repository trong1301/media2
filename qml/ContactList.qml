import QtQuick 2.12
import QtQuick.Layouts 1.10
import QtQuick.Controls 2.0

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: root
    objectName: "contactListContainer"
    property bool isExitedMouseAreaPress: false // To prevent onReleased invoked after onExited

    Component {
        id: contactDelegate
        Rectangle {
            id: containerID
            width: contactListview.width - 15
            height: 105
            color: QmlStyling.color_transparent
            Row {
                id: rowID
                spacing: 10
                width: containerID.width - 20
                height: containerID.height - 5
                anchors {
                    verticalCenter: parent.verticalCenter
                }
                Image {
                    id: avatarID
                    width: 70
                    height: 70
                    source: "qrc:/images/user"
                    fillMode: Image.PreserveAspectFit
                    mipmap: true
                    anchors.verticalCenter: parent.verticalCenter
                }
                Column {
                    anchors.top: avatarID.top
                    spacing: 7
                    TWText {
                        id: contactNameID
                        width: 360
                        text: contactName
                        color: QmlStyling.color_C01
                        elide: Text.ElideRight
                        font.pixelSize: QmlStyling.fontPixelSize_F2
                        font.bold: true
                        horizontalAlignment: Text.AlignLeft
                        state: "DynamicColor"
                    }
                    TWText {
                        id: contactNumberID
                        width: contactNameID.width
                        text: contactNumber
                        color: QmlStyling.color_C01
                        font.pixelSize: QmlStyling.fontPixelSize_F2
                        horizontalAlignment: Text.AlignLeft
                        wrapMode: Text.Wrap
                        state: "DynamicColor"
                    }
                }
                Image {
                    id: callButtonID
                    width: 75
                    height: 75
                    source: "qrc:/images/ICN_LICON_CALL5"
                    fillMode: Image.PreserveAspectFit
                    mipmap: true
                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            root.isExitedMouseAreaPress = false
                            animExpand.start()
                        }
                        onReleased: {
                            animNormal.start()
                            if (!root.isExitedMouseAreaPress) {
                                if (viewManager.isNativeBuild()) {
                                    // For native, keep for reference
                                    phoneControllerModel.nameUserCalling = contactName
                                    viewManager.lastViewState = viewManager.viewState
                                    viewManager.requestChangeViewState(
                                                SharedConstants.viewAnyWhere,
                                                SharedConstants.viewTopOutgoingCall)
                                } else {
                                    phoneControllerModel.makeAPhoneCall(
                                                contactNumber)
                                }
                                // To jump back to previous position
                                phoneControllerModel.currentIndexList = index
                            }
                        }
                        onCanceled: {
                            animNormal.start()
                        }
                        onExited: {
                            root.isExitedMouseAreaPress = true
                            animNormal.start()
                        }
                    }
                }

                // Expand the button
                PropertyAnimation {
                    id: animExpand
                    target: callButtonID
                    property: "scale"
                    to: 1.3
                    duration: 100
                    easing.type: Easing.InOutQuad
                }

                // Shrink back to normal
                PropertyAnimation {
                    id: animNormal
                    target: callButtonID
                    property: "scale"
                    to: 1.0
                    duration: 100
                    easing.type: Easing.InOutQuad
                }
            }
            Rectangle {
                id: separatorID
                width: containerID.width
                height: 2
                color: QmlStyling.color_C08
                anchors {
                    right: parent.right
                    bottom: containerID.bottom
                }
            }
        }
    }

    ListView {
        id: contactListview
        delegate: contactDelegate
        model: contactModel
        width: 550
        height: QmlStyling.contentHeight
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: 5
        }

        ScrollBar.vertical: ScrollBar {
            objectName: "scrollBar"
            width: 14
            policy: ScrollBar.AlwaysOn
            parent: contactListview
            interactive: false
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            contentItem: Rectangle {
                radius: 20
                color: QmlStyling.color_C08
            }
            visible: contactListview.contentHeight > contactListview.height
        }
    }
    Component.onCompleted: {
        // Jump to the position of list
        contactListview.positionViewAtIndex(
                    phoneControllerModel.currentIndexList, ListView.Center)
    }
}
