import QtQuick 2.2
import QtQuick.Controls 2.0
//import QtQuick.Controls.Styles 2.0
//import QtQuick.Extras 2.0
import TwoWheels.QmlStylingSingleton 1.0
//import QtQuick.Controls.Styles 1.0


//import speedometer 1.0
//import odometer 1.0
//import battery 1.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

Item {
//    id: root
//    Item {
//        id: container
//        width: root.width
//        height: 300
//        anchors {
//            top: parent.top
//            topMargin: 8
//            horizontalCenter: parent.horizontalCenter
//        }

//        Row {
//            id: gaugeRow
//            spacing: container.width * 0.05
//            anchors.centerIn: parent

////            Item {
////                id: batteryCapacity
////                width: 210
////                height: 210
////                Rectangle {
////                    radius: width * 0.5
////                    anchors.fill: parent
////                    color: "#a4a4a4"
////                    opacity: 0.8
////                }

////                TWText {
////                    id: batteryText
////                    width: 210
////                    anchors.centerIn: parent
////                    horizontalAlignment: Text.AlignHCenter
////                    verticalAlignment: Text.AlignVCenter
////                    state: "StaticColor"
////                    text: batteryViewModel.batteryLevel + "%"
////                    font.pixelSize: 60
////                    font.bold: true
////                }
////            }

////            Item {
////                id: speedometer
////                width: 210
////                height: 210
////                Rectangle {
////                    radius: width * 0.5
////                    anchors.fill: parent
////                    color: {
////                        var result = "#a4a4a4"
////                        if (speedometerModel.speed !== 0) {
////                            if (speedometerModel.speed >= 60) {
////                                result = "#C9050B"
////                            } else if (speedometerModel.speed >= 40) {
////                                result = "#F67600"
////                            } else {
////                                result = "#6EB325"
////                            }
////                        }
////                        return result
////                    }
////                    opacity: 0.8
////                }

////                TWText {
////                    id: speedText
////                    width: 210
////                    anchors.centerIn: parent
////                    horizontalAlignment: Text.AlignHCenter
////                    verticalAlignment: Text.AlignVCenter
////                    state: "StaticColor"
////                    text: speedometerModel.speed + "km/h"
////                    font.pixelSize: 60
////                    font.bold: true
////                }
////            }

////            Item {
////                id: trip
////                width: 210
////                height: 210
////                Rectangle {
////                    radius: width * 0.5
////                    anchors.fill: parent
////                    color: {
////                        var result = "#a4a4a4"
////                        if (speedometerModel.mileAge !== 0) {
////                            if (speedometerModel.mileAge >= 60) {
////                                result = "#C9050B"
////                            } else if (speedometerModel.mileAge >= 40) {
////                                result = "#F67600"
////                            } else {
////                                result = "#6EB325"
////                            }
////                        }
////                        return result
////                    }
////                    opacity: 0.8
////                }

////                TWText {
////                    id: tripText
////                    width: 210
////                    anchors.centerIn: parent
////                    horizontalAlignment: Text.AlignHCenter
////                    verticalAlignment: Text.AlignVCenter
////                    state: "StaticColor"
////                    text: speedometerModel.mileAge + "km"
////                    font.pixelSize: 60
////                    font.bold: true
////                }
////            }

//            Speedometer{
//                id: speedometer
//                y: -130
//                objectName: "speedometer"
//                anchors.horizontalCenter:  parent.horizontalCenter
//                width: speedometerSize
//                height: speedometerSize
//                startAngle: startAngle
//                alignAngle: alignAngle
//                lowestRange: lowestRange
//                highestRange: highestRange
//                speed: speedometerModel.speed
//                arcWidth: arcWidth
//                outerColor: outerColor
//                innerColor: innerColor
//                textColor: textColor
//                backgroundColor: backgroundColor
//            }

//            Battery{
//                x: -310
//                y: -100
//                objectName: "battery"
//                width: batterySize
//                height: batterySize
//                startAngle: startAngle
//                alignAngle: alignAngle
//                lowestRange: lowestRange
//                highestRange: highestRange
//                batteryLevel: batteryLevel
//                arcWidth: arcWidth
//                outerColor: outerColor
//                innerColor: innerColor
//                textColor: textColor
//                backgroundColor: backgroundColor
//            }

//            Odometer{
//                x: 140
//                y: -100
//                objectName: "odometer"
//                width: tripSize
//                height: tripSize
//                startAngle: startAngle
//                alignAngle: alignAngle
//                lowestRange: lowestRange
//                highestRange: highestRange
//                trip: trip
//                arcWidth: arcWidth
//                outerColor: outerColor
//                innerColor: innerColor
//                textColor: textColor
//                backgroundColor: backgroundColor
//            }

////            Item {
////                Timer {
////                    id: timer_d
////                    interval: 50; running: true; repeat: true
////                    onTriggered: speedometer.speed = speedometer.speed + 1
////                }
////            }
//        }
//    }
}
