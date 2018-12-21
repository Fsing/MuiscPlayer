import QtQuick 2.0
import QtQuick.Controls 2.0
import "../../songList/element"

Rectangle {
    width: 300
    height: 100

    //    property string loginButtonSource: "qrc:/images/common/ac0.png"
    //    property alias useName: username.text
    //    property int songlistdNumber:0
    //    property int fansNumber:0

    Row{
        anchors.fill: parent
        spacing: 10
        Button{
            width:80
            height: 80
            anchors.verticalCenter: parent.verticalCenter
            background: CircleIcon {
                id: loginbuttonImage
                anchors.fill: parent
                opacity: 1
                userImage: loginButtonSource  //1
            }
        }
        //        Column{
        //            anchors.verticalCenter: parent.verticalCenter
        //            spacing: 10
        Text{
            id:username
            text:usernametext
            anchors.verticalCenter: parent.verticalCenter
        }
        //            Text {
        //                id: songlist
        //                text:"歌单： " + songlistNumber  //2
        //            }
        //            Text {
        //                id: fan
        //                text:"粉丝： " + fansNumber    //3
        //            }
        //        }
    }
}
