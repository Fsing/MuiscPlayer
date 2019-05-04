import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.6
import "topArea"
import "middleArea"
import "bottomArea"
import "element"

import FSingClient 1.0
import RtspClient 1.0
import LocalPlay 1.0

Window {
    id:mainWindow
    visible: true

    minimumWidth: 1025
    minimumHeight: 670

    flags: Qt.Window | Qt.FramelessWindowHint

    property alias client: client

    TopArea {
        id: topArea
    }

    MiddleArea {
        id: middleArea
        anchors.top: topArea.bottom
        width: parent.width
        height: parent.height - topArea.height - bottomArea.height
    }

    BottomArea{
        id:bottomArea
        controlButtonColor: topArea.color
        sliderColor: topArea.color
    }

    MediaPlayer {
        id: mediaPlayer
        autoPlay: true
        volume: 0.5
        playlist: currentPlaylist
    }

    Playlist {
        id: currentPlaylist
    }
    CurrentPlayList {
        id: currentListRectangle
    }

    FSingClient{
        id: client
    }

    RtspClient{
        id:rtspClient
    }

    LocalPlay{
        id:localPlay
    }
}
