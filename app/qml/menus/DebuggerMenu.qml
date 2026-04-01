import QtQuick
import QtQuick.Controls

import EtherBench.Bridge

Menu {
    title: qsTr("Debugger")

    Action {
        text: qsTr("Save debugging session to file")
        onTriggered: console.log("Loading a new parameter file...")
    }
}
