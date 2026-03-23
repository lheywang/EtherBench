import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

import App

Rectangle {
    id: logsRoot

    color: "#1e1e1e"
    border.color: "#333333"

    property int selectedRow: -1
    property var selectedData: null

    TableModel {
        id: mockModel

        TableModelColumn {
            display: "timeStr"
        }
        TableModelColumn {
            display: "busStr"
        }
        TableModelColumn {
            display: "dirStr"
        }
        TableModelColumn {
            display: "dataHex"
        }

        rows: [
            {
                timeStr: "10:15:02.123",
                busStr: "CAN",
                dirStr: "TX",
                dataHex: "DE AD BE EF"
            },
            {
                timeStr: "10:15:02.145",
                busStr: "I2C",
                dirStr: "RX",
                dataHex: "04 4A"
            },
            {
                timeStr: "10:15:02.180",
                busStr: "CAN",
                dirStr: "RX",
                dataHex: "00 11 22 33 44 55"
            },
            {
                timeStr: "10:15:02.201",
                busStr: "SPI",
                dirStr: "TX",
                dataHex: "FF FF"
            }
        ]
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 1
        spacing: 0

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

            model: mockModel
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

            delegate: Rectangle {
                implicitHeight: 24

                color: (logsRoot.selectedRow === row) ? "#094771" : ((row % 2 === 0) ? "#252526" : "#2d2d30")

                TapHandler {
                    onTapped: {
                        logsRoot.selectedRow = row;
                        console.log("Trame selectionnee, index :", row);
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
