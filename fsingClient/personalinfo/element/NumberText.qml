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
        }
        Text {
            id: tx
            text: qsTr("动态")
        }
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            numberTextClicked()
        }
    }
}
