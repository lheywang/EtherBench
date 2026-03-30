import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench
import EtherBench.Core

Rectangle {
    id: logsRoot

    border.color: Theme.border
    radius: Theme.borderRadius

    color: Theme.background

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
                    color: autoScrollToggle.checked ? Theme.textStatusAccentGreen : Theme.textPrimary
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
                color: Theme.panelBackground

                Rectangle {
                    anchors.right: parent.right
                    width: 1
                    height: parent.height
                    color: Theme.panelBackground
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 1
                    color: Theme.panelBackground
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
                    color: Theme.textPrimary
                }
            }

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: Theme.borderHeight
                color: Theme.border
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
                    return 120;
                case 1:
                    return 60;
                case 2:
                    return 60;
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

                color: {
                    if (logsRoot.selectedRow === row)
                        return Theme.textStatusAccentBlue2;
                    if (row % 2 === 0)
                        return Theme.background;
                    return Theme.panelBackground;
                }

                TapHandler {
                    onTapped: {
                        logsRoot.selectedRow = row;
                        SystemCore.decoder.decodeFrameAt(row);
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: display
                    font.family: Theme.fontStandard

                    color: {
                        if (logsRoot.selectedRow === row)
                            return Theme.textSelected;

                        if (display === "RX")
                            return Theme.textStatusAccentGreen;

                        if (display === "TX")
                            return Theme.textStatusAccentBlue1;

                        return Theme.textPrimary;
                    }
                }
            }
        }
    }
}
