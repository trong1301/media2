import QtQuick 2.12
import QtQuick.Layouts 1.10
import QtQuick.Controls 2.0

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

import "../js/moment.js" as Moment
import "../js/moment-timezone-with-data.js" as MomentTimezone

Item {
    id: root
    objectName: "callLogListScreen"
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
        id: callLogDelegate
        Rectangle {
            id: containerID
            width: callLogListview.width - 15
            height: 105
            color: QmlStyling.color_transparent
            Row {
                id: rowID
                spacing: 10
                width: containerID.width - 20
                height: containerID.height - 5
                anchors {
                    verticalCenter: parent.verticalCenter
                }
                Image {
                    id: callStatusImage
                    width: 67
                    height: 67
                    fillMode: Image.PreserveAspectFit
                    mipmap: true
                    anchors.verticalCenter: parent.verticalCenter

                    states: [
                        State {
                            name: "missCall"
                            when: callLogType === 3
                            PropertyChanges {
                                target: callStatusImage
                                source: "qrc:/images/ICN_XXLICON_MISSED_CALL"
                            }
                        },
                        State {
                            name: "outcomingCall"
                            when: callLogType === 2
                            PropertyChanges {
                                target: callStatusImage
                                source: "qrc:/images/ICN_XXLICON_OUTCOMING_CALL"
                            }
                        },
                        State {
                            name: "incomingCall"
                            when: callLogType === 1
                            PropertyChanges {
                                target: callStatusImage
                                source: "qrc:/images/ICN_XXLICON_INCOMING_CALL"
                            }
                        }
                    ]
                }
                Column {
                    anchors.top: callStatusImage.top
                    spacing: 7
                    TWText {
                        id: callLogNameID
                        width: 360
                        text: callLogName
                        elide: Text.ElideRight
                        font.pixelSize: QmlStyling.fontPixelSize_F2
                        font.bold: true
                        horizontalAlignment: Text.AlignLeft
                        state: "DynamicColor"
                    }
                    TWText {
                        id: callLogNumberID
                        width: callLogNameID.width
                        font.pixelSize: QmlStyling.fontPixelSize_F2
                        horizontalAlignment: Text.AlignLeft
                        wrapMode: Text.Wrap
                        state: "DynamicColor"

                        property string mCallLogDate: callLogDate
                        // mCallLogDateArr [DOW, Day, Month, Year, HH:mm]
                        property var mCallLogDateArr: mCallLogDate.split('-')

                        // currentDateArr [Month Day Year]
                        property var currentDateArr: getDateWithTimeZone(
                                                         "Asia/Bangkok").toString(
                                                         ).split('/')
                        text: {
                            var result = ""
                            var dayCalibFromMonth = 0

                            // year
                            if (parseInt(mCallLogDateArr[3]) < parseInt(
                                        currentDateArr[2])) {

                                // If sms year and current year are next to eachother
                                if (parseInt(mCallLogDateArr[2]) === 12
                                        && parseInt(currentDateArr[0]) === 1) {

                                    // We have 4 types of months: 28days, 29days, 30days, 31days -> Get appropriate ratio
                                    // But with this special case, the last month is 12 and current month is 1

                                    // To check in a week or not
                                    var calculateInAWeek1 = Math.abs(
                                                parseInt(
                                                    mCallLogDateArr[1]) - parseInt(
                                                    currentDateArr[1]))

                                    // If in a week
                                    if (calculateInAWeek1 >= 24) {
                                        if (calculateInAWeek1 === 30) {
                                            // Yesterday
                                            result = "Yesterday " + mCallLogDateArr[4]
                                        } else {
                                            // DOW
                                            result = mCallLogDateArr[0] + " " + mCallLogDateArr[4]
                                        }
                                    } else {
                                        // Not in a week -> Display date
                                        result = mCallLogDateArr[1] + "/" + mCallLogDateArr[2] + "/"
                                                + mCallLogDateArr[3] + " " + mCallLogDateArr[4]
                                    }
                                } else {
                                    // Not next to eachother -> Display date
                                    result = mCallLogDateArr[1] + "/" + mCallLogDateArr[2] + "/"
                                            + mCallLogDateArr[3] + " " + mCallLogDateArr[4]
                                }
                            } else {
                                // month
                                if (parseInt(mCallLogDateArr[2]) < parseInt(
                                            currentDateArr[0])) {

                                    // If sms month and current month are next to eachother
                                    if ((parseInt(currentDateArr[0]) - parseInt(
                                             mCallLogDateArr[2])) === 1) {

                                        // We have 4 types of months: 28days, 29days, 30days, 31days -> Get appropriate ratio
                                        dayCalibFromMonth = getDayCalib(
                                                    parseInt(
                                                        mCallLogDateArr[2]))

                                        // To check in a week or not
                                        let calculateInAWeek2 = Math.abs(
                                                parseInt(
                                                    mCallLogDateArr[1]) - parseInt(
                                                    currentDateArr[1]))

                                        // If in a week
                                        if (calculateInAWeek2 >= (23 + dayCalibFromMonth)) {
                                            // Check yesterday
                                            if (calculateInAWeek2 === (29 + dayCalibFromMonth)) {
                                                result = "Yesterday " + mCallLogDateArr[4]
                                            } else {
                                                // DOW
                                                result = mCallLogDateArr[0] + " "
                                                        + mCallLogDateArr[4]
                                            }
                                        } else {
                                            // Not in a week - > Display date
                                            result = mCallLogDateArr[1] + "/" + mCallLogDateArr[2]
                                                    + "/" + mCallLogDateArr[3]
                                                    + " " + mCallLogDateArr[4]
                                        }
                                    } else {
                                        // Not next to eachother -> Display date
                                        result = mCallLogDateArr[1] + "/" + mCallLogDateArr[2] + "/"
                                                + mCallLogDateArr[3] + " " + mCallLogDateArr[4]
                                    }
                                } else {
                                    //day
                                    if (parseInt(
                                                mCallLogDateArr[1]) <= parseInt(
                                                currentDateArr[1])) {

                                        // To check in a week or not
                                        let calculateInAWeek3 = parseInt(
                                                currentDateArr[1]) - parseInt(
                                                mCallLogDateArr[1])

                                        // In a week
                                        if (calculateInAWeek3 <= 7) {
                                            if (calculateInAWeek3 === 0) {
                                                // Today + Display time
                                                result = "Today " + mCallLogDateArr[4]
                                            } else if (calculateInAWeek3 === 1) {
                                                // Yesterday
                                                result = "Yesterday " + mCallLogDateArr[4]
                                            } else {
                                                // DOW
                                                result = mCallLogDateArr[0] + " "
                                                        + mCallLogDateArr[4]
                                            }
                                        } else {
                                            // Not in a week -> Dislay date
                                            result = mCallLogDateArr[1] + "/" + mCallLogDateArr[2]
                                                    + "/" + mCallLogDateArr[3]
                                                    + " " + mCallLogDateArr[4]
                                        }
                                    }
                                }
                            }
                            return result
                        }
                    }
                }
                Image {
                    id: callButtonID
                    width: 75
                    height: 75
                    source: "qrc:/images/ICN_LICON_CALL5"
                    fillMode: Image.PreserveAspectFit
                    mipmap: true
                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            root.isExitedMouseAreaPress = false
                            animExpand.start()
                        }
                        onReleased: {
                            animNormal.start()
                            if (!root.isExitedMouseAreaPress) {
                                if (viewManager.isNativeBuild()) {
                                    // For native, keep for reference
                                    phoneControllerModel.nameUserCalling = callLogName
                                    viewManager.lastViewState = viewManager.viewState
                                    viewManager.requestChangeViewState(
                                                SharedConstants.viewAnyWhere,
                                                SharedConstants.viewTopOutgoingCall)
                                } else {
                                    phoneControllerModel.makeAPhoneCall(
                                                callLogNumber)
                                }

                                // To jump back to previous position
                                phoneControllerModel.currentIndexList = index
                            }
                        }
                        onCanceled: {
                            animNormal.start()
                        }
                        onExited: {
                            root.isExitedMouseAreaPress = true
                            animNormal.start()
                        }
                    }
                }

                // Expand the button
                PropertyAnimation {
                    id: animExpand
                    target: callButtonID
                    property: "scale"
                    to: 1.3
                    duration: 100
                    easing.type: Easing.InOutQuad
                }

                // Shrink back to normal
                PropertyAnimation {
                    id: animNormal
                    target: callButtonID
                    property: "scale"
                    to: 1.0
                    duration: 100
                    easing.type: Easing.InOutQuad
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
        }
    }

    ListView {
        id: callLogListview
        delegate: callLogDelegate
        model: callLogListModel
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
            parent: callLogListview
            interactive: false
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            contentItem: Rectangle {
                radius: 20
                color: QmlStyling.color_C08
            }
            visible: callLogListview.contentHeight > callLogListview.height
        }
    }
    Component.onCompleted: {
        // Jump to the position of list
        callLogListview.positionViewAtIndex(
                    phoneControllerModel.currentIndexList, ListView.Center)
    }
}
