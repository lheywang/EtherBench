import QtQuick
import QtQuick.Controls

import App

Instantiator {
    active: SystemController.currentView === SystemController.Memory

    delegate: Menu {
        title: qsTr("Memory")

        Action {
            text: qsTr("Load binary")
            onTriggered: console.log("Loading binary file")
        }

        Action {
            text: qsTr("Save binary")
            onTriggered: console.log("Saving binary file")
        }

        MenuSeparator {}

        Action {
            text: qsTr("Read device")
            onTriggered: console.log("Flashing device")
        }

        Action {
            text: qsTr("Flash device")
            onTriggered: console.log("Reading device")
        }

        MenuSeparator {}

        Action {
            text: qsTr("Configure target device")
            onTriggered: console.log("Setting up device")
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
