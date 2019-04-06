import QtQuick 2.0

Rectangle {
    width: 200
    height: 20
    radius: 10
//    anchors.left: leftRightButton.right
//    anchors.leftMargin: 10
//    anchors.verticalCenter: parent.verticalCenter

    color: "#a82828"

    property bool inputFocus: false

    //    signal startSearch
    TextInput {
        id: searchEdit
        width: parent.width
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        selectByMouse: true

        text: "搜索音乐，视频，歌词，电台"
        font.pixelSize: 12
        maximumLength: 20
        color: "#C77373"
        focus: inputFocus
        activeFocusOnPress: inputFocus
        onFocusChanged: {
            if (focus) {
                text = ""
            } else
                text = "搜索音乐，视频，歌词，电台"
        }
    }
}
