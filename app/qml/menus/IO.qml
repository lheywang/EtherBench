import QtQuick
import QtQuick.Controls

import App

Menu {
    title: qsTr("IO")

    Action {
        text: qsTr("Save session")
        onTriggered: console.log("Saving debugging session")
    }

    Action {
        text: qsTr("Load session")
        onTriggered: console.log("Loading a debugging session")
    }

    MenuSeparator {}

    Action {
        text: qsTr("Save session to logs")
        onTriggered: console.log("Writting human log text")
    }
}
