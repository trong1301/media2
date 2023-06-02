import QtQuick 2.12
import QtQuick.Layouts 1.10
import QtQuick.Controls 2.0

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

import "../js/moment.js" as Moment
import "../js/moment-timezone-with-data.js" as MomentTimezone

Item {
    id: root
    objectName: "SMSListContainer"
    property bool isExitedMouseAreaPress: false // To prevent onReleased invoked after onExited

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

    Component {
        id: smsListDelegate
        Rectangle {
            id: containerID
            width: smsListView.width - 15
            height: 105
            color: QmlStyling.color_transparent
            Rectangle {
                id: unreadIndicator
                width: 15
                height: 15
                radius: 100
                anchors {
                    left: parent.left
                    top: parent.top
                    topMargin: smsNameID.font.pointSize / 2
                               + (containerID.height - columnOfData.height) / 2
                }
                color: {
                    if (read == 0) {
                        QmlStyling.color_C03
                    } else {
                        QmlStyling.color_transparent
                    }
                }
            }

            Column {
                id: columnOfData
                width: containerID.width - 20
                height: containerID.height - 5
                spacing: 2
                anchors {
                    left: unreadIndicator.right
                    leftMargin: 5
                    verticalCenter: parent.verticalCenter
                }

                Row {
                    id: nameAndDateRowID
                    width: parent.width - 20
                    spacing: 10
                    TWText {
                        id: smsNameID
                        width: 340
                        text: address
                        elide: Text.ElideRight
                        color: QmlStyling.color_C01
                        font.pixelSize: QmlStyling.fontPixelSize_F1
                        font.bold: true
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignLeft
                        state: "DynamicColor"
                    }
                    TWText {
                        id: smsDateID
                        width: parent.width - smsNameID.width
                        wrapMode: Text.Wrap
                        color: QmlStyling.color_C01
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignRight
                        font.pixelSize: QmlStyling.fontPixelSize_F3
                        state: "DynamicColor"

                        property string smsDate: date
                        // smsDateArr [DOW, Day, Month, Year, HH:mm]
                        property var smsDateArr: smsDate.split('-')

                        property date currentDate: new Date()
                        property string dateString: currentDate.toLocaleString(
                                                        Locale.ShortFormat)
                        // splitDateString [Month/Day/Year hh:mm AMPM]
                        property var splitDateString: dateString.split(' ')
                        // currentDateArr [Month Day Year]
                        property var currentDateArr: getDateWithTimeZone(
                                                         "Asia/Bangkok").toString(
                                                         ).split('/')

                        text: {
                            var result = ""
                            var dayCalibFromMonth = 0

                            // year
                            if (parseInt(smsDateArr[3]) < parseInt(
                                        currentDateArr[2])) {

                                // If sms year and current year are next to eachother
                                if (parseInt(smsDateArr[2]) === 12 && parseInt(
                                            currentDateArr[0]) === 1) {

                                    // We have 4 types of months: 28days, 29days, 30days, 31days -> Get appropriate ratio
                                    // But with this special case, the last month is 12 and current month is 1

                                    // To check in a week or not
                                    var calculateInAWeek1 = Math.abs(
                                                parseInt(
                                                    smsDateArr[1]) - parseInt(
                                                    currentDateArr[1]))

                                    // If in a week
                                    if (calculateInAWeek1 >= 24) {
                                        if (calculateInAWeek1 === 30) {
                                            // Yesterday
                                            result = "Yesterday"
                                        } else {
                                            // DOW
                                            result = smsDateArr[0]
                                        }
                                    } else {
                                        // Not in a week -> Display date
                                        result = smsDateArr[1] + "/" + smsDateArr[2]
                                                + "/" + smsDateArr[3]
                                    }
                                } else {
                                    // Not next to eachother -> Display date
                                    result = smsDateArr[1] + "/" + smsDateArr[2]
                                            + "/" + smsDateArr[3]
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
                                                parseInt(
                                                    smsDateArr[1]) - parseInt(
                                                    currentDateArr[1]))

                                        // If in a week
                                        if (calculateInAWeek2 >= (23 + dayCalibFromMonth)) {
                                            // Check yesterday
                                            if (calculateInAWeek2 === (29 + dayCalibFromMonth)) {
                                                result = "Yesterday"
                                            } else {
                                                // DOW
                                                result = smsDateArr[0]
                                            }
                                        } else {
                                            // Not in a week - > Display date
                                            result = smsDateArr[1] + "/" + smsDateArr[2]
                                                    + "/" + smsDateArr[3]
                                        }
                                    } else {
                                        // Not next to eachother -> Display date
                                        result = smsDateArr[1] + "/" + smsDateArr[2]
                                                + "/" + smsDateArr[3]
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
                                                // Today -> Display time
                                                result = smsDateArr[4]
                                            } else if (calculateInAWeek3 === 1) {
                                                // Yesterday
                                                result = "Yesterday"
                                            } else {
                                                // DOW
                                                result = smsDateArr[0]
                                            }
                                        } else {
                                            // Not in a week -> Dislay date
                                            result = smsDateArr[1] + "/" + smsDateArr[2]
                                                    + "/" + smsDateArr[3]
                                        }
                                    }
                                }
                            }
                            return result
                        }
                    }
                }
                TWText {
                    id: smsTextId
                    text: body
                    elide: Text.ElideRight
                    width: containerID.width - 20
                    color: QmlStyling.color_C01
                    font.pixelSize: QmlStyling.fontPixelSize_F3
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    maximumLineCount: 2
                    state: "DynamicColor"
                }
            }

            Rectangle {
                id: separatorID
                width: containerID.width
                height: 2
                color: QmlStyling.color_C08
                anchors {
                    right: parent.right
                    bottom: containerID.bottom
                }
            }
            MouseArea {
                property bool isExited: false
                anchors.fill: parent
                onPressed: {
                    root.isExitedMouseAreaPress = false
                    containerID.color = settingHandler.themeModel.smsColorModel[SharedConstants.sms_press_list]
                }
                onPressAndHold: {
                    containerID.color = settingHandler.themeModel.smsColorModel[SharedConstants.sms_press_list]
                }

                onReleased: {
                    containerID.color = "transparent"
                    if (!root.isExitedMouseAreaPress) {
                        phoneControllerModel.currentIndexList = index
                        phoneControllerModel.smsItemSelected = address
                    }
                }
                onCanceled: {
                    containerID.color = "transparent"
                }
                onExited: {
                    root.isExitedMouseAreaPress = true
                    containerID.color = "transparent"
                }
            }
        }
    }

    ListView {
        id: smsListView
        delegate: smsListDelegate
        model: smsListModel
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
            parent: smsListView
            interactive: false
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            contentItem: Rectangle {
                radius: 20
                color: QmlStyling.color_C08
            }
            visible: smsListView.contentHeight > smsListView.height
        }
    }
    Component.onCompleted: {
        // Jump to the position of list
        smsListView.positionViewAtIndex(phoneControllerModel.currentIndexList,
                                        ListView.Center)
    }
}
