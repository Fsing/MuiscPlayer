import QtQuick 2.0
import "../../songList"

Rectangle {
    property int index: 1
    color: "yellow"

        Text {
            anchors.centerIn: parent
           text: qsTr("FM")
        }
}
