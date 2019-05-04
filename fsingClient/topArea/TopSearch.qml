import QtQuick 2.0

Rectangle {
    id:search_
    width: 200
    height: 20
    radius: 10
//    anchors.left: leftRightButton.right
//    anchors.leftMargin: 10
//    anchors.verticalCenter: parent.verticalCenter

    //color: "#a82828"
    //color: "black"
    //opacity: 0.2
    color: "transparent"

    //property bool inputFocus: false
    property var searchList
    property var searchCount

    Rectangle{
        anchors.fill: parent
        color: "black"
        opacity: 0.1
        radius: 10
    }

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
        color: "#ffffff"
        opacity: 0.8
        focus: false
        //activeFocusOnPress: inputFocus
        onFocusChanged: {
            if (focus) {
                text = ""
                console.log("search_: " + search_.color)
            } else
                text = "搜索音乐，视频，歌词，电台"
        }

        onAccepted: {
            //searchList = client.search(text)
            //searchCount = client.getSearchCount()
            search()
            middleArea.rightArea.searchSongs(searchList, searchCount)
        }
    }
}
