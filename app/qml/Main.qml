import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QtQuick.Controls.Material

import App.Views 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("EtherBench")
    color: "#ececec"

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            MenuItem {
                text: qsTr("Settings")
                shortcut: "Ctrl+,"
                onTriggered: console.log("Not implemented for now...")
            }

            MenuSeparator{}

            MenuItem {
                text: qsTr("&Quitter")
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("&View")
            
            MenuItem {
                text: qsTr("Home")
                shortcut: "Ctrl+H"
                onTriggered: sysController.setCurrentView(SystemController.Home)
            }
            MenuItem {
                text: qsTr("Debugger")
                shortcut: "Ctrl+D"
                onTriggered: sysController.setCurrentView(SystemController.Debugger)
            }
            MenuItem {
                text: qsTr("Memory")
                shortcut: "Ctrl+M"
                onTriggered: sysController.setCurrentView(SystemController.Memory)
            }
            MenuItem {
                text: qsTr("Sequences")
                shortcut: "Ctrl+K"
                onTriggered: sysController.setCurrentView(SystemController.Memory)
            }
        }
    }

    StackLayout {
        id: viewContainer
        anchors.fill: parent

        currentIndex: sysController.currentView

        Home {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Memory {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Sequences {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        InputOutput {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

    }
}