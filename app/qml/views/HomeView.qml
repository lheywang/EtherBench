import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench

Page {

    background: Rectangle {
        color: Theme.background
    }

    Text {
        anchors.centerIn: parent
        text: "Home"
        font.pixelSize: Theme.fontSizeTitle
        color: Theme.textPrimary
    }
}
