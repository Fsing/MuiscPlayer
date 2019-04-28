import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

TabBar
{
    id: bar
    currentIndex: 0
    height: 30
    y:20
    spacing: 10
    background: Rectangle{
        color: "transparent"
    }

    property string lineColor:"transparent"
    property int buttonWidth: 100
    property alias myModel:repeater.model
    property int lastIndex: 0
    property string hoverColor: "#f5f5f7"
    property string normalColor: "#ffffff"
    //property string clickColor: "#a82828"
    property string clickColor: topArea.color
    property string textNormalColor: "black"
    property string textClickColor: "white"
    property string textHoverColor: "black"

    Repeater {
        id: repeater
        model: myModel

        TabButton {
            id:barButton
            height: bar.height

            width: buttonWidth
            property alias groundColor: gColor.color
            property alias textColor: texts.color

            background:Rectangle{
                id: gColor
                color: bar.currentIndex === model.index ? clickColor : normalColor
                Rectangle{
                    visible: bar.currentIndex === model.index ? true : false
                    anchors.bottom: gColor.bottom
                    width: gColor.width
                    height: 2
                    color: lineColor
                }
            }

            contentItem:
                Text {
                    id: texts
                    //anchors.centerIn: barButton
                    color: bar.currentIndex === model.index ? textClickColor : textNormalColor
                    horizontalAlignment: Text.AlignHCenter//(1)
                    verticalAlignment: Text.AlignVCenter
                    text: modelData

                }

            //}
            onHoveredChanged: {
                if (model.index !== bar.currentIndex){
//                    console.log("hover" + model.index)
//                    console.log(hovered)
                   if(hovered){

                       repeater.itemAt(model.index).groundColor = hoverColor
                       repeater.itemAt(model.index).textColor = textHoverColor
                   }else {

                       repeater.itemAt(model.index).groundColor = normalColor
                       repeater.itemAt(model.index).textColor = textNormalColor
                   }
                }
            }

        }
    }

    onCurrentIndexChanged: {
        //将之前选中的变为正常状态
        repeater.itemAt(bar.lastIndex).groundColor = normalColor;
        repeater.itemAt(bar.lastIndex).textColor = textNormalColor

        //设置当前选中的
        bar.lastIndex = currentIndex
        repeater.itemAt(bar.lastIndex).groundColor = clickColor;
        repeater.itemAt(bar.lastIndex).textColor = textClickColor
    }
}


