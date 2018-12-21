import QtQuick 2.0
import "../../songList"

Rectangle {
    property int index: 1
    color: "yellow"

    //    Text {
    //        anchors.centerIn: parent
    //        text: qsTr("FM")
    //    }
    SongList {
        id: songlist
        width: parent.width
        height: parent.height
        ListModel {
            id: listmodel
        }
        model: listmodel
        listname: "zzzz"
        listImg: "qrc:/images/logo.jpg"
        userImg: "qrc:/images/logo.jpg"
        username: "eva"
        createTime: "2018-09-01"
    }
}
