import QtQuick
import QtQuick.Controls

import App

Instantiator {
    active: SystemController.currentView === SystemController.Debugger

    delegate: Menu {
        title: qsTr("Debugger")

        Action {
            text: qsTr("Save debugging session to file")
            onTriggered: console.log("Loading a new parameter file...")
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
