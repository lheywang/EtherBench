import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench

RowLayout {
    spacing: 5

    Rectangle {
        width: 12
        height: 12
        radius: 6

        color: Theme.textStatusInvalid
    }

    Label {
        text: "USB"
        font.bold: Theme.textStatusBold
        color: Theme.textPrimary
    }
}
