import QtQuick 2.0

Item {
    //    width: parent.width - 10
    //    height: classify.visible ? 60 : 35


    //main里面的什么都没改，就是去掉了长宽
    property alias classfify: classify
    //左侧字的颜色
    property string leftElementTextColor: "#333333"
    property double leftElementTextSize: 12.5

    signal itemClicked(int index)
    signal createClicked()

    Text {
        id: classify
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 10
        }

        text: classifyText
        width: parent.width
        //        height: 15
        font.pixelSize: leftElementTextSize
        color: leftElementTextColor
        opacity: 0.55
        visible: classifyVisible
        z: 2
    }
    Image {
        id: create
        width: 17
        height: 17
        opacity: 0.8
        source: "../images/leftArea/creatSongList.png"
        anchors {
            right: showAllCreate.left
            rightMargin: 5
            top: parent.top
            topMargin: 9
        }
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            hoverEnabled: true
            propagateComposedEvents: true
            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
            enabled: true
            onEntered: {
                create.opacity = 1
            }
            onExited: {
                create.opacity = 0.8
            }
            onClicked: {
                createClicked()
                showAllCreate.rotation = 90
                rec_parent.showAllCreateClicked = true
            }
        }

        visible: showAllCreateVisible
    }
    Image {
        id: showAllCreate
        width: 17
        height: 17
        opacity: 0.8
        source: "../images/leftArea/showAllCreatedSongList.png"
        anchors {
            right: parent.right
            rightMargin: 5
            top: parent.top
            topMargin: 9
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            hoverEnabled: true
            propagateComposedEvents: true
            enabled: true
            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
            onEntered: {
                showAllCreate.opacity = 1
            }
            onExited: {
                showAllCreate.opacity = 0.8
            }
            onClicked: {
                if (!rec_parent.showAllCreateClicked) {
                    showAllCreate.rotation = 90
                    rec_parent.showAllCreateClicked = true
                } else {
                    showAllCreate.rotation = 0
                    rec_parent.showAllCreateClicked = false
                }
            }
        }

        visible: showAllCreateVisible
    }
    Rectangle {
        id: delegate_list
        width: parent.width //rec_parent.width - 30
        height: 40
        color: recColor
        visible: delegate_listVisible

        anchors.left: parent.left
        anchors.top: classify.visible ? classify.bottom : parent.top
        property alias image: image
        property alias text: textx

        Row {
            id: row
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            Image {
                id: image
                width: 20
                height: 20
                source: imagesource
                opacity: opaci
            }
            Text {
                id: textx
                text: tx
                width: 150
                font.pixelSize: leftElementTextSize
                color: leftElementTextColor
                elide: Text.ElideRight
                opacity: opaci
            }
        }

        //高亮
        MouseArea {
            id: mouse_delegate

            acceptedButtons: Qt.RightButton | Qt.LeftButton
            hoverEnabled: true
            propagateComposedEvents: true
            enabled: true
            anchors.fill: parent
            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
            onEntered: {
                listModel.setProperty(index, "opaci", 1)
            }
            onExited: {
                if (delegate_list.color != "#dcdcdc")
                    listModel.setProperty(index, "opaci", 0.55)
            }
            onClicked: {

                console.log("console.log(index):   " + index)
                itemClicked(index)
                //console.log(index)
                if (rec_parent.modelindex != -1) {
                    listModel.setProperty(rec_parent.modelindex, "recColor",
                                         "transparent") //左侧条目底色
                    listModel.setProperty(rec_parent.modelindex, "opaci", 0.55)
                }

                mouse.accepted = false
                listModel.setProperty(index, "opaci", 1)
                //鼠标点击时的条目颜色
                listModel.setProperty(index, "recColor", "#DCDCDC")
                rec_parent.modelindex = index
                //middleArea.personal.visible = false
                //middleArea.allAttentions.visible = false
                //                        console.log("item click.  " + rec_parent.modelindex + "  " + index)
            }
        }
    }
}
