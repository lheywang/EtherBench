import QtQuick
import QtQuick.Controls

import App

Menu {
    title: qsTr("&File")

    Action {
        text: qsTr("Settings")
        shortcut: "Ctrl+,"
        onTriggered: console.log("Not implemented for now...")
    }

    Action {
        text: qsTr("Load another parameter file")
        onTriggered: console.log("Loading a new parameter file...")
        enabled: SystemController.currentView === SystemController.Settings
    }

    MenuSeparator {}

    Action {
        text: qsTr("Quit")
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
    }
}
