import QtQuick 2.5

Rectangle {
    border.color: "silver"
    border.width: 1
    radius: 2

    property alias remindText: hint.text  //对话框的提示信息根据text属性来判断是否显示
    property alias text: input.text
    property alias maxTextLength: input.maximumLength
    property alias validator: input.validator
    property alias echoMode: input.echoMode

    //输入歌单名字时，有用于判断输入是否结束,也可以按下enter键时
    signal textAccepted

    Text{
        id:hint
        anchors.fill: parent
        anchors{
            top:parent.top
            topMargin: parent.height * 0.2
            left: parent.left
            leftMargin: 10
        }
        color: "#666666"
    }

    TextInput {
        id: input
        focus: true
        width: parent.width - 15
        height: parent.height
        clip: true
        anchors{
            top:parent.top
            topMargin: parent.height * 0.2
            left: parent.left
            leftMargin: 10
        }

        color: "#666666"
        selectByMouse: true
        mouseSelectionMode: TextInput.SelectWords
//        onTextEdited: remindText = ""//textEditing()
        onAccepted: textAccepted()
    }
}
