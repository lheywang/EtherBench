import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QtQuick.Controls.Material

import EtherBench.Bridge
import "views" as Views
import "menus" as Menus
import "components" as Components

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: qsTr("EtherBench")
    color: "#ececec"
    /*
     * Header bar
     */
    header: ToolBar {
        background: Rectangle {
            color: '#b1b1b1'
        }

        RowLayout {
            anchors.fill: parent
            spacing: 0

            MenuBar {
                id: mainMenuBar

                Layout.fillWidth: true
                background: Rectangle {
                    color: "transparent"
                }

                // These are always shows
                Menus.File {}
                Menus.View {}
            }

            RowLayout {
                Layout.alignment: Qt.AlignVCenter
                Layout.rightMargin: 15
                spacing: 15

                Components.StatusETH {}
                Components.StatusUSB {}
            }
        }
    }

    Components.ContextualMenu {
        targetMenuBar: mainMenuBar
        active: SystemController.currentView === SystemController.Memory
        delegate: Menus.Memory {}
    }

    Components.ContextualMenu {
        targetMenuBar: mainMenuBar
        active: SystemController.currentView === SystemController.Sequences
        delegate: Menus.Build {}
    }

    Components.ContextualMenu {
        targetMenuBar: mainMenuBar
        active: SystemController.currentView === SystemController.InputOutput || SystemController.currentView === SystemController.Debugger
        delegate: Menus.IO {}
    }

    Components.ContextualMenu {
        targetMenuBar: mainMenuBar
        active: SystemController.currentView === SystemController.Debugger
        delegate: Menus.Debugger {}
    }

    /*
     * Windows handling ...
     */
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
