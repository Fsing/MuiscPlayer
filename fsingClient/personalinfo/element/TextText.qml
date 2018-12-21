import QtQuick 2.0

Item {
    width: parent.width
    height: 20
    property alias titleText: title.text
    property alias contentText: content.text

    Row{
        anchors.fill: parent
        spacing: 5
        Text {
            id: title
        }
        Text {
            id: content
        }
    }
}
