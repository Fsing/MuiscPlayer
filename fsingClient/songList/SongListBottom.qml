import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import "../element"

Rectangle {
    id:songListBottom
    height: bar.height + line.height + layout.height
    property var _songlistComments:[]

    MyTabBar{
        id: bar
        x: 50
        width: parent.width
        height: 30
        spacing: 10

        myModel: ["歌曲列表", "评论", "收藏者"]

        onCurrentIndexChanged: {
            if(currentIndex === 1){
                console.log("进入歌单评论")
                client.comment(songListId_,1,10)
                //var comments = client.getComments()
                songListCommentModel.clear()

                _songlistComments = client.getComments()
                console.log("_songlistComments.length: "+_songlistComments.length)
                if (_songlistComments.length !== 0){
                    console.log("show 歌单评论!!!!")
                    songListCommentModel.clear()
                    console.log("show Song List Commnet count: " +  _songlistComments.length)
                    for (var i = 0; i < _songlistComments.length/5; i++){
                        var number = parseInt(_songlistComments[i*5+4])
                        songListCommentModel.append({image:"file://"+applicationDirPath+"/"+_songlistComments[i*5+3],
                                                 name: _songlistComments[i*5+1],
                                                 comment: _songlistComments[i*5+2],
                                             point:number})
                    }
                }
            }
        }
    }

    Rectangle{
        id:line
        anchors.top: bar.bottom
        width: songListBottom.width
        height: 2
        color: topArea.color
    }

    StackLayout{
        id:layout
        anchors.top: line.bottom

        width: songListBottom.width
        height: if (currentIndex ===0 ) {
                    songListInit.visible ? (songlist.height - songListTop.height - bar.height - line.height): listSongs.height +28
                }else{
                    songlist.height - songListTop.height - bar.height - line.height
                }

        currentIndex: bar.currentIndex
        Rectangle{
            width: layout.width
            height: listSongs.height
            Text{
                id:songListInit
                //visible:listSongs.model.count === 0 ? true : false
                visible:songListModel.count === 0 ? true : false
                text: "赶快去收藏你喜欢的音乐"
                anchors.centerIn: parent
            }
            ListSongs{
                id:listSongs
                //anchors.fill:parent
                //visible:listSongs.model.count === 0 ? true : false

                visible:songListModel.count === 0 ? false : true
            }
        }

        Rectangle{
            //color: "plum"
//            Text{
//                text: "评论"
//                anchors.centerIn: parent
//            }

            Comment{
                id:songListComment
                x:20
                width: songListBottom.width - 40
                height: songListCommentModel.count * 60+200
                commentModel: songListCommentModel

                onAddCommnet: {

                    console.log("currentSongId :   "+songListId_)
                    console.log("UserId() :   "+client.getUserId())
                    console.log("onAddCommnet:          " + str)
                    client.postComment(songListId_, client.getUserId(), str)
                }

                onDeletePoint: {
                    var method = "unlike"
                    console.log("_songlistComments[index*5]: " +inx)
                    client.commentLike(songListId_, _songlistComments[inx*5],method)
                }
                onAddPoint: {
                    var method = "like"
                    console.log("_songlistComments[index*5]: " +inx)
                    client.commentLike(songListId_, _songlistComments[inx*5],method)
                }
            }

        }

        Rectangle{
            color: "teal"
            Text{
                text: "暂无收藏者"
                anchors.centerIn: parent
            }
        }
    }

}
