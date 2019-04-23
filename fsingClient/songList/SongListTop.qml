import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import "../element"

Rectangle {
    //歌单名
    property string listName
    //歌单图片
    property string listImage
    //用户图片
    property string userImg
    //创建者
    property string username
    //创建时间
    property string createTime
    //标签
    property string labels
    //歌单简介
    property string briefInfos

    signal userClick
    signal collectClick
    signal shareClick
    signal downloadClick
    signal editClick

//    border.width: 2
//    border.color: "blue"

    RowLayout {
        x: 50
        y:30
        spacing: 30
        RecIcon {
            id: icon
        }
        ColumnLayout {
            spacing: 15
            RowLayout {
                Rectangle{
                    width: label.width+10
                    height: label.height
                    radius: 2
                    color: "#C62F2F"
                    Label {
                        id:label
                        text: "歌单"
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
                Text {
                    text: listName
                    font.pixelSize: 20
                }
                Button {
                    id: editbutton
                    MouseArea {
                        id: editbuttonMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: editClick()
                    }

                    background: Image {
                        id: editbuttonImage
                        anchors.fill: parent
                        opacity: 1
                        source: "qrc:/images/leftArea/list.png"
                    }
                }
            }

            RowLayout {
                spacing: 10
                CircleIcon {
                    userImage: "qrc:/images/logo.jpg"

                }

                Text {
                    text: username
                    MouseArea {
                        anchors.fill: parent
                        onClicked: userClick()
                    }
                }

                Text {
                    text: createTime
                }
            }

            RowLayout {
                spacing: 10
                PlayAllButton {
                    id: addtoPlayListBtn
                }

                IconButton {
                    id: collectButton
                    iconScale: 0.8
                    buttonText: "收藏"
                    onClicked: collectClick()
                }

                IconButton {
                    id: shareButton
                    buttonText: "分享"
                    iconScale: 0.8
                    onClicked: shareClick()
                }

                IconButton {
                    id: downloadButton
                    iconScale: 0.8
                    buttonText: "下载全部"
                    iconSource: "qrc:/images/leftArea/btndownload.png"
                    //onClicked: downloadClick()
                }
            }

            RowLayout {
                Label {
                    text: "标签: "
                }
                Text {
                    text:labels
                }
            }

            RowLayout {
                Label {
                    text: "简介: "
                }
                Text {
                }
            }
        }
    }

//    Text {
//        x: 365
//        y: 204
//        width: 420
//        //text:briefInfo
//        height: 75
//        wrapMode: Text.Wrap
//        smooth:true        //是平滑
//        elide: Text.ElideRight

//    }

}


