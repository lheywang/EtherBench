import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench
import EtherBench.Core

Rectangle {
    id: rootSettingsEditor

    color: Theme.background
    border.color: Theme.border
    border.width: 1

    property var targetIndex: null

    readonly property var currentData: (targetIndex && targetIndex.valid) ? targetIndex.model : null
    readonly property bool isLeaf: currentData !== null && !SystemCore.settings.hasChildren(targetIndex)

    ColumnLayout {

        anchors {
            fill: parent
            margins: Theme.standardMargin
        }
        spacing: Theme.standardSpacing

        visible: isLeaf

        ColumnLayout {
            Layout.fillWidth: true
            Text {
                text: currentData ? currentData.parameterName : ""
                font.pixelSize: Theme.fontSizeTitle
                font.bold: true
                color: Theme.textPrimary
            }
            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: Theme.border
            }
        }

        Loader {
            id: valueEditorLoader
            Layout.fillWidth: true

            sourceComponent: {
                if (!isLeaf)
                    return null;
                return (currentData.allowedValues && currentData.allowedValues.length > 0) ? comboBoxComponent : textFieldComponent;
            }

            property var parameterValue: currentData ? currentData.parameterValue : ""
            property var allowedValues: currentData ? currentData.allowedValues : []
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Qt.darker(Theme.background, 1.1)
            radius: Theme.borderRadius
            border.color: Theme.border

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                Text {
                    text: "HELP"
                    font.pixelSize: Theme.fontSizeSmall
                    font.bold: true
                    color: Theme.textSecondary
                }
                Text {
                    Layout.fillWidth: true
                    text: currentData ? currentData.helpText : "Select a parameter to see details."
                    wrapMode: Text.WordWrap
                    color: Theme.textPrimary
                }
                Item {
                    Layout.fillHeight: true
                } // Spacer
            }
        }

        Text {
            text: "EtherBench Config Tool v1.0"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.textSecondary
            Layout.alignment: Qt.AlignRight
        }

        Text {
            visible: !isLeaf
            text: "Select a setting to edit"
            color: Theme.textSecondary
        }

        Component {
            id: comboBoxComponent
            ComboBox {
                model: valueEditorLoader.allowedValues
                currentIndex: find(valueEditorLoader.parameterValue)
                onActivated: currentData.parameterValue = currentText
            }
        }

        Component {
            id: textFieldComponent
            TextField {
                text: valueEditorLoader.parameterValue
                onEditingFinished: currentData.parameterValue = text
            }
        }
    }
}
