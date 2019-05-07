import QtQuick 2.0

Item {
    width: 30
    height: 35
    property alias number: number.text
    property alias text: tx.text

    signal numberTextClicked

    Column{
        anchors.fill: parent
//        spacing:
        Text {
            id: number
            text: qsTr("0")
            font.pixelSize: 16
        }
        Text {
            id: tx
            text: qsTr("动态")
            color: "#6b6b6b"
            opacity: numberTextMouse.containsMouse ? 1.0 : 0.8
        }
    }
    MouseArea{
        id:numberTextMouse
        anchors.fill: parent
        hoverEnabled: true
        cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
        onClicked: {
            numberTextClicked()
        }
    }
}
