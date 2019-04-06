import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.6
import "topArea"
import "middleArea"
import "bottomArea"
import "element"

import FSingClient 1.0

Window {
    id:mainWindow
    visible: true

    minimumWidth: 1025
    minimumHeight: 670

    flags: Qt.Window | Qt.FramelessWindowHint

    TopArea {
        id: topArea
    }

    MiddleArea {

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
}
