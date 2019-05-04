
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
                var j = middleArea.leftArea.listmodel.count - 10
                while (j) {
                    middleArea.listmodel.remove(middleArea.listmodel.count - 1)
                    j--
                }
                console.log("client.getUserName(): " + client.getUserName())
                topRightButton.fanName = client.getUserName()
                console.log("client.getUserIcon():      "+client.getUserIcon())
                topRightButton.loginButtonSource = "file://" + applicationDirPath + "/" + client.getUserIcon()
                var createSongListsCount = client.getCreateSongNameLists().length/2
                console.log("createSongListsCount； "+createSongListsCount)
                for (var i = 0; i < createSongListsCount; i++){
                    if (middleArea.leftArea.showAllCreateClicked) {
                        middleArea.listmodel.append({
                                                        recColor: "#F5F5F7",
                                                        imagesource: "../images/leftArea/list.png",
                                                        tx: client.createdSongLists(
                                                                )[i],
                                                        opaci: 0.55,
                                                        classifyText: "",
                                                        delegate_listVisible: true
                                                    })
                    } else {
                        middleArea.listmodel.append({
                                                        recColor: "#F5F5F7",
                                                        imagesource: "../images/leftArea/list.png",
                                                        tx: client.createdSongLists(
                                                                )[i],
                                                        opaci: 0.55,
                                                        classifyText: "",
                                                        delegate_listVisible: false
                                                    })
                    }
                }
            }
        }
        onRegisterClicked: {
            client.registerUser(registerUserNameText,
                                         registerUserPasswordText)
            setRemindMessage(mainWindow.client.getLoginControllerResult())
            console.log(mainWindow.client.getLoginControllerResult())
        }

    }
}
