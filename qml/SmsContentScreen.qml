import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

import "../js/moment.js" as Moment
import "../js/moment-timezone-with-data.js" as MomentTimezone

Item {
    id: root
    objectName: "SMSContentContainer"
    property var smsColorModel: settingHandler.themeModel.smsColorModel

    function isLeapYear(year) {
        return ((year % 4 === 0) && (year % 100 !== 0))
                || (year % 400 === 0) // false = 28, true = 29 days
    }

    function getDayCalib(day) {
        var result = 0

        // 28days: ratio = -2
        // 29days: ratio = -1
        // 30days: ratio = 0
        // 31days: ratio = 1
        switch (day) {
        case 1:
            result = 1
            break
        case 2:
            if (isLeapYear(2000))
                result = -1
            else
                result = -2
            break
        case 3:
            result = 1
            break
        case 4:
            result = 0
            break
        case 5:
            result = 1
            break
        case 6:
            result = 0
            break
        case 7:
            result = 1
            break
        case 8:
            result = 1
            break
        case 9:
            result = 0
            break
        case 10:
            result = 1
            break
        case 11:
            result = 0
            break
        case 12:
            result = 1
            break
        default:
            break
        }
        return result
    }

    function getDateWithTimeZone(timeZone) {
        var momentDate = moment(new Date())
        var momentDateTz = momentDate.tz(timeZone)

        return momentDateTz.format('l')
    }
    ListView {
        id: list
        spacing: 20
        model: smsContentModel
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
            parent: list
            interactive: false
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            contentItem: Rectangle {
                radius: 20
                color: QmlStyling.color_C08
            }
            visible: list.contentHeight > list.height
        }

        delegate: Column {
            id: col
            width: list.width
            height: messageBox.height + dateId.contentHeight
            Rectangle {
                id: messageBox
                radius: 10
                width: message_body.implicitWidth > 400 ? 400 : message_body.implicitWidth + 20
                height: message_body.contentHeight + 8

                TWText {
                    id: message_body
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }
                    width: parent.width - 20
                    text: body
                    wrapMode: Text.Wrap
                    font.pixelSize: QmlStyling.fontPixelSize_F2
                }

                states: [
                    State {
                        name: "leftReceiveSMS"
                        when: model.type === 1
                        PropertyChanges {
                            target: messageBox
                            color: smsColorModel[SharedConstants.sms_content_leftBox]
                            anchors {
                                left: col.left
                                leftMargin: 5
                            }
                        }
                        PropertyChanges {
                            target: message_body
                            color: smsColorModel[SharedConstants.sms_content_leftText]
                        }
                    },
                    State {
                        name: "rightSendSMS"
                        when: model.type === 2
                        PropertyChanges {
                            target: messageBox
                            color: smsColorModel[SharedConstants.sms_content_rightBox]
                            anchors {
                                right: col.right
                                rightMargin: 20
                            }
                        }
                        PropertyChanges {
                            target: message_body
                            color: smsColorModel[SharedConstants.sms_content_rightText]
                        }
                    }
                ]
            }
            TWText {
                id: dateId
                font.pixelSize: QmlStyling.fontPixelSize_F2
                property string smsDate: date
                // smsDateArr [DOW, Day, Month, Year, HH:mm]
                property var smsDateArr: smsDate.split('-')

                // currentDateArr [Month Day Year]
                property var currentDateArr: getDateWithTimeZone(
                                                 "Asia/Bangkok").toString(
                                                 ).split('/')
                color: smsColorModel[SharedConstants.sms_content_date]

                text: {
                    var result = ""
                    var dayCalibFromMonth = 0
                    // year
                    if (parseInt(smsDateArr[3]) < parseInt(currentDateArr[2])) {

                        // If sms year and current year are next to eachother
                        if (parseInt(smsDateArr[2]) === 12 && parseInt(
                                    currentDateArr[0]) === 1) {

                            // We have 4 types of months: 28days, 29days, 30days, 31days -> Get appropriate ratio
                            // But with this special case, the last month is 12 and current month is 1

                            // To check in a week or not
                            var calculateInAWeek1 = Math.abs(
                                        parseInt(smsDateArr[1]) - parseInt(
                                            currentDateArr[1]))

                            // If in a week
                            if (calculateInAWeek1 >= 24) {
                                if (calculateInAWeek1 === 30) {
                                    // Yesterday
                                    result = "Yesterday " + smsDateArr[4]
                                } else {
                                    // DOW
                                    result = smsDateArr[0] + " " + smsDateArr[4]
                                }
                            } else {
                                // Not in a week -> Display date
                                result = smsDateArr[1] + "/" + smsDateArr[2] + "/"
                                        + smsDateArr[3] + " " + smsDateArr[4]
                            }
                        } else {
                            // Not next to eachother -> Display date
                            result = smsDateArr[1] + "/" + smsDateArr[2] + "/"
                                    + smsDateArr[3] + " " + smsDateArr[4]
                        }
                    } else {
                        // month
                        if (parseInt(smsDateArr[2]) < parseInt(
                                    currentDateArr[0])) {

                            // If sms month and current month are next to eachother
                            if ((parseInt(currentDateArr[0]) - parseInt(
                                     smsDateArr[2])) === 1) {

                                // We have 4 types of months: 28days, 29days, 30days, 31days -> Get appropriate ratio
                                dayCalibFromMonth = getDayCalib(
                                            parseInt(smsDateArr[2]))

                                // To check in a week or not
                                let calculateInAWeek2 = Math.abs(
                                        parseInt(smsDateArr[1]) - parseInt(
                                            currentDateArr[1]))

                                // If in a week
                                if (calculateInAWeek2 >= (23 + dayCalibFromMonth)) {
                                    // Check yesterday
                                    if (calculateInAWeek2 === (29 + dayCalibFromMonth)) {
                                        result = "Yesterday " + smsDateArr[4]
                                    } else {
                                        // DOW
                                        result = smsDateArr[0] + " " + smsDateArr[4]
                                    }
                                } else {
                                    // Not in a week - > Display date
                                    result = smsDateArr[1] + "/" + smsDateArr[2]
                                            + "/" + smsDateArr[3] + " " + smsDateArr[4]
                                }
                            } else {
                                // Not next to eachother -> Display date
                                result = smsDateArr[1] + "/" + smsDateArr[2] + "/"
                                        + smsDateArr[3] + " " + smsDateArr[4]
                            }
                        } else {
                            //day
                            if (parseInt(smsDateArr[1]) <= parseInt(
                                        currentDateArr[1])) {

                                // To check in a week or not
                                let calculateInAWeek3 = parseInt(
                                        currentDateArr[1]) - parseInt(
                                        smsDateArr[1])

                                // In a week
                                if (calculateInAWeek3 <= 7) {
                                    if (calculateInAWeek3 === 0) {
                                        // Today + Display time
                                        result = "Today " + smsDateArr[4]
                                    } else if (calculateInAWeek3 === 1) {
                                        // Yesterday
                                        result = "Yesterday " + smsDateArr[4]
                                    } else {
                                        // DOW
                                        result = smsDateArr[0] + " " + smsDateArr[4]
                                    }
                                } else {
                                    // Not in a week -> Dislay date
                                    result = smsDateArr[1] + "/" + smsDateArr[2]
                                            + "/" + smsDateArr[3] + " " + smsDateArr[4]
                                }
                            }
                        }
                    }
                    return result
                }

                anchors {
                    left: type == 1 ? messageBox.left : undefined
                    right: type == 2 ? messageBox.right : undefined
                }
            }
        }
        Component.onCompleted: {
            // Jump to the bottom of sms (newest)
            list.positionViewAtEnd()
        }
    }
}
