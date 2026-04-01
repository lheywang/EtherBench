import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench
import EtherBench.Core

Rectangle {
    id: rootSettingsPanel

    color: Theme.background
    border.color: Theme.border
    border.width: 1

    TreeView {
        id: settingsTree
        anchors.fill: parent
        anchors.margins: 5
        model: SystemCore.settings
        selectionModel: ItemSelectionModel {
            model: SystemCore.settings
        }

        property alias currentIndex: settingsTree.selectionModel.currentIndex

        clip: true

        delegate: TreeViewDelegate {
            id: treeDelegate

            implicitWidth: settingsTree.width

            contentItem: Text {
                text: model.parameterName || "..."
                color: treeDelegate.selected ? Theme.textAccent : Theme.textPrimary
                font.bold: treeDelegate.selected || treeDelegate.hasChildren
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            onClicked: {
                if (modelIndex.valid) {
                    settingsTree.selectionModel.setCurrentIndex(modelIndex, ItemSelectionModel.ClearAndSelect | ItemSelectionModel.Rows);
                }
            }
            // contentItem: Row {
            //     spacing: 10

            //     Text {
            //         Layout.preferredWidth: Theme.panelPreferredWidth
            //         Layout.alignment: Qt.AlignVCenter

            //         text: model.parameterName ? model.parameterName : "Loading ..."

            //         elide: Text.ElideRight
            //         font.bold: treeDelegate.hasChildren
            //         font.pixelSize: treeDelegate.hasChildren ? Theme.fontSizeTitle : Theme.fontSizeNormal

            //         color: Theme.textPrimary
            //     }

            //     Loader {
            //         id: editorLoader

            //         Layout.fillWidth: true
            //         Layout.alignment: Qt.AlignVCenter

            //         property bool hasChoices: (model.allowedValues !== undefined) && (model.allowedValues.length > 0)
            //         sourceComponent: treeDelegate.hasChildren ? null : (hasChoices ? comboBoxComponent : textFieldComponent)
            //     }

            //     Component {
            //         id: comboBoxComponent

            //         ComboBox {
            //             id: controlCb
            //             model: treeDelegate.model.allowedValues

            //             currentIndex: find(treeDelegate.model.parameterValue)

            //             background: Rectangle {
            //                 implicitHeight: 30
            //                 color: Theme.popUpBackground
            //                 border.color: controlCb.activeFocus ? Theme.borderSelected : Theme.border
            //                 radius: Theme.borderRadius
            //             }

            //             contentItem: Text {
            //                 text: controlCb.currentText
            //                 color: Theme.popUpBackground
            //                 verticalAlignment: Text.AlignVCenter
            //                 leftPadding: 10
            //             }

            //             popup: Popup {
            //                 y: controlCb.height - 1
            //                 width: Math.max(controlCb.width, 250)
            //                 padding: 1

            //                 contentItem: ListView {
            //                     clip: true

            //                     implicitHeight: Math.min(contentHeight, 300)

            //                     model: controlCb.popup.visible ? controlCb.delegateModel : null
            //                     currentIndex: controlCb.highlightedIndex
            //                     ScrollIndicator.vertical: ScrollIndicator {}
            //                 }

            //                 background: Rectangle {
            //                     color: Theme.popUpBackground
            //                     border.color: Theme.border
            //                     radius: 3
            //                 }
            //             }

            //             onActivated: {
            //                 if (treeDelegate.model.parameterValue !== currentText) {
            //                     treeDelegate.model.parameterValue = currentText;
            //                 }
            //             }
            //         }
            //     }

            //     Component {
            //         id: textFieldComponent

            //         TextField {
            //             id: controlTf
            //             text: treeDelegate.model.parameterValue !== undefined ? treeDelegate.model.parameterValue : ""
            //             color: Theme.popUpBackground

            //             background: Rectangle {
            //                 implicitHeight: 30
            //                 color: Theme.popUpBackground
            //                 border.color: controlTf.activeFocus ? Theme.border : Theme.borderSelected
            //                 border.width: Theme.borderHeight
            //                 radius: Theme.borderRadius
            //             }

            //             onEditingFinished: {
            //                 if (treeDelegate.model.parameterValue !== text) {
            //                     treeDelegate.model.parameterValue = text;
            //                 }
            //             }
            //         }
            //     }
            // }
        }
    }
}
