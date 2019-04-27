
import QtQuick 2.0
import QtQuick.Controls 2.1
import "./common"

CommonDialog {
    id: loginDialog
    x: mainWindow.width / 2 - 150
    width: 300
    height: 400

    contentItem: LoginDialogItem {
        onUserLoginClicked: {
            middleItemVisibe = false
            middleLoginItemVisible = true
            remindMessageVisible = ""
        }
        onUserRegisterClicked: {
            middleItemVisibe = false
            middleRegisterItemVisible = true
            remindMessageVisible = ""
        }
        onReturnClicked: {
            middleLoginItemVisible = false
            middleRegisterItemVisible = false
            middleItemVisibe = true
        }
        onLoginClicked: {
            console.log("点击登录按钮")
            mainWindow.client.login(loginUserNameText, loginUserPasswordText)
            console.log("result: " + mainWindow.client.getLoginControllerResult())
            client.fileTransfer(client.getUserIcon())
            setRemindMessage(mainWindow.client.getLoginControllerResult())

            console.log("client.checkLogin(): " + client.checkLogin())
            console.log("client.getUserName(): " + client.getUserName())
            console.log("applicationDirPath" + applicationDirPath)
            if(client.checkLogin()){
                console.log("client.getUserName(): " + client.getUserName())
                topRightButton.fanName = client.getUserName()
                console.log("client.getUserIcon():      "+client.getUserIcon())
                topRightButton.loginButtonSource = "file://" + applicationDirPath + "/" + client.getUserIcon()
            }
        }
        onRegisterClicked: {

        }
    }
}
