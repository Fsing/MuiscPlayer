import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    color: "white"

    property var listmodel: leftArea.listmodel
    property alias leftArea: leftArea

    SplitView{
        width: parent.width
        height: parent.height
        orientation: Qt.Horizontal
    LeftArea {
        id: leftArea
        width: 200
    }
    RightArea {
        id: rightArea

    }
   }
}
