import QtQuick 2.2

import TwoWheels.QmlStylingSingleton 1.0

Item {
    id: root
    property int iconSpacing: 15

    Row {
        id: rowIndicators
        anchors.centerIn: parent
        spacing: iconSpacing
        Repeater {
            model: indicatorListModel
            IndicatorIcons {
                listModel: model
                height: QmlStyling.xsIconHeight
                width: QmlStyling.xsIconWidth
            }
        }
    }
}
