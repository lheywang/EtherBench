import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import EtherBench.Core

Rectangle {
    color: "#1e1e1e"
    border.color: "#333333"

    TreeView {
        id: settingsTree
        anchors.fill: parent
        model: SystemCore.settings

        delegate: TreeViewDelegate {
            id: treeDelegate

            contentItem: Row {
                spacing: 10

                // Affichage du nom du paramètre
                Text {
                    text: model.parameterName
                    width: 200
                    verticalAlignment: Text.AlignVCenter
                }

                // Composant d'édition dynamique
                Loader {
                    id: editorLoader
                    sourceComponent: model.allowedValues.length > 0 ? comboBoxComponent : textFieldComponent
                }

                Component {
                    id: comboBoxComponent
                    ComboBox {
                        model: treeDelegate.model.allowedValues // Utilise les contraintes
                        currentText: treeDelegate.model.parameterValue
                        onActivated: {
                            treeDelegate.model.parameterValue = currentText;
                        }
                    }
                }

                Component {
                    id: textFieldComponent
                    TextField {
                        text: treeDelegate.model.parameterValue
                        onEditingFinished: {
                            treeDelegate.model.parameterValue = text;
                        }
                    }
                }
            }
        }
    }
}
