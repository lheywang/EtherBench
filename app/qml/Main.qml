import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QtQuick.Controls.Material

import App
import "views" as Views
import "menus" as Menus
import "components" as Components

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("EtherBench")
    color: "#ececec"

    // These are always on screen
    menuBar: MenuBar {
        Menus.File {}
        Menus.View {}
    }

    // These aren't always shown :
    Menus.Build {}
    Menus.IO {}
    Menus.Memory {}
    Menus.Debugger {}

    StackLayout {
        id: viewContainer
        anchors.fill: parent

        currentIndex: SystemController.currentView

        Views.Home {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Views.Memory {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Views.InputOutput {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Views.Sequences {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Views.Debugger {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Views.Settings {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Views.Help {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
