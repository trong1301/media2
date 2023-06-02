
import QtQuick 2.2
import QtQuick.Window 2.1

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Window {
    id: root
    width: QmlStyling.displayWidth
    height: QmlStyling.displayHeight
    visible: true
//    visibility: "FullScreen"
    flags: viewManager.isNativeBuild(
               ) ? Qt.Widget : Qt.FramelessWindowHint // Hidden window top bar control


    Item {
        id: rotateWrapper
        anchors.fill: parent
        //rotation: 90


        BackGround {
            id: bgId
        }

        Header {
            id: header
            anchors.top: parent.top
            width: parent.width
            height: QmlStyling.headerHeight
            menuSource: viewManagerLoader.sourceComponent
                        === mainGauge ? "qrc:/images/ICN_MICON_MENU" : "qrc:/images/ICN_LICON_BACKARROW"
        }

        Component {
            id: mainGauge
            MainGauge {}
        }

        Component {
            id: subGauge
            SubGauge {}
        }

        Loader {
            id: viewManagerLoader
            width: QmlStyling.displayWidth
            height: QmlStyling.contentHeight
            anchors.top: header.bottom
            sourceComponent: {
                var result = mainGauge
                if (viewManager.viewState !== SharedConstants.viewMainGauge) {
                    // TODO: Dummy to show/hide icons when access main/subgauge atm.
                    indicatorListModel.changeVisibility(
                                SharedConstants.viewSubGauge)
                    result = subGauge
                } else {
                    // TODO: Dummy to show/hide icons when access main/subgauge atm.
                    indicatorListModel.changeVisibility(
                                SharedConstants.viewMainGauge)
                }
                return result
            }
        }
    }
}
