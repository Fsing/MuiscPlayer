import QtQuick 2.0
import QtQuick.Controls 2.1

Popup {
    id: commonDialog
    x: parent.x
    y: parent.y

    modal: false
    focus: true
    closePolicy: Popup.CloseOnEscape
    dim: false
}
