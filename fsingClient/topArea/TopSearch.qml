import QtQuick 2.0

Rectangle {
    width: 200
    height: 21
    radius: 10
    anchors.left: leftRightButton.right
    anchors.leftMargin: 10
    anchors.verticalCenter: parent.verticalCenter
    signal search

    color: "#a82828"

    property var searchList
    property var searchCount

    //    signal startSearch
    TextInput {
        id: textEdit
        width: parent.width
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        selectByMouse: true

        text: "搜索音乐，视频，歌词，电台"
        //        font.pointSize:
        font.pixelSize: 12
        maximumLength: 20
        color: "#C77373"
        focus: false
        onFocusChanged: {
            if (focus == true) {
                text = ""
            } else
                text = "搜索音乐，视频，歌词，电台"
        }
        onAccepted: {

        }
    }

    onSearch: {
        middleArea.rightArea.stackView.push(
                    middleArea.rightArea.searchComponent)
    }
}
