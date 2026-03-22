import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QtQuick.Controls.Material

import App
import "views"
import "components"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("EtherBench")
    color: "#ececec"

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            Action {
                text: qsTr("Settings")
                shortcut: "Ctrl+,"
                onTriggered: console.log("Not implemented for now...")
            }

            MenuSeparator {}

            Action {
                text: qsTr("&Quit")
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }

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
        }
    }

    StackLayout {
        id: viewContainer
        anchors.fill: parent

        currentIndex: SystemController.currentView

        Home {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Memory {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        InputOutput {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Sequences {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Debugger {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
