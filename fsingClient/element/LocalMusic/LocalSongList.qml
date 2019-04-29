import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    width: parent.width
    height: model.count * 28 +30
    property alias model:libraryModel
    property double length: (width-50)/5

    ListModel {
        id: libraryModel
    }

    TableView {
        id:view
        anchors.fill: parent
        enabled: true
        model: libraryModel
        //model: localMusic.songList()

        horizontalScrollBarPolicy:Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy:Qt.ScrollBarAlwaysOff

        headerDelegate: Rectangle
        {
            color:"#fafafa"
            implicitWidth:200
            implicitHeight:30
            border.color:"#e1e1e2"
            border.width:1;

            Text
            {
                anchors.leftMargin: 10
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                text: styleData.value
                color: "#757575"
                //font.bold: true
                anchors.fill:parent;

            }
        }

        rowDelegate: Rectangle{
                    id:rowRectangle

                    property color rowColor: styleData.selected?"#e3e3e5":(styleData.alternate ? "#fafafa":"#f5f5f7")
                    color:itemMouse.containsMouse ? "#ecedee" : rowColor
                    height: 28
                    MouseArea{
                        id:itemMouse
                        anchors.fill: rowRectangle
                        enabled: rowRectangle.focus
                        hoverEnabled: true
                        onClicked: {

                        }
                    }
       }

        TableViewColumn {
            id:numberColumn
            role: "number"
            title: " "
            movable: false
            resizable: false
            horizontalAlignment: Text.AlignRight
            width: 50
            visible: true

        }
        TableViewColumn {
            id:titleColumn
            role: "title"
            title: "音乐标题"
            width: length
            elideMode: Text.ElideMiddle

            movable: false
        }

        TableViewColumn {
            id:artistColumn
            role: "artist"
            title: "歌手"
            width: length
            movable: false
        }
        TableViewColumn {
            id:albumColumn
            role: "album"
            title: "专辑"
            width: length
            movable: false
        }
        TableViewColumn {
            id:timeColumn
            role: "time"
            title: "时长"
            width: length
            movable: false
        }
        TableViewColumn {
            id:sizeColumn
            role: "size"
            title: "大小"
            width: length
            movable: false
            resizable: false
        }

        onClicked: {
            console.log("row clicked")
            console.log("info:    " + libraryModel.get(view.currentRow).title)
            console.log("path: " + songInfoList[row].path)
            console.log(index);
        }
        onDoubleClicked:{
            localPlay.play(songInfoList[row].path)
        }
    }
}
