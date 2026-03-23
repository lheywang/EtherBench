import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import App

Rectangle {
    id: detailPane
    color: "#252526"
    border.color: "#333333"

    property var currentLog: null

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 10

        Label {
            text: "Inspector"
            font.bold: true
            font.pixelSize: 14
            color: "#cccccc"
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "#444444"
        }

        GridLayout {
            Layout.fillWidth: true
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            visible: currentLog !== null

            Label {
                text: "Timestamp:"
                color: "#888888"
            }
            Label {
                text: currentLog ? currentLog.timeStr : ""
                font.family: "Consolas"
                color: "#ffffff"
                Layout.fillWidth: true
            }

            Label {
                text: "Bus:"
                color: "#888888"
            }
            Label {
                text: currentLog ? (currentLog.busStr + " (" + currentLog.dirStr + ")") : ""
                font.family: "Consolas"
                color: "#ffffff"
            }

            Label {
                text: "Raw Hex:"
                color: "#888888"
            }
            Label {
                text: currentLog ? currentLog.dataHex : ""
                font.family: "Consolas"
                color: "#00BCD4"
            }
        }

        Label {
            text: "Select a packet to inspect"
            color: "#666666"
            font.italic: true
            Layout.alignment: Qt.AlignCenter
            visible: currentLog === null
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
