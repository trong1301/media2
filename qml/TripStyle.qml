import QtQuick 2.2
//import QtQuick.Controls.Styles 1.4

//DashboardGaugeStyle {
//    property var settingUnit: settingHandler.unitSetting

//    tickmarkStepSize: 1
//    labelStepSize: 1
//    needle: null
//    foreground: null
//    tickmarkLabel: null
//    minorTickmark: null
//    tickmark: null

//    function degreesToRadians(degrees) {
//        return degrees * (Math.PI / 180)
//    }
//    background: Canvas {
//        id: canvas
//        onPaint: {
//            var ctx = getContext("2d")
//            ctx.reset()

//            ctx.beginPath()
//            ctx.strokeStyle = "#3fff06"
//            ctx.lineWidth = outerRadius * 0.02

//            ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
//                    degreesToRadians(valueToAngle(0) - 360),
//                    degreesToRadians(valueToAngle(100)))
//            ctx.stroke()
//        }
//        TWText {
//            text: "TRIP"
//            state: "StaticColor"
//            font.pixelSize: toPixels(0.3)
//            anchors {
//                bottom: tripText.top
//                horizontalCenter: parent.horizontalCenter
//            }
//        }
//        TWText {
//            id: tripText
//            font.pixelSize: toPixels(0.4)
//            text: parseInt(control.value)
//            state: "StaticColor"
//            anchors {
//                verticalCenter: parent.verticalCenter
//                horizontalCenter: parent.horizontalCenter
//            }
//        }
//        TWText {
//            text: settingUnit ? "Miles" : "Km"
//            state: "StaticColor"
//            font.pixelSize: toPixels(0.3)
//            anchors {
//                top: tripText.bottom
//                horizontalCenter: parent.horizontalCenter
//            }
//        }
//    }
//}

Item{}
