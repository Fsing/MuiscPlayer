import QtQuick 2.0
import QtQuick.Layouts 1.1
import "./common"

Rectangle {
    id: rectangle
    width: 280
    height: 200

    signal setClick
    signal logoutClick

    Column {
        ButtonItem {
            usource: "qrc:/images/common/setting.png"
            utext: "个人信息设置"
            onButtonClick: {
                setClick()
            }
        }

        Rectangle {
            id: horline
            //模拟线段
            width: rectangle.width //长
            height: 1 //高
            visible: true
            color: "#f3f2f2" //颜色
        }

        ButtonItem {
            usource: "qrc:/images/common/user.png"
            utext: "退出登录"
            onButtonClick: {
                logoutClick()
            }
        }
    }
}
