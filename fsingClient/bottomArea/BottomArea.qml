import QtQuick 2.0
import QtMultimedia 5.8

Rectangle {
    width: parent.width
    y: parent.height - 50
    height: 50
    color: "#F6F6F8"
    //    border.color: "#CCCCCC"
    //    border.width: 1
    //---------左下控制按钮
    BottomLeftButton {
        id: bottomLeftButton
    }
    BottomRightButton {
        id: bottomRightButton
    }
    BottomMiddleButton {
        id: bottomMiddleButton
    }
}
