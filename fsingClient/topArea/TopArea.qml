import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0
import "../dialog"

Rectangle {
    id: topArea
    width: parent.width
    height: 50
    //color: "#C62F2F"
    //color: "#a82828"
    color: "lightgreen"
    radius: 0
    border.width: 0

    property var backStackView:[0]
    property var forwardStackView:[]
    property double xPosition: 0.0
    property double yPosition: 0.0

    property int titleFontSize: 20
    property string titleColor: "#ffffff"

    property alias loginDialog: loginDialog
    property alias topSearch_: topSearch
    property alias backAndForwardButton: leftRightButton

    signal back()
    signal forward()

    Text {
        id: titleName
        x:14
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("FSing 音乐")
        font.pixelSize: titleFontSize
        color: titleColor

    }
    //---------------前进后退按钮组件
    LeftRightButton {
        id: leftRightButton
        width: 52
        height: 21
        radius: 3


    }
    //----------------搜索组件
    TopSearch {
        id: topSearch
        anchors.left: leftRightButton.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    //-----------------右上角功能组件
    TopRightButton {
        id: topRightButton
        //loginButtonSource:

        onLoginButtonClicked: {
            console.log("client.checkLogin():  "+ client.checkLogin())
                if (!client.checkLogin()){
                    loginDialog.open()
                } else {
                    logoutDialog.y = topRightButton.height
                    logoutDialog.x = (mainWindow.width - topRightButton.width - logoutDialog.width / 2)
                    if (logoutDialog.opened)
                        logoutDialog.close()
                    else
                        logoutDialog.open()
                }
        }
        onSkinButtonClicked: {
            colorDialog.open()
        }
    }

    LoginDialog{
        id:loginDialog
        //x: mainWindow.width / 2 - 150
        y: 100
    }

    LogoutDialog {
        id: logoutDialog
    }

    ColorDialog {
        id: colorDialog
        currentColor: topArea.color
        onAccepted: {
            topArea.color = currentColor
            console.log("You chose: " + colorDialog.color)
                      //Qt.quit()
        }
        onRejected: {
                  console.log("Canceled")
                  //Qt.quit()
              }
    }

    //-----------------------------
    MouseArea {
        //top栏拖动
        x: 0 //parent.left
        width: 190
        height: parent.height
        hoverEnabled: false
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            mainWindow.setX(mainWindow.x + delta.x)
            mainWindow.setY(mainWindow.y + delta.y)
            xPosition = mainWindow.x + delta.x
            yPosition = mainWindow.y + delta.y
        }
    }
    MouseArea {
        //搜索栏和设置按钮中间区域的拖动栏
        anchors.left: topSearch.right
        anchors.right: topRightButton.left
        height: parent.height
        hoverEnabled: false
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
            //topSearch.inputFocus = false
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            mainWindow.setX(mainWindow.x + delta.x)
            xPosition = mainWindow.x + delta.x
            mainWindow.setY(mainWindow.y + delta.y)
            yPosition = mainWindow.y + delta.y
        }
    }

    MouseArea {
        //top栏右侧 可拖动窗口大小
        width: 5
        height: parent.height
        x: parent.width - 5
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            if (mainWindow.width + delta.x <= 1025) {

            } else {
                mainWindow.setWidth(mainWindow.width + delta.x)
            }
        }
    }

//    onBackStackViewChange: {
//        console.log("onBackStackViewChanged")
//        if (backStackView.length === 0){
//            leftRightButton.leftButtonOpacity = 1.0
//        }else{
//            leftRightButton.leftButtonOpacity = 0.5
//        }
//    }
}
