import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QtQuick.Controls.Material

import EtherBench.Bridge
import EtherBench

import "views" as Views
import "menus" as Menus
import "components" as Components

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: qsTr("EtherBench")
    color: Theme.panelBackground

    /*
     * Header bar
     */
    header: ToolBar {

        background: Rectangle {
            color: Theme.panelBackground
        }

        RowLayout {
            anchors {
                fill: parent
                leftMargin: Theme.standardMargin
                rightMargin: Theme.standardMargin
            }

            spacing: Theme.standardSpacing

            MenuBar {
                id: mainMenuBar

                Layout.fillWidth: true

                background: Rectangle {
                    color: Theme.panelBackground
                }

                // These are always shows
                Menus.File {}
                Menus.View {}
            }

            // Usefull statuses on the top right corner
            RowLayout {
                Layout.alignment: Qt.AlignVCenter
                Layout.rightMargin: Theme.standardMargin
                spacing: Theme.standardSpacing

                Components.StatusETH {}
                Components.StatusUSB {}
            }
        }
    }

    /*
     * Instantiate all the conditionnal elements on the menubar :
     */
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
