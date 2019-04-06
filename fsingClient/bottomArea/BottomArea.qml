import QtQuick 2.0
import QtMultimedia 5.8

Rectangle {
    width: parent.width
    y: parent.height - 50
    height: 50
    color: "#F6F6F8"

    property string controlButtonColor: ""
    property string sliderColor: ""
    //    border.color: "#CCCCCC"
    //    border.width: 1
    //---------左下控制按钮
    BottomLeftButton {
        id: bottomLeftButton
        buttonColor: controlButtonColor
    }
    BottomRightButton {
        id: bottomRightButton
        slidercolor: sliderColor
    }
    BottomMiddleButton {
        id: bottomMiddleButton
        slidercolor: sliderColor
    }
}
