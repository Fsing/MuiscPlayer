import QtQuick 2.0
import QtMultimedia 5.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id:currentListRectangle
    color:"#F0F0F0"
    opacity: 0.8
    anchors.right: parent.right
    anchors.bottom: bottomArea.top
    visible: false
    width: 300
    height: 500
    ListView {
        id:listView
        anchors.fill: parent
        model: currentPlaylist
        delegate:Rectangle{
            height: 30
            width: parent.width
            color: currentPlaylist.currentIndex
            == index
                   ?"#BFEFFF" :currentListRectangle.color

            Text {
                text: client.getSongInformation()[1]
            }
            MouseArea {
                anchors.fill: parent
                onClicked:{
                currentPlaylist.currentIndex = index
                songChanged(currentPlaylist.currentItemSource)
                }
            }
        }
    }
}
