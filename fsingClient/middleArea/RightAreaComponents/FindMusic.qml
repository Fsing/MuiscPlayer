import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.2
import "../../songList"

Rectangle {
    id: findMusicRetangle
    property int index: 0

    Connections {
        target: mainWindow
        onLeftButtonPressed: {
            findMusicstackView.pop(findMusicPage)
        }
    }

    StackView {
        id: findMusicstackView
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: 825

        visible: true
        initialItem: findMusicPage
        Component {
            id: findMusicPage
            ScrollView {
                id: scrollView
                anchors.fill: parent
                verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                ColumnLayout {
                    Advert {
                        id: advert
                        modle: advertListmodle
                        Layout.fillWidth: true
                    }

                    GridLayout {
                        columns: 4
                        anchors.top: advert.bottom
                        anchors.left: advert.left
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {

                            }
                        }
                    }
                }
            }
        }
    }
}
