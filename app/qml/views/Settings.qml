import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        SplitView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: Qt.Horizontal

            Rectangle {
                id: selectionPanel
                color: "#1e1e1e"
                border.color: "#333333"

                SplitView.fillWidth: true
                SplitView.minimumWidth: 300
            }

            Rectangle {
                id: detailPane
                color: "#252526"
                border.color: "#333333"

                SplitView.preferredWidth: 250
                SplitView.minimumWidth: 150
                SplitView.maximumWidth: 500
            }
        }
    }
}
