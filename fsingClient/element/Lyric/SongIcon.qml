import QtQuick 2.0
import QtQuick.Layouts 1.11
import "../../element"

Item {
    height: 450
    property alias songListIcon: songListIcon_.userImage
    ColumnLayout{
        width: parent.width
        y:50
        spacing: 35
        CircleIcon{
            //anchors.centerIn: parent
            width: 300
            height: 300
            userImage: "qrc:/images/common/azl.png"
            Layout.alignment: Qt.AlignHCenter
            CircleIcon{
                id:songListIcon_
                width: 200
                height: 200
                anchors.centerIn: parent
            }
        }
        Row{
            Layout.alignment: Qt.AlignHCenter
            spacing: 10
            IconButton{
                width: 80
                iconSource: "qrc:/images/leftArea/favorite.png"
                iconScale: 0.6
                buttonText: "喜欢"
            }
            IconButton{
                width: 80
                iconSource: "qrc:/images/common/collect.png"
                iconScale: 0.9
                buttonText: "收藏"
            }
            IconButton{
                width: 80
                iconSource: "qrc:/images/leftArea/btndownload.png"
                iconScale:0.8
                buttonText: "下载"
            }
            IconButton{
                width: 80
                iconSource: "qrc:/images/common/share.png"
                iconScale: 0.6
                buttonText: "分享"
            }
        }
    }
}
