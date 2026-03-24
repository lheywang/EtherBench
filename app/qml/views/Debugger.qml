import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import App
import "debugger" as Debugger

Page {
    id: debuggerView

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
                SplitView.minimumWidth: 300
            }
            Debugger.Details {
                id: detailsPane
                SplitView.fillWidth: true
                SplitView.preferredWidth: 250
                SplitView.minimumWidth: 150
                SplitView.maximumWidth: 500
            }
        }
    }
}
