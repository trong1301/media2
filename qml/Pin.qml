import QtQuick 2.2
import QtQuick.Controls.Styles 1.4

DashboardGaugeStyle {
    readonly property int highBatteryRange: batteryCapacity.maximumValue * 0.6 // 2/3 pin
    readonly property int midBatteryRange: batteryCapacity.maximumValue * 0.2 //  1/3 pin

    maximumValueAngle: 180
    minimumValueAngle: -180
    tickmarkInset: toPixels(0.04)
    minorTickmarkInset: tickmarkInset
    labelStepSize: 20
    labelInset: toPixels(0.23)

    function toPixels(percentage) {
        return percentage * outerRadius
    }

    function degToRad(degrees) {
        return degrees * (Math.PI / 180)
    }

    function radToDeg(radians) {
        return radians * (180 / Math.PI)
    }

    background: Canvas {
        id: canvas
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()

            ctx.beginPath()
            ctx.strokeStyle = "#3fff06"
            ctx.lineWidth = outerRadius * 0.02

            ctx.arc(outerRadius, outerRadius,
                    outerRadius - ctx.lineWidth / 2, degToRad(
                        valueToAngle(0) - 360), degToRad(
                        valueToAngle(100) - 90))
            ctx.stroke()
        }
        TWText {
            text: "BATTERY"
            state: "StaticColor"
            font.pixelSize: toPixels(0.25)
            anchors {
                bottom: speedText.top
                horizontalCenter: parent.horizontalCenter
            }
        }
        TWText {
            id: speedText
            font.pixelSize: toPixels(0.4)
            text: control.value
            state: "StaticColor"
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }
        TWText {
            text: "%"
            state: "StaticColor"
            font.pixelSize: toPixels(0.3)
            anchors {
                top: speedText.bottom
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
    needle: null
    foreground: null
    tickmarkLabel: null
    tickmark: Rectangle {
        visible: styleData.value < 80 || styleData.value % 10 == 0
        implicitWidth: outerRadius * 0.09
        antialiasing: true
        implicitHeight: outerRadius * 0.1
        color: {
            var result = "#083221"
            if (styleData.value <= batteryCapacity.value) {
                if (batteryCapacity.value >= highBatteryRange) {
                    result = "#6EB325"
                } else if (batteryCapacity.value >= midBatteryRange) {
                    result = "#F67600"
                } else {
                    result = "#C9050B"
                }
            }
            return result
        }
    }
    minorTickmark: Rectangle {
        implicitWidth: outerRadius * 0.09
        implicitHeight: outerRadius * 0.1
        antialiasing: true
        smooth: true
        color: {
            var result = "#083221"
            if (styleData.value <= batteryCapacity.value) {
                if (batteryCapacity.value >= highBatteryRange) {
                    result = "#6EB325"
                } else if (batteryCapacity.value >= midBatteryRange) {
                    result = "#F67600"
                } else {
                    result = "#C9050B"
                }
            }
            return result
        }
    }
}

