import QtQuick 2.2

Item{}
//import QtQuick.Controls.Styles 1.4

//CircularGaugeStyle {
//    property var settingUnit: settingHandler.unitSetting
//    readonly property int highSpeedRange: speedometer.maximumValue * 0.6 // 2/3 speed
//    readonly property int midSpeedRange: speedometer.maximumValue * 0.3 //  1/3 speed

//    maximumValueAngle: 120
//    minimumValueAngle: -120
//    tickmarkInset: toPixels(0.04)
//    minorTickmarkInset: tickmarkInset
//    labelStepSize: 20
//    labelInset: toPixels(0.23)

//    function toPixels(percentage) {
//        return percentage * outerRadius
//    }

//    function degToRad(degrees) {
//        return degrees * (Math.PI / 180)
//    }

//    function radToDeg(radians) {
//        return radians * (180 / Math.PI)
//    }

//    background: Canvas {
//        id: canvas
//        onPaint: {
//            var ctx = getContext("2d")
//            ctx.reset()

//            ctx.beginPath()
//            ctx.strokeStyle = "#b1b711"
//            ctx.lineWidth = outerRadius * 0.02

//            ctx.arc(outerRadius, outerRadius,
//                    outerRadius - ctx.lineWidth / 2, degToRad(
//                        valueToAngle(0) - 360), degToRad(
//                        valueToAngle(100) - 90))
//            ctx.stroke()
//        }

//        TWText {
//            id: speedText
//            font.pixelSize: toPixels(0.45)
//            text: Math.ceil(speedometerModel.speed)
//            state: "StaticColor"
//            anchors {
//                verticalCenter: parent.verticalCenter
//                verticalCenterOffset: -10
//                horizontalCenter: parent.horizontalCenter
//            }
//        }

//        TWText {
//            text: settingUnit ? qsTr("mph") : qsTr("km/h")
//            state: "StaticColor"
//            font.pixelSize: toPixels(0.15)
//            anchors {
//                top: speedText.bottom
//                horizontalCenter: parent.horizontalCenter
//            }
//        }
//        TWText {
//            text: speedometerModel.speedStatus
//            state: "StaticColor"
//            font.pixelSize: toPixels(0.17)
//            anchors {
//                bottom: parent.bottom
//                bottomMargin: 44
//                horizontalCenter: parent.horizontalCenter
//            }
//        }
//    }
//    needle: null
//    foreground: null
//    tickmarkLabel: null
//    tickmark: Rectangle {
//        id: speedColor
//        implicitWidth: 13
//        antialiasing: true
//        smooth: true
//        implicitHeight: outerRadius * 0.4
//        color: {
//            var result = "#083221"
//            if (styleData.value <= speedometer.value
//                    && speedometer.value !== 0) {
//                if (speedometer.value >= highSpeedRange) {
//                    result = "#C9050B"
//                } else if (speedometer.value >= midSpeedRange) {
//                    result = "#F67600"
//                } else {
//                    result = "#6EB325"
//                }
//            }
//            return result
//        }
//    }

//    minorTickmark: Rectangle {
//        implicitWidth: 13
//        implicitHeight: outerRadius * 0.4
//        antialiasing: true
//        smooth: true
//        color: {
//            var result = "#083221"
//            if (styleData.value <= speedometer.value
//                    && speedometer.value !== 0) {
//                if (speedometer.value >= highSpeedRange) {
//                    result = "#C9050B"
//                } else if (speedometer.value >= midSpeedRange) {
//                    result = "#F67600"
//                } else {
//                    result = "#6EB325"
//                }
//            }
//            return result
//        }
//    }
//}
