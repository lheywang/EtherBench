import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QtQuick.Controls.Material

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Base de Développement Qt6")
    color: "#ececec"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        Text {
            text: "Interactions enregistrées : " + sysController.clickCount
            font.pixelSize: 22
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            spacing: 20
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: qsTr("Lancer Calibration")
                onClicked: {
                    console.log("[QML] Requête de calibration envoyée.");
                    sysController.executeAction("CALIBRATION_SEQ_01");
                }
            }

            Button {
                text: qsTr("Arrêt d'Urgence")
                Material.background: Material.Red 
                onClicked: {
                    console.warn("[QML] Interruption manuelle !");
                    sysController.executeAction("EMERGENCY_STOP");
                }
            }
        }
    }
}