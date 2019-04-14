import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Item{
    id: allButton
    width:140
    height: 27


    signal playAllClick
    signal addClick


    IconButton{
        id:playAll
        x:1
        radius: 2
        border.width: 0
        border.color: "#00000000"
        anchors.verticalCenter: parent.verticalCenter
        iconSource: "qrc:/images/common/playAll.png"
        iconScale: 0.8
        buttonText: "播放全部"
        onClicked: {
            console.log("Play All Button clicked!")
        }
    }

    Rectangle {
        id: line
        //模拟线段
        width: 1 //长
        height: parent.height //高
        anchors.left: playAll.right
        //anchors.bottom: playAll.bottom
        visible: true
        color: "#e0e0e0" //颜色
    }
    Rectangle{
        id: addToListEnd
        width: parent.width - playAll.width - line.width -1
        height: 25
        radius: 2
        anchors.left: line.right
        anchors.verticalCenter: parent.verticalCenter
        color: addToListMouse.containsMouse ? "#f5f5f7" : "white"
        Text{
            text:"+"
            font.pixelSize: 20
            anchors.centerIn:parent
        }

        MouseArea{
            id:addToListMouse
            anchors.fill: parent
            hoverEnabled: true
        }
    }

    Rectangle {
        id: mask
        radius: 5
        anchors.fill: allButton
        border.width: 1
        border.color: "#e0e0e0"
        smooth: true
        color: "#00000000"
        visible: true
    }

    OpacityMask {
        anchors.fill: addToListEnd
        source: addToListEnd
        maskSource: mask
    }

    OpacityMask {
        anchors.fill: playAll
        source: playAll
        maskSource: mask
    }
}
