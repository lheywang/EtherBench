import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench
import EtherBench.Core

Rectangle {
    id: detailPane

    border.color: Theme.panelBackground
    radius: Theme.borderRadius

    property bool hasData: SystemCore.decoder.decodedTimestamp !== ""

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.standardMargin
        spacing: 10

        Label {
            text: "Inspector"
            Layout.fillWidth: true

            font {
                bold: Theme.fontBoldTitle
                pixelSize: Theme.fontSizeTitle
            }

            color: Theme.textPrimary
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: Theme.panelBackground
        }

        GridLayout {
            Layout.fillWidth: true

            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            visible: detailPane.hasData

            Label {
                text: "Timestamp:"
                color: Theme.textPrimary
            }

            Label {
                text: SystemCore.decoder.decodedTimestamp
                font.family: Theme.fontStandard
                color: "#ffffff"
                Layout.fillWidth: true
            }

            Label {
                text: "Bus:"
                color: Theme.textPrimary
            }

            Label {
                text: SystemCore.decoder.decodedBus
                font.family: Theme.fontStandard
                color: "#ffffff"
            }

            Label {
                text: "Payload:"
                color: Theme.textPrimary
            }

            Label {
                text: SystemCore.decoder.decodedPayload
                font.family: Theme.fontStandard
                color: "#00BCD4"
            }
        }

        Label {
            text: "Select a packet to inspect"
            color: Theme.panelBackground
            font.italic: true
            Layout.alignment: Qt.AlignCenter
            visible: !detailPane.hasData
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
