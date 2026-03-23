import QtQuick
import QtQml

Instantiator {
    id: root

    property var targetMenuBar: null
    property int insertionIndex: 2

    onObjectAdded: function (index, object) {
        if (targetMenuBar) {
            targetMenuBar.insertMenu(insertionIndex, object);
        } else {
            console.warn("[ContextualMenu] targetMenuBar isn't defined !");
        }
    }

    onObjectRemoved: function (index, object) {
        if (targetMenuBar) {
            targetMenuBar.removeMenu(object);
        }
    }
}
