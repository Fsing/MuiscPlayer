import QtQuick 2.0
import "common"

Rectangle {
    color: "white"

    signal userLoginClicked   //账户登录按钮
    signal userRegisterClicked  //用户注册按钮
    signal returnClicked    //返回按钮
    signal loginClicked     //输入信息后，确认登录按钮
    signal registerClicked  //输入信息后，确认注册按钮

    property alias middleItemVisibe:middleItem.visible
    property alias middleLoginItemVisible: middleLoginItem.visible
    property alias middleRegisterItemVisible: middleRegisterItem.visible
    property alias loginUserNameText: loginUserName.text
    property alias loginUserPasswordText: loginUserPassword.text
    property alias registerUserNameText: registerUserName.text
    property alias registerUserPasswordText: registerUserPassword.text
    property string remindMessageVisible
    property alias remindMessageText: remindMessage.text

    Item {
        id: header
        width: parent.width
        height: parent.height * 0.3
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        Image {
            id: close
            width: 20
            height: 20
            source: "../images/leftArea/close.png"
            anchors{
                right: parent.right
                rightMargin: 10
                top:parent.top
                topMargin: 10

            }
            MouseArea {
                anchors.fill: close
                focus: true
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    loginDialog.close()
                    middleLoginItemVisible = false
                    middleRegisterItemVisible = false
                    middleItemVisibe = true
                    remindMessageVisible = ""
                    remindMessageText = ""
                }
            }
        }
        Image {
            id: retn
            source: "../images/leftArea/showAllCreatedSongList.png"
            width: 20
            height: 20
            rotation: 180
            visible: middleItemVisibe ? false : true
            anchors{
                top:parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 10
            }
            MouseArea {
                anchors.fill: retn
                focus: true
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    returnClicked()
                }
            }
        }
        Text {
            id: remindMessage
            text:"注册成功，请返回登录"
            font.pixelSize: 10
            color: "red"
            anchors{
                bottom: parent.bottom
                bottomMargin: 20
                left: parent.left
                leftMargin: (parent.width - remindMessage.width)/2.0
            }
            visible: !middleItemVisibe && remindMessageVisible != "" ?true :false
        }

        //对话框的拖动
        MouseArea {
            anchors {
                left: parent.left
                leftMargin: 30
                bottom: parent.bottom
                top: parent.top
                right: parent.right
                rightMargin: 30
            }

            hoverEnabled: false
            acceptedButtons: Qt.LeftButton
            property point clickpos: "0,0"
            onPressed: {
                clickpos = Qt.point(mouse.x, mouse.y)
            }
            onPositionChanged: {
                var delta = Qt.point(mouse.x - clickpos.x, mouse.y - clickpos.y)
                loginDialog.x = (loginDialog.x + delta.x)
                loginDialog.y = (loginDialog.y + delta.y)
            }
        }
    }
    Item{
        id:middleItem
        width: parent.width
        height: parent.height * 0.7
        anchors{
            top:header.bottom
            left: parent.left
            right: parent.right
        }
        MyButton {
            id: login
            width: parent.width * 0.7
            height: 40
            radius: 20
            anchors {
                left: parent.left
                leftMargin: 35
                top: parent.top
            }
            text: "帐号登录"
            onButtonClicked: userLoginClicked()
        }
        MyButton {
            id: register
            width: parent.width * 0.7
            height: login.height
            radius: 20
            anchors {
                top: login.bottom
                topMargin: 20
                left: parent.left
                leftMargin: 35
            }
            text: "注册"
            onButtonClicked: userRegisterClicked()
        }
    }
    Item{
        id:middleLoginItem
        width: parent.width
        height: parent.height * 0.7
        visible: false//middleItemVisibe ? false :(middleRegisterItemVisible ? false : true)
        anchors{
            top:header.bottom
            left: parent.left
            right: parent.right
        }
        MyTextInput{
            id:loginUserName
            width: parent.width * 0.7
            height: 40
            maxTextLength: 30
            anchors{
                top:parent.top
                left: parent.left
                leftMargin: 35
            }
            remindText: loginUserName.text == "" ? "输入用户名":""
            text:middleLoginItem.visible ? loginUserName.text : ""
        }
        MyTextInput{
            id:loginUserPassword
            width: parent.width * 0.7
            height: 40
            maxTextLength: 11
            echoMode: TextInput.Password
            anchors{
                top:loginUserName.bottom
                left: parent.left
                leftMargin: 35
            }
            remindText: loginUserPassword.text == "" ? "输入密码":""
            text:middleLoginItem.visible ? loginUserPassword.text : ""
            onTextAccepted: {
                if(isInputAccept(loginUserName.text,loginUserPassword.text))
                    loginClicked()
            }
        }
        MyButton{
            id:loginButton
            width: loginUserName.width
            height: loginUserName.height
            color: "red"
            anchors{
                top:loginUserPassword.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 35
            }
            text: "登录"
            onButtonClicked:{
                if(isInputAccept(loginUserName.text,loginUserPassword.text))
                    loginClicked()
            }
        }
    }
    Item{
        id:middleRegisterItem
        width: parent.width
        height: parent.height * 0.6
        visible:false
        anchors{
            top:header.bottom
            left: parent.left
        }
        MyTextInput{
            id:registerUserName
            width: parent.width * 0.7
            height: 40
            maxTextLength: 11
            anchors{
                top:parent.top
                left: parent.left
                leftMargin: 35
            }
            remindText: registerUserName.text == "" ? "输入用户名":""
            text:middleRegisterItem.visible ? registerUserName.text : ""
        }
        MyTextInput{
            id:registerUserPassword
            width: parent.width * 0.7
            height: 40
            maxTextLength: 11
            anchors{
                top:registerUserName.bottom
                left: parent.left
                leftMargin: 35
            }
            remindText: registerUserPassword.text == "" ? "输入密码，至少6位":""
            text:middleRegisterItem.visible ? registerUserPassword.text : ""
            onTextAccepted: {
                console.log()
                if(isInputAccept(registerUserName.text,registerUserPassword.text))
                    registerClicked()
            }
        }
        MyButton{
            id:registerButton
            width: registerUserName.width
            height: registerUserName.height
            color:"red"
            anchors{
                top:registerUserPassword.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 35
            }
            text: "注册"
            onButtonClicked: {
                if(isInputAccept(registerUserName.text,registerUserPassword.text))
                    registerClicked()
            }
        }
    }
    function isInputAccept(username,userpassword)
    {
        if(username !== "" && userpassword !== "")
            return true;
        else
            return false;
    }

    function setRemindMessage(result)
    {
        if(middleRegisterItemVisible){
            remindMessageVisible = result
            if(result === "SUCCESS")
                remindMessageText = "注册成功，请返回登录"
            else
                remindMessageText = "注册失败，用户名或者密码错误"
        }
        if(middleLoginItemVisible){
            remindMessageVisible = result;
            if(result === "PW_INVALID")
                remindMessageText = "密码错误，请重新输入"
            else if(result === "NAME_INVALID")
                remindMessageText = "用户不存在"
            else if(result === "SUCCESS"){
                middleLoginItemVisible = false
                middleRegisterItemVisible = false
                middleItemVisibe = true
                remindMessageVisible = ""
                remindMessageText = ""
                topArea.loginDialog.close();
            }
        }
    }
}
