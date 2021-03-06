import QtQuick 2.0
import "./common"

CommonDialog {
    id: logoutDialog

    width: 300
    height: 300
    contentItem: LogoutDialogItem {
        onLogoutClick: {
            client.logout()
            topRightButton.fanName = "未登录"
            topRightButton.loginButtonSource = "qrc:/images/common/ac0.png"
            logoutDialog.close()
            var j = middleArea.leftArea.listmodel.count - 10
            while (j) {
                middleArea.listmodel.remove(middleArea.listmodel.count - 1)
                j--
            }
        }
    }
}
