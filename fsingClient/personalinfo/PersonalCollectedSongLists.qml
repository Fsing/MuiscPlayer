import QtQuick 2.0
import "../middleArea/RightAreaComponents"
import QtQuick.Layouts 1.2

Rectangle {
    border.color: "#CCCCCC"

    property alias songlistModel: songlistModel

    Grid{
        columns: 4
        anchors{
            top:parent.top
            topMargin: 20
            left: parent.left
            leftMargin:5
        }
        Repeater{
            model:songlistModel
            delegate:
                Rectangle {
                Layout.fillWidth: true
                width: 200
                height: 200
                border.color: "#CCCCCC"
                SongListRectangle {
                    playQuantity: playquantity
                    source: imageSource
                    songlistId: songlistid
                    songlistName: songlistname
                }
            }
        }
    }

    ListModel{
        id:songlistModel
    }
}
