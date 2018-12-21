import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    property alias  modle: pathView.model
    id: advert_rec
    width: parent.width
    height: 300
    clip: true

    Timer {
        interval: 3000
        running: true
        repeat: true
        onTriggered: pathView.incrementCurrentIndex()
    }

    /*
    ListModel {
        id: model
        ListElement {
            advertImg: "qrc:/images/advert/1.jpg"
        }
        ListElement {
            advertImg: "qrc:/images/advert/2.jpg"
        }
        ListElement {
            advertImg: "qrc:images/advert/4.jpg"
        }
        ListElement {
            advertImg: "qrc:/images/advert/5.jpg"
        }
        ListElement {
            advertImg: "qrc:/images/advert/6.jpg"
        }
        ListElement {
            advertImg: "qrc:/images/advert/7.jpg"
        }
    }
    */

    Rectangle {
        width: 20
        height: 30
        color: "#dbcfcf"
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.left: parent.left
        anchors.leftMargin: 15
        Button {

            anchors.fill: parent
            MouseArea {
                id: leftButtonMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    pathView.incrementCurrentIndex()
                }
            }

            background: Image {
                id: leftButtonImage
                anchors.fill: parent
                opacity: leftButtonMouseArea.containsMouse ? 1.0 : 0.5
                source: "qrc:/images/topArea/left.png"
            }
        }
    }

    Rectangle {
        width: 20
        height: 30
        color: "#dbcfcf"
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.right: parent.right
        anchors.rightMargin: 10
        Button {

            anchors.fill: parent

            MouseArea {
                id: rightButtonMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    pathView.decrementCurrentIndex()
                }
            }
            background: Image {
                mirror: true
                anchors.fill: parent
                opacity: rightButtonMouseArea.containsMouse ? 1.0 : 0.8
                source: "qrc:/images/topArea/left.png"
            }
        }
    }

    PathView {
        id: pathView
        x: 120
        y: 50
        width: 550
        height: 300
        interactive: false
        highlightRangeMode: PathView.StrictlyEnforceRange

        model: model
        delegate: Item {
            id: delegateItem
            width: 380
            height: 180
            z: PathView.iconZ
            scale: PathView.iconScale
            opacity: PathView.iconOpacity
            Image {
                id: dlgImg
                source: advertImg
                width: delegateItem.width
                height: delegateItem.height
            }
        }
        path: Path {
            id: coverFlowPath
            startX: 50
            startY: pathView.height / 3
            PathAttribute {
                name: "iconZ"
                value: -1
            }
            PathAttribute {
                name: "iconOpacity"
                value: 0.1
            }
            PathAttribute {
                name: "iconScale"
                value: 0.8
            }

            PathLine {
                x: pathView.width * 0.5
                y: pathView.height / 3
            }
            PathAttribute {
                name: "iconZ"
                value: 1
            }
            PathAttribute {
                name: "iconOpacity"
                value: 1
            }
            PathAttribute {
                name: "iconScale"
                value: 1.0
            }

            PathLine {
                x: pathView.width
                y: pathView.height / 3
            }
            PathAttribute {
                name: "iconZ"
                value: -1
            }
            PathAttribute {
                name: "iconOpacity"
                value: 0.1
            }
            PathAttribute {
                name: "iconScale"
                value: 0.8
            }
        }
        pathItemCount: 3
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5

        focus: true
        Keys.onLeftPressed: pathView.decrementCurrentIndex()
        Keys.onRightPressed: pathView.incrementCurrentIndex()
    }
    //    Button {
    //        width: 60
    //        height: 30
    //        anchors.bottom: advert_rec.bottom
    //        anchors.bottomMargin: 10

    //        onClicked: {
    //            pathView.positionViewAtIndex(pathView.currentIndex - 2,
    //                                         PathView.Center)
    //            console.log(pathView.currentIndex)
    //        }
    //    }
}
