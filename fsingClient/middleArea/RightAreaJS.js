function popView(n) {
    switch (n) {
    case 0:
        var findMusic = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (findMusic === null) {
            stackView.push(findMusicComponent)
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
        } else {
            stackView.pop(mv)
        }
        ;
        break
    case 3:
        var friend = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (friend === null) {
            stackView.push(friendComponent)
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
        } else {
            stackView.pop(mySinger)
        }
        ;
        break
    case 8:
        var mymv = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (mymv === null) {
            stackView.push(myMvComponent)
        } else {
            stackView.pop(mymv)
        }
        ;
        break
        //    case 9:
        //        //        var search = stackView.find(function (item) {

        //        //            return item.index === n ? true : false
        //        //        })
        //        //        if (search === null) {
        //        //            stackView.push(searchComponent)
        //        //        } else {
        //        //            stackView.pop(search)
        //        //        }
        //        //        ;
        //        //        break
        //        var songlist = stackView.find(function (item) {

        //            return item.index === n ? true : false
        //        })
        //        if (songlist === null) {
        //            stackView.push(favoriteComponent)
        //        } else {
        //            stackView.pop(favoriteComponent)
        //        }
        //        ;

        //        break
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
    default:

        var songlist = stackView.find(function (item) {

            return item.index === n ? true : false
        })
        if (songlist === null) {
            stackView.push(mySongListComponent)
        } else {
            stackView.pop(songlist)
        }
        ;

        break
    }
}
