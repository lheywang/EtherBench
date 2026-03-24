import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

import App
import EtherBench.Backend

Rectangle {
    id: logsRoot

    color: "#1e1e1e"
    border.color: "#333333"

    property int selectedRow: -1

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 1
        spacing: 0

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "Clear buffer"
                onClicked: console.log("Cliked clear buffer !")
            }

            Item {
                Layout.fillWidth: true
            }

            Switch {
                id: autoScrollToggle
                text: "Auto-scroll"
                checked: true

                contentItem: Text {
                    text: autoScrollToggle.text
                    color: autoScrollToggle.checked ? "#4CAF50" : "#888888"
                    leftPadding: autoScrollToggle.indicator.width + autoScrollToggle.spacing
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        HorizontalHeaderView {
            id: debuggerHeader
            Layout.fillWidth: true
            syncView: debuggerTable
            boundsBehavior: Flickable.StopAtBounds

            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 28
                color: "#2d2d30"

                Rectangle {
                    anchors.right: parent.right
                    width: 1
                    height: parent.height
                    color: "#3e3e42"
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 1
                    color: "#3e3e42"
                }

                Label {
                    anchors.centerIn: parent
                    anchors.margins: 4
                    text: {
                        switch (index) {
                        case 0:
                            return "Timestamp";
                        case 1:
                            return "Bus";
                        case 2:
                            return "Dir";
                        case 3:
                            return "Raw Payload";
                        default:
                            return "";
                        }
                    }
                    font.bold: true
                    font.pixelSize: 12
                    color: "#cccccc"
                }
            }
        }

        TableView {
            id: debuggerTable
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: SystemCore.debuggerModel
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            columnWidthProvider: function (column) {
                switch (column) {
                case 0:
                    return 120; // Timestamp
                case 1:
                    return 60;  // Bus
                case 2:
                    return 60;  // Direction
                case 3:
                    return Math.max(100, debuggerTable.width - 240);
                }
            }

            onContentHeightChanged: {
                if (autoScrollToggle.checked && contentHeight > height) {
                    contentY = contentHeight - height;
                }
            }

            onMovementStarted: {
                if (contentY < (contentHeight - height - 20)) {
                    autoScrollToggle.checked = false;
                }
            }

            onMovementEnded: {
                if (contentY >= (contentHeight - height - 20)) {
                    autoScrollToggle.checked = true;
                }
            }

            delegate: Rectangle {
                implicitHeight: 24

                color: (logsRoot.selectedRow === row) ? "#094771" : ((row % 2 === 0) ? "#252526" : "#2d2d30")

                TapHandler {
                    onTapped: {
                        logsRoot.selectedRow = row;
                        SystemCore.decoder.decodeFrameAt(row);
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: display
                    font.family: "Consolas"

                    color: {
                        if (logsRoot.selectedRow === row)
                            return "#ffffff";
                        if (display === "RX")
                            return "#4CAF50";
                        if (display === "TX")
                            return "#00BCD4";
                        return "#cccccc";
                    }
                }
            }
        }
    }
}
