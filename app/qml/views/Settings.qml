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

    SplitView {
        anchors {
            fill: parent
            margins: Theme.standardMargin
        }

        Settings.Tree {
            id: settingsNav
            SplitView.fillWidth: true
            SplitView.fillHeight: true
        }

        Settings.Editor {
            SplitView.fillWidth: true
            SplitView.fillHeight: true

            SplitView.minimumWidth: Theme.panelMinimalWidth
            SplitView.preferredWidth: Theme.panelPreferredWidth
            SplitView.maximumWidth: Theme.panelMaximalWidth

            targetIndex: settingsNav.currentIndex
        }
    }
}
