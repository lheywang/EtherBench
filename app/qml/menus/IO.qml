import QtQuick
import QtQuick.Controls

import App

Instantiator {
    active: SystemController.currentView === SystemController.Debugger || SystemController.currentView === SystemController.InputOutput

    delegate: Menu {
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

    // Callbacks
    onObjectAdded: function (index, object) {
        menuBar.insertMenu(2, object);
    }
    onObjectRemoved: function (index, object) {
        menuBar.removeMenu(object);
    }
}
