import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../element"
import "../dialog"

Rectangle {
    id: songlist
    anchors.fill: parent

    property int index
    property string userName
    property string userImage
    property string songListName
    property string songListCreateTime
    property string label
    property string briefInfo

    ScrollView {
        id: scroll
        anchors.fill: parent

        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        Column{
            //spacing: 0
            SongListTop {
                id: songListTop
                width: songlist.width
                height: 250

                username: userName
                userImg: userImage
                listName: songListName
                createTime:songListCreateTime
                labels: label
                briefInfos:briefInfo
            }

            SongListBottom {
                id: songListBottom
                width: songlist.width
                height: 500
               //y:songListTop.y+songListTop.height
            }
        }
    }
}
