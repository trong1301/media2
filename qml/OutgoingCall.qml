import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    id: outgoingCallId
    objectName: "OutgoingCall"
    width: QmlStyling.contentSubLeftWidth
    height: QmlStyling.contentHeight

    TWText {
        id: contactNameId
        state: "DynamicColor"
        text: phoneControllerModel.nameUserCalling
        height: 80
        width: QmlStyling.contentSubLeftWidth - 20
        font.pixelSize: QmlStyling.fontPixelSize_F0
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        elide: Text.ElideRight
        maximumLineCount: 2
        anchors {
            top: parent.top
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: avtatarId
        width: contactNameId.width
        height: 190
        anchors {
            top: contactNameId.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        Image {
            id: avatarImgId
            width: 150
            height: 150
            source: "qrc:/images/cal_person.png"
            anchors.centerIn: parent
        }

        Image {
            id: avatarBgId
            width: 190
            height: 190
            source: "qrc:/images/cal_Background_linearx3.png"
            anchors.centerIn: parent
        }
    }

    Item {
        id: rejectBtId
        width: contactNameId.width
        height: 100
        anchors {
            top: avtatarId.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        Image {
            id: rejectIcon
            width: 100
            height: 100
            anchors.centerIn: parent
            source: "qrc:/images/cal_hang.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (viewManager.isNativeBuild()) {
                        // For native, keep for reference
                        viewManager.requestChangeViewState(
                                    SharedConstants.viewTopIncomingCall,
                                    SharedConstants.viewAnyWhere)
                    //media add
                    } else {
                        phoneControllerModel.denyCall()
                    }
                }
            }
        }
    }
}
