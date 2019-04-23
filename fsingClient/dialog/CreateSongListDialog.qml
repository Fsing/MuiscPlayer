import QtQuick 2.2
import QtQuick.Controls 2.1
import "common"
import "../middleArea/RightAreaJS.js" as Js

CommonDialog {
    id: createSongListDialog

    signal inputAccepted
    property string inputText: ""

    width: 300
    height: 300
    contentItem: CreateSongListDialogItem {
        onQuitClicked: createSongListDialog.close()
        onOkButtonClicked: {

        }
    }

    function getCurDate() {
        var d = new Date()
        var years = d.getFullYear()
        var month = add_zero(d.getMonth() + 1)
        var days = add_zero(d.getDate())

        var ndate = years + "-" + month + "-" + days
        return ndate
    }

    function add_zero(temp) {
        if (temp < 10)
            return "0" + temp
        else
            return temp
    }
}
