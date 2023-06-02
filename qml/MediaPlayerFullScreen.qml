import QtQuick 2.10
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1

import TwoWheels.QmlStylingSingleton 1.0
import TwoWheels.SharedConstantsSingleton 1.0

Item {
    ListModel {
        id: musicModel
        Component.onCompleted: {
            loadAudio()
        }
    }

    function loadAudio() {
        var musicList = mediaPlaylistModel.getAllAudioFiles()

        console.log(">> ", musicList)
        musicModel.clear()
        for (var i = 0; i < musicList.length; i++) {
            console.log("--> ", musicList[i])
            musicModel.append({
                                  "_no": i + 1,
                                  "_title": ((StandardPaths.standardLocations(
                                                  StandardPaths.MusicLocation)[0])
                                             + "/" + musicList[i])
                              })
        }
    }

    anchors.fill: parent

    Rectangle {

        width: parent.width
        height: 20
        color: "blue"
    }

    Column {
        width: parent.width
        height: parent.height

        Rectangle {

            width: parent.width
            height: 50
            color: "blue"
        }
        Button {
            id: clickButton
            height: 50
            width: 50
            text: "Click"
            onClicked: {
                console.log("Clicked")
                loadAudio()
            }
        }

        ListView {
            id: listV
            width: 50
            height: 300
            model: musicModel
            delegate: Rectangle {
                width: 50
                height: 50
                border.color: "black"
            }
        }
    }
}
