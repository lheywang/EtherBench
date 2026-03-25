import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "settings" as Settings

Page {
    id: settingsPage

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        SplitView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: Qt.Horizontal

            Settings.Tree {
                SplitView.fillWidth: true
                SplitView.minimumWidth: 300
            }

            Settings.Editor {
                SplitView.fillWidth: true
                SplitView.minimumWidth: 150
                SplitView.maximumWidth: 500
            }
        }
    }
}
