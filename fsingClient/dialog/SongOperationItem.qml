import QtQuick 2.0
import QtQuick.Layouts 1.1
import "./common"

Rectangle {
    id: operationItem
    width: 200
    height: 243

    signal collectSongClick(var pos)

    ColumnLayout {

        ButtonItem {
            width: 180
            utext: "查看评论"
            usource: "../../images/common/user.png"
            endImageVisible: false
        }
        ButtonItem {
            width: 180
            utext: "播放"
            usource: "../../images/common/user.png"
            endImageVisible: false
        }
        ButtonItem {
            width: 180
            utext: "下一首播放"
            usource: "../../images/common/user.png"
            endImageVisible: false
        }
        ButtonItem {
            width: 180
            utext: "收藏到歌单"
            usource: "../../images/common/user.png"
            onButtonClick: {
                var pos = 3
                collectSongClick(pos)
            }
        }
        ButtonItem {
            width: 180
            utext: "分享"
            usource: "../../images/common/user.png"
        }
        ButtonItem {
            width: 180
            utext: "复制链接"
            endImageVisible: false
            usource: "../../images/common/user.png"
        }
        ButtonItem {
            width: 180
            utext: "下载"
            usource: "../../images/common/user.png"
        }
    }
}
