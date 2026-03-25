import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import App
import EtherBench.Core

Rectangle {
    id: detailPane
    color: "#252526"
    border.color: "#333333"

    property bool hasData: SystemCore.decoder.decodedTimestamp !== ""

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

            visible: detailPane.hasData

            Label {
                text: "Timestamp:"
                color: "#888888"
            }
            Label {
                text: SystemCore.decoder.decodedTimestamp
                font.family: "Consolas"
                color: "#ffffff"
                Layout.fillWidth: true
            }

            Label {
                text: "Bus:"
                color: "#888888"
            }
            Label {
                text: SystemCore.decoder.decodedBus
                font.family: "Consolas"
                color: "#ffffff"
            }

            Label {
                text: "Payload:"
                color: "#888888"
            }
            Label {
                text: SystemCore.decoder.decodedPayload
                font.family: "Consolas"
                color: "#00BCD4"
            }
        }

        Label {
            text: "Select a packet to inspect"
            color: "#666666"
            font.italic: true
            Layout.alignment: Qt.AlignCenter
            visible: !detailPane.hasData
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
