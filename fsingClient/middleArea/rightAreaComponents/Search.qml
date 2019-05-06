import QtQuick 2.0
import "../../element"

Item {
    anchors.fill: parent
    ListSongs{
        anchors.fill: parent
        height: searchModel.count * 28 +30
        _songListModel_:searchModel
    }

}
