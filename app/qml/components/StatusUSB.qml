import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import App

RowLayout {
    spacing: 5

    Rectangle {
        width: 12
        height: 12
        radius: 6

        color: '#e01010'
    }

    Label {
        text: "USB"
        font.bold: true
        color: "#cccccc"
    }
}
