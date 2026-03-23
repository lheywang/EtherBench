import QtQuick
import QtQuick.Controls

import App

Menu {
    title: qsTr("Memory")

    Action {
        text: qsTr("Load binary")
        onTriggered: console.log("Loading binary file")
    }

    Action {
        text: qsTr("Save binary")
        onTriggered: console.log("Saving binary file")
    }

    MenuSeparator {}

    Action {
        text: qsTr("Read device")
        onTriggered: console.log("Flashing device")
    }

    Action {
        text: qsTr("Flash device")
        onTriggered: console.log("Reading device")
    }

    MenuSeparator {}

    Action {
        text: qsTr("Configure target device")
        onTriggered: console.log("Setting up device")
    }
}
