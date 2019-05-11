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
    property var songListCommentModel:songListCommentModel_

    ListModel{
        id:songListCommentModel_
    }

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

                onCollectClick: {
                    console.log("Collect Button Click!")
                    if (client.checkLogin()){
                        client.collectSongList(client.getUserId(), songListId_)
                        middleArea.leftArea.userSongListNamesAndIds.push(songListName_)
                        middleArea.leftArea.userSongListNamesAndIds.push(songListId_)
                        if (middleArea.leftArea.showAllCreateClicked) {
                            middleArea.listmodel.append({
                                                            recColor: "#F5F5F7",
                                                            imagesource: "../images/leftArea/list.png",
                                                            tx: songListName_,
                                                            opaci: 0.55,
                                                            classifyText: "",
                                                            delegate_listVisible: true
                                                        })
                        } else {
                            middleArea.listmodel.append({
                                                            recColor: "#F5F5F7",
                                                            imagesource: "../images/leftArea/list.png",
                                                            tx: songListName_,
                                                            opaci: 0.55,
                                                            classifyText: "",
                                                            delegate_listVisible: false
                                                        })
                        }
                    }else {
                        console.log("请登录")
                        topArea.loginDialog.open()
                    }
                }
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
