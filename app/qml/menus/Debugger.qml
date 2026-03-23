import QtQuick
import QtQuick.Controls

import App

Menu {
    title: qsTr("Debugger")

    Action {
        text: qsTr("Save debugging session to file")
        onTriggered: console.log("Loading a new parameter file...")
    }
}
