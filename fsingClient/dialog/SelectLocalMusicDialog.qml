import QtQuick 2.2
import QtQuick.Controls 2.1
import "common"
import "../middleArea/RightAreaJS.js" as Js

CommonDialog {
    id: selectLocalMusicDialog

    signal inputAccepted
    property string inputText: ""

    width: 300
    height: 300
    contentItem: SelectLocalMusicDialogItem {
        onQuitClicked: selectLocalMusicDialog.close()
        onOkButtonClicked: {

        }
    }
}
