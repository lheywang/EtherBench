import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench
import "debugger" as Debugger

Page {
    id: debuggerView

    background: Rectangle {
        color: Theme.background
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        SplitView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: Qt.Horizontal

            Debugger.Logs {
                id: logsPane
                SplitView.fillWidth: true
                SplitView.minimumWidth: Theme.panelMinimalWidth
            }

            Debugger.Details {
                id: detailsPane
                SplitView.fillWidth: true
                SplitView.preferredWidth: Theme.panelPreferredWidth
                SplitView.minimumWidth: Theme.panelMinimalWidth
                SplitView.maximumWidth: Theme.panelMaximalWidth
            }
        }
    }
}
