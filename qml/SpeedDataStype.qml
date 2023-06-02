

/**
 * @addtogroup <MainGauge.qml>
 * @{
 * @file        TripStyle.qml
 * @brief       Design for TripGauge.
 * @author      guo2hc
 * @}
 */
import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

DashboardGaugeStyle {
    id: tachometerStyle
    tickmarkStepSize: 1
    labelStepSize: 1
    needleLength: toPixels(0.85)
    needleBaseWidth: toPixels(0.08)
    needleTipWidth: toPixels(0.03)
    needle: null
    foreground: null
    tickmarkLabel: null
    minorTickmark: null
    tickmark: null

    function degreesToRadians(degrees) {
        return degrees * (Math.PI / 180)
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
                    outerRadius - ctx.lineWidth / 2, degreesToRadians(
                        valueToAngle(0) - 360), degreesToRadians(
                        valueToAngle(100) - 90))
            ctx.stroke()
        }
        TWText {
            text: "Km/H"
            color: "white"
            font.pixelSize: toPixels(0.3)
            anchors.bottom: trip.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TWText {
            id: trip
            font.pixelSize: toPixels(0.5)
            text: speedometerModel.speed
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
