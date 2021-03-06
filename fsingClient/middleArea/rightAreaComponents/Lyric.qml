import QtQuick 2.5
import QtMultimedia 5.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import "../../element/Lyric"
import "../../element"

Rectangle {
    id: rec0
    //border.width: 2
    //border.color: "pink"
    color: "#b9c5ca"

    property int index: -1

    property var songSource
    property string name:leftArea.currentSongName
    property string artist:leftArea.currentSinger
    property string album:leftArea.currentAlbum
    //property var comments_:leftArea.comments

    property int current
    property int  playPosition : rtspClient.position
    property int lyricIndex : 1
    property bool increasing: true

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
            Rectangle{
                id:lyricTop_
                width: parent.width-20
                height: 450
                color: "transparent"
                Row{
                    SongIcon{
                        width: rec0.width - lyricRec.width
                        //songListIcon: "file:///root/new7/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/3.jpg"
                    }

                    Rectangle{
                        id:lyricRec
                        width: 400
                        height: 400
                        //border.width: 2
                        //border.color: "green"
                        color: "transparent"

                        Rectangle{
                            id:labelRec
                            width: lyricRec.width
                            height: 100
                            color: "transparent"
                            ColumnLayout{
                                spacing: 10
                                y:15
                                width: parent.width
                                Text{
                                    text:name
                                    color: "#282828"
                                    font.pixelSize: 25
                                    Layout.alignment: Qt.AlignHCenter
                                }

                                RowLayout{
                                    spacing: 10
                                    Layout.alignment: Qt.AlignHCenter
                                    Text{
                                        text: "专辑："
                                        color: "#5a5a5b"

                                    }
                                    Text{
                                        text:album
                                        color: "#0a4bac"
                                        opacity: albumColumn.containsMouse ? 1.0 :0.7
                                        MouseArea{
                                            id:albumColumn
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                                        }
                                    }

                                    Text{
                                        text: "歌手："
                                        color: "#5a5a5b"
                                    }
                                    Text{
                                        text:artist
                                        color: "#0a4bac"
                                        opacity: artistColumn.containsMouse ? 1.0 :0.7
                                        MouseArea{
                                            id:artistColumn
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                                        }
                                    }
                                }
                            }
                        }

                        ListView {
                            id: lyricview
                            anchors.top: labelRec.bottom
                            //anchors.topMargin: 10
                            width: lyricRec.width -20
                            height: parent.height - 150

                            spacing: 10 //每个Rectangle相隔10的单位
                            displayMarginBeginning: 0
                            displayMarginEnd: 0
                            model: client.getLyric(songSource)
                            delegate: Rectangle {
                                color: Qt.rgba(0,0,0,0)
                                height: 25
                                width: parent.width
                                Text {
                                    color: if (rec0.current === index) {
                                               "#ffffff"
                                           } else {
                                               "#3d484b"
                                           }
                                    anchors.centerIn: parent
                                    text: model.modelData.text
                                    font.pixelSize: 15
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked:{
                                        rec0.current = index
                                        var lists = client.getLyric(songSource)
                                        console.log("歌词：     "+lists[index].time)
                                        console.log("index: " + index)
                                    }
                                }
                            }

                            currentIndex: rec0.current
                            /*{
                                var lists = client.getLyric(songSource)
                                console.debug("index: " + index);
                                console.debug("position: " +rtspClient.position)
                                if(lists[index+1].time === rtspClient.position){
                                    index++;
                                    return index
                                }
                            }*/

                            onCurrentIndexChanged: {
                            }
                        }

                        //歌词
                        SequentialAnimation {
                            id: lyricAnimtion
                            loops: lyricview.count - 1
                            //        running: true
                            PauseAnimation {
                                id: pausetime
                                //duration: lyricview.model[1].time
                            }
                            ScriptAction {
                                script: if (rec0.increasing) {
                                            rec0.current++
                                            if (rec0.current >= lyricview.count - 1) {
                                                rec0.increasing = !rec0.increasing
                                            }
                                        }
                            }
                        }
                    }
                }
            }
            Comment{
                id:_commnets
                x:20
                width:rec0.width - 40
                height:  commentModel_.count * 60+200
                //commentView.height: commentModel_.count * 50
                //                onHeightChanged: {
                //                    console.log("parent.height:  " + parent.height)
                //                }
                onAddCommnet: {

                    console.log("leftArea.currentSongId :   "+leftArea.currentSongId)
                    console.log("client.getUserId() :   "+client.getUserId())
                    console.log("onAddCommnet:          " + str)
                    client.postComment(leftArea.currentSongId, client.getUserId(), str)
                }
                onDeletePoint: {
                    var method = "unlike"
                    client.commentLike(leftArea.currentSongId, leftArea.comments[inx*5],method)
                }
                onAddPoint: {
                    var method = "like"
                    client.commentLike(leftArea.currentSongId, leftArea.comments[inx*5],method)
                }
            }
        }

    }

    Connections{
        target: leftArea
        onShowComment:{
            console.log("leftArea.currentSongId :onShowComment:   "+leftArea.currentSongId)
            client.comment(leftArea.currentSongId,1,10)
            leftArea.comments = client.getComments()
            console.log("client.getComments(): "+ leftArea.comments.length)

            commentModel_.clear()
            if (leftArea.comments.length !== 0){
                console.log("show Commnet!!!!")
                commentModel_.clear()
                for (var j = 0; j< leftArea.comments.length/5; j++){
                    client.fileTransfer(leftArea.comments[j*5+3])
                }

                console.log("show Commnet count: " +  leftArea.comments.length)
                for (var i = 0; i < leftArea.comments.length/5; i++){

                    var number = parseInt(leftArea.comments[i*5+4])
                    console.log("leftArea.comments[i*5+3]:  "+leftArea.comments[i*5+3])

                    var path = "file://"+applicationDirPath+"/"+leftArea.comments[i*5+3]
                    commentModel_.append({image:path,
                                             name: leftArea.comments[i*5+1],
                                             comment: leftArea.comments[i*5+2],
                                             point:number})
                }
            }
            console.log("_commnets.height: " + _commnets.height)
        }
    }

    ListModel{
        id:commentModel_
    }
}
