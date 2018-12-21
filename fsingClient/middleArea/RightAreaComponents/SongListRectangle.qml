import QtQuick 2.0
import "../../songList/"

Rectangle {
    anchors.fill: parent;
    property alias source: backImage.source
    property alias playQuantity: playQuantityText.text
    property string songlistId : "null"
    property alias songlistName : nameText.text


    Image {
        id: backImage
        width: 170
        height: 170
        anchors.top:parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectCrop
    }
    Text {
        id: tips
        width: 164
        height: 29
        color: "#060607"
        visible: backImage.status === Image.Null
         || backImage.status === Image.Error
        anchors.centerIn: parent
        text: qsTr("image is not avilable")
        font.bold: true
        font.pointSize: 11
        verticalAlignment: Text.AlignVCenter
        styleColor: "#ed1212"
    }
    Rectangle {
        id:playQuantityRectangle
        x: 363
        anchors.top:backImage.top
        anchors.right: backImage.right
        width:  backImage.height * 0.1
        height:backImage.width * 0.4
        anchors.rightMargin: 26
        anchors.topMargin: -25
        color: parent.color
        rotation:90
        visible:!mouseArea.containsMouse && backImage.status === Image.Ready
        gradient: Gradient {
            GradientStop{
                position: 0.0;
                color: Qt.rgba(0,0,0,0.7);

            }
            GradientStop{
                position: 1.0;
                color: Qt.rgba(0,0,0,0);
            }
        }
    }
    Text {
        id: playQuantityText
        color: "#ffffff"
        anchors.top:backImage.top
        anchors.right: backImage.right
        anchors.rightMargin: 5
        text: qsTr("100")
        font.bold: true
        font.pointSize: 14
        visible:!mouseArea.containsMouse && backImage.status === Image.Ready
    }
    MouseArea {
        id:mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            if(songlistId != "null"){
            client.songList(songlistId)
            clickedSongList(songlistId)
            appendSong(songlistId)
            }
        }
    }
    Image {
        id: playImage
        width: 30
        height: 30
        visible: mouseArea.containsMouse && backImage.status === Image.Ready
        anchors.bottom: backImage.bottom
        anchors.right: backImage.right
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        source: "../../images/middleArea/play.png"
    }
    Text {
        id: nameText
        color: "black"
        anchors.top:backImage.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        font.pointSize: 10
        visible:true
        smooth:true        //是平滑
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
    }
}
