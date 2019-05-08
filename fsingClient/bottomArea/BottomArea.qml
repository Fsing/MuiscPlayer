import QtQuick 2.0
import QtMultimedia 5.8

Rectangle {
    width: parent.width
    y: parent.height - 50
    height: 50
    color: "#F6F6F8"

    property string controlButtonColor: ""
    property string sliderColor: ""
    property alias duration : bottomMiddleButton.duration
    property alias playingSongName: bottomLeftButton.playingSongName

    property alias leftonlieVisible: bottomLeftButton.visible
//    property alias leftLocalVisible: bottomLeftButtonLocal.visible
//    property alias middleLocalVisible: bottomMiddleButtonLocal.visible
//    property alias middleonlineVisible: bottomMiddleButton.visible

//    property alias isPlaying: bottomLeftButton.isPlaying


    //    border.color: "#CCCCCC"
    //    border.width: 1
    //---------左下控制按钮
    BottomLeftButton {
        id: bottomLeftButton
        buttonColor: controlButtonColor
    }
//    BottomLeftButtonLocal{
//        id:bottomLeftButtonLocal
//        buttonColor: controlButtonColor
//        visible: false
//    }

    BottomRightButton {
        id: bottomRightButton
        slidercolor: sliderColor
    }
    BottomMiddleButton {
        id: bottomMiddleButton
        slidercolor: sliderColor
    }
//    BottomMiddleButtonLocal{
//        id:bottomMiddleButtonLocal
//        slidercolor: sliderColor
//        visible: false
//    }
}
