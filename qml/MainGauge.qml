import QtQuick 2.2

import TwoWheels.QmlStylingSingleton 1.0

Item {
    id: rootMainGauge

    IndicatorBar {
        id: indicatorBar
        anchors {
            top: parent.top
            topMargin: 30
        }
        width: parent.width
        height: 50
    }

    MainGaugeCluster {
        id: mainGaugeCluster
        anchors {
            top: indicatorBar.bottom
            topMargin: 20
        }
        width: parent.width
        height: QmlStyling.contentHeight - indicatorBar.height
    }
}
