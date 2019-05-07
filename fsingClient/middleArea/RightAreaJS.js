function popView(n) {
    switch (n) {
    case 0:
        var findMusic = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (findMusic === null) {
            stackView.push(findMusicComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(findMusic)
        }
        ;
        break
    case 1:
        var fm = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (fm === null) {
            stackView.push(fmComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(fm)
        }
        ;
        break
    case 2:
        var mv = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (mv === null) {
            stackView.push(mvComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(mv)
        }
        ;
        break
    case 3:
        var friend = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        console.log("friend: " + friend)
        if (friend === null) {
            stackView.push(friendComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(friend)
        }
        ;
        break
    case 4:
        var localMusic = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (localMusic === null) {
            stackView.push(localMusicComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(localMusic)
        }
        ;
        break
    case 5:
        var download = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (download === null) {
            stackView.push(downloadComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(download)
        }
        ;
        break
    case 6:
        var myMusicCloudDisk = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (myMusicCloudDisk === null) {
            stackView.push(myMusicCloudDiskComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(myMusicCloudDisk)
        }
        ;
        break
    case 7:
        var mySinger = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (mySinger === null) {
            stackView.push(mySingerComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(mySinger)
        }
        ;
        break
    case 8:
        var mymv = stackView.find(function (item) {

            return item.index === n ? true : false
        })

        console.log("mymv:*************** " + mymv)
        if (mymv === null) {
            stackView.push(myMvComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(mymv)
        }
        ;
        break
    case 9:
        var favorite = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        console.log("songlist:*************** " + favorite)
        if (favorite === null) {
            stackView.push(favoriteComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(favoriteComponent)
        }
        ;

        break

    case -1:
        var lyric = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (lyric === null) {
            stackView.push(lyricComponent)
        } else {
            stackView.pop(lyric)
        }
        ;
        break

    case -2:
        var search_ = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (search_ === null) {
            stackView.push(searchComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(search_)
        }
        ;
        break

    case -3:
        var psersonInfo = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (psersonInfo === null) {
            stackView.push(personInfoComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(psersonInfo)
        }
        ;
        break
    default:
        var songList = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        console.log("songlist:*************** " + songList)
        if (songList === null) {
            stackView.push(songListComponent)
            topArea.backStackView.push(n)
            topArea.backAndForwardButton.leftButtonOpacity = 1.0
            topArea.forwardStackView = []
            console.log("topArea.forwardStackView.count:   " +topArea.forwardStackView.length)
            console.log("topArea.backStackView.count:   " +topArea.backStackView.length)
        } else {
            stackView.pop(songListComponent)
        }
        ;
    }
}
