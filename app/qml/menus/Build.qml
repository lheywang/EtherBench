import QtQuick
import QtQuick.Controls

import App

Instantiator {
    active: SystemController.currentView === SystemController.Sequences

    delegate: Menu {
        title: qsTr("Build")

        Action {
            text: qsTr("Load source")
            onTriggered: console.log("Loading raw sequence file")
        }

        Action {
            text: qsTr("Export to file")
            onTriggered: console.log("Writting raw")
        }

        MenuSeparator {}

        Action {
            text: qsTr("Compile")
            shortcut: "Ctrl+B"
            onTriggered: console.log("Compiling sequence")
        }

        Action {
            text: qsTr("Decompile")
            onTriggered: console.log("Decompiling sequence")
        }

        MenuSeparator {}

        Action {
            text: qsTr("Load to device")
            onTriggered: console.log("Sending sequence to device")
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
