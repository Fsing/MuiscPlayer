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

    property int current: 0
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
                                    onClicked: rec0.current = index
                                }
                            }

                            currentIndex: rec0.current
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
            }
        }

    }

    Connections{
        target: leftArea
        onShowComment:{
//            if (leftArea.comments.length !== 0){
//                console.log("show Commnet!!!!")
//                for (var i = 0; i < leftArea.comments.length/3; i++){
//                    commentModel_.append({image:"file:///root/new7/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/zhenhy.jpg",
//                                             name: leftArea.comments[i*3],
//                                             comment: leftArea.comments[i*3+1]})
//                }
//            }
//            console.log("_commnets.height: " + _commnets.height)
        }
    }

    ListModel{
        id:commentModel_
//        ListElement{

//            image:"file:///root/new7/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/zhenhy.jpg"
//            name:"Eva: "
//            comment:"叶凡：“尝尽人间绚烂，难补一生辛酸遗憾”"

//        }
//        ListElement{

//            image:"file:///root/new7/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/zhenhy.jpg"
//            name:"Eva: "
//            comment:"叶凡：“尝尽人间绚烂，难补一生辛酸遗憾”"

//        }
//        ListElement{

//            image:"file:///root/new7/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/zhenhy.jpg"
//            name:"Eva: "
//            comment:"叶凡：“尝尽人间绚烂，难补一生辛酸遗憾”"

//        }
//        ListElement{

//            image:"file:///root/new7/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/zhenhy.jpg"
//            name:"Eva: "
//            comment:"叶凡：“尝尽人间绚烂，难补一生辛酸遗憾”"

//        }

    }
}
