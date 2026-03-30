import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench

import "settings" as Settings

Page {
    id: settingsPage

    background: Rectangle {
        color: Theme.background
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.standardMargin

        Settings.Tree {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
