import QtQuick 2.0
import QtQuick.Layouts 1.1
import "./element"

Rectangle{

    property alias attentions: rightBaseInfo.attentions
    property alias fans: rightBaseInfo.fans
    property alias personalInfo: rightBaseInfo.personalInfo
    property alias address: rightBaseInfo.address
    property alias userName: rightBaseInfo.userName
    property alias userIcon: userIcon.source

    signal fansUserClicked
    signal attentionUserClicked

    Row{
        anchors.fill: parent
        spacing: 30
        UserIcon{
            id:userIcon
            width: 200
            height: 200
        }
        RightBaseInfo{
            id:rightBaseInfo
            width: parent.width-200-10
            height: parent.height

            onFansClicked: fansUserClicked()
            onAttentionsClicked: attentionUserClicked()
        }
    }
}
