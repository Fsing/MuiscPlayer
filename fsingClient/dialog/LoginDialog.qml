
import QtQuick 2.0
import QtQuick.Controls 2.1
import "./common"

CommonDialog {
    id: loginDialog
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
            mainWindow.client.myLogin(loginUserNameText, loginUserPasswordText)
            setRemindMessage(client.result)
            console.log(client.result)
            if (client.logining) {
                console.log(middleArea.leftArea.listmodel.count)
                var j = middleArea.leftArea.listmodel.count - 10
                while (j) {
                    middleArea.listmodel.remove(middleArea.listmodel.count - 1)
                    j--
                }
                console.log(middleArea.leftArea.listmodel.count)

                topRightButton.loginButtonSource = "file:///" + applicationDirPath + "/" + client.userIcon
                middleArea.personal.userIcon = "file:///" + applicationDirPath + "/" + client.userIcon
                topRightButton.fanName = client.userName
                var i = 0
                //                console.log(client.createdSongLists()[i])
                while (client.createdSongLists()[i]) {
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

                    i++
                }
                //用户信息界面插入原创歌单信息
                i = 0;
                while (client.createdSongLists()[i]) {
                    middleArea.personal.songlistModel.append({
                                                                 playquantity:50,
                                                                 imageSource:"file:///" + applicationDirPath + "/" + client.userIcon,
                                                                 songlistid:50,
                                                                 songlistname:client.createdSongLists()[i]
                                                             })
                    i++
                }
                //用户信息界面插入收藏歌单信息
                i = 0;
                while (client.collectedSongLists()[i]) {
                    middleArea.personal.songlistModel1.append({
                                                                  playquantity:50,
                                                                  imageSource:"file:///" + applicationDirPath + "/" + client.userIcon,
                                                                  songlistid:10,
                                                                  songlistname:client.collectedSongLists()[i]
                                                              })
                    i++
                }

                //用户信息界面插入关注用户信息
                i = 0
                while(client.attentedUsers()[i]){
                    middleArea.attentedUserModel.append({
                                                            usernametext:client.attentedUsers()[i],
                                                            loginButtonSource:"file:///" + applicationDirPath + "/" + client.attentedUsers()[++i],
                                                        })
                    i++;
                }

                //用户信息界面插入粉丝用户信息
                i=0
                while(client.fanUsers()[i]){
                    middleArea.attentedUserModel.append({
                                                            usernametext:client.fanUsers()[i],
                                                            loginButtonSource:"file:///" + applicationDirPath + "/" + client.fanUsers()[++i],
                                                        })
                    i++;
                }
            }
        }
        onRegisterClicked: {
            mainWindow.client.myRegister(registerUserNameText,
                                         registerUserPasswordText)
            setRemindMessage(client.result)
            console.log(client.result)
        }
    }
}
