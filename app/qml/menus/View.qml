import QtQuick
import QtQuick.Controls

import App

Menu {
    title: qsTr("&View")

    Action {
        text: qsTr("Home")
        shortcut: "Ctrl+H"
        onTriggered: SystemController.setCurrentView(SystemController.Home)
    }
    Action {
        text: qsTr("Memory")
        shortcut: "Ctrl+M"
        onTriggered: SystemController.setCurrentView(SystemController.Memory)
    }
    Action {
        text: qsTr("Serial IO")
        shortcut: "Ctrl+B"
        onTriggered: SystemController.setCurrentView(SystemController.InputOutput)
    }
    Action {
        text: qsTr("Sequences")
        shortcut: "Ctrl+K"
        onTriggered: SystemController.setCurrentView(SystemController.Sequences)
    }
    Action {
        text: qsTr("Debugger")
        shortcut: "Ctrl+D"
        onTriggered: SystemController.setCurrentView(SystemController.Debugger)
    }
    Action {
        text: qsTr("Help")
        shortcut: "F1"
        onTriggered: SystemController.setCurrentView(SystemController.Help)
    }
}
