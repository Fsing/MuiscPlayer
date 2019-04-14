
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

        }
        onRegisterClicked: {

        }
    }
}
