import QtQuick 2.0
import QtQuick.Controls 2.1

Popup {
    id: commonDialog
    x: mainWindow.width / 2 - 150
    y: 100

    modal: false
    focus: true
    closePolicy: Popup.CloseOnEscape
    dim: false
}
