import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import "../element"

Rectangle {
//    //歌单名
//    property string listName
//    //歌单图片
//    property string listImage
//    //用户图片
//    property string userImg
//    //创建者
//    property string username
//    //创建时间
//    property string createTime
//    //标签
//    property string labels
//    //歌单简介
//    property string briefInfos

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
            iconSource: songListImage_
        }
        ColumnLayout {
            spacing: 15
            RowLayout {
                Rectangle{
                    width: label.width+10
                    height: label.height
                    radius: 2
                    color: topArea.color
                    Label {
                        id:label
                        text: "歌单"
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
                Text {
                    text: songListName_
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
                    userImage: userImage_

                }

                Text {
                    text: userName_
                    MouseArea {
                        anchors.fill: parent
                        onClicked: userClick()
                    }
                }

                Text {
                    text: songListCreateTime_
                }
            }

            RowLayout {
                spacing: 10
                PlayAllButton {
                    id: addtoPlayListBtn
                    onPlayAllClick: {
                        console.log("songlist.songListModel.count: " + songlist.songListModel.count)
                        if (songlist.songListModel.count !== 0){
                            currentListRectangle.playListModel.clear()
                            var i = 0
                            for (; i < songlist.songListModel.count; i++){
                                currentListRectangle.playListModel.append({"title":songlist.songListModel.get(i).title,"artist":songlist.songListModel.get(i).artist, "time":songlist.songListModel.get(i).time})
                                //currentPlaylist.addItem(songlist.songListModel.get(i).path)
                            }
                            currentListRectangle.songNumber = currentListRectangle.playListModel.count
                            currentListRectangle.listView.height = currentListRectangle.playListModel.count * 30
                            currentListRectangle.noSongsView.visible = false
                            currentListRectangle.listView.visible = true
                        }
                    }
                }

                IconButton {
                    id: collectButton
                    iconScale: 0.9
                    buttonText: "收藏"
                    iconSource: "qrc:/images/common/collect.png"
                    onIconButtonClicked: collectClick()
                }

                IconButton {
                    id: shareButton
                    buttonText: "分享"
                    iconScale: 0.6
                    iconSource:"qrc:/images/common/share.png"
                    onIconButtonClicked: shareClick()
                }

                IconButton {
                    id: downloadButton
                    iconScale: 0.8
                    buttonText: "下载全部"
                    iconSource: "qrc:/images/leftArea/btndownload.png"
                    //onIconButtonClicked: downloadClick()
                }
            }

            RowLayout {
                Label {
                    text: "标签: "
                }
                Text {
                    text:label_
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


