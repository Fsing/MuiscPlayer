import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../element"
import "../dialog"

Rectangle {
    id: songlist
    anchors.fill: parent

    property int index:10
    property string songListId_
    property string userName_
    property string userImage_
    property string songListName_
    property string songListImage_
    property string songListCreateTime_
    property string label_
    property string briefInfo_

     property var songListModel

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

//                username_: userName
//                userImg: userImage
//                listName: songListName
//                createTime:songListCreateTime
//                labels: label
//                briefInfos:briefInfo
            }

            SongListBottom {
                id: songListBottom
                width: songlist.width
                //height: songlist.height - songListTop.height
               //y:songListTop.y+songListTop.height
            }
        }
    }
}
