use Fsing;
CREATE TABLE `Account`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` char(30)  NOT NULL,
  `password` char(30)  NOT NULL,
  `label` char(50)  NULL DEFAULT NULL,
  `sex` char(10)  NULL DEFAULT NULL,
  `birthday` date NULL DEFAULT NULL,
  `address` char(50)  NULL DEFAULT NULL,
  `icon` char(100)  NULL DEFAULT NULL,
  `isVaild` tinyint(1) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) AUTO_INCREMENT = 114 ;

-- ----------------------------
-- Records of Account
-- ----------------------------
INSERT INTO `Account` VALUES (100, 'huangjz', 'huangjz', 'test label 1', 'boy', '2019-04-19', 'test address code', 'huangjz.jpg', 1);
INSERT INTO `Account` VALUES (101, 'minxy', 'minxy', 'test lable 2', 'girl', '2019-04-19', 'test address', 'minxy.jpg', 1);
INSERT INTO `Account` VALUES (102, 'zhenhy', 'zhenhy', 'test lable3', 'girl', '2019-04-19', 'test address code', 'zhenhy.jpg', 1);
INSERT INTO `Account` VALUES (106, 'zhy', '123456', 'test lable3', 'sex', '2019-05-08', 'china', 'userIcon.png', NULL);
INSERT INTO `Account` VALUES (107, 'mxy', '123', 'test lable3', 'sex', '2019-05-08', 'china', 'userIcon.png', NULL);
INSERT INTO `Account` VALUES (109, 'test1', 'test1', 'label', 'sex', '2019-05-08', 'china', 'userIcon.png', NULL);
INSERT INTO `Account` VALUES (110, 'text', 'text', 'label', 'sex', '2019-05-08', 'china', 'userIcon.png', NULL);
INSERT INTO `Account` VALUES (111, 'text1', 'text1', 'label', 'sex', '2019-05-09', 'china', 'userIcon.png', NULL);
INSERT INTO `Account` VALUES (112, '', '', 'label', 'sex', '2019-05-09', 'china', 'userIcon.png', NULL);
INSERT INTO `Account` VALUES (113, '123', '123', 'label', 'sex', '2019-05-09', 'china', 'userIcon.png', NULL);

-- ----------------------------
-- Table structure for CollectionRelation
-- ----------------------------

CREATE TABLE `CollectionRelation`  (
  `songlistID` int(11) NOT NULL,
  `collectedUser` char(50)  NOT NULL
) ;

-- ----------------------------
-- Records of CollectionRelation
-- ----------------------------
INSERT INTO `CollectionRelation` VALUES (1, 'zhenhy');
INSERT INTO `CollectionRelation` VALUES (3000, 'text');
INSERT INTO `CollectionRelation` VALUES (4000, 'text');
INSERT INTO `CollectionRelation` VALUES (9000, 'text');
INSERT INTO `CollectionRelation` VALUES (7000, 'text');
INSERT INTO `CollectionRelation` VALUES (3000, 'text1');
INSERT INTO `CollectionRelation` VALUES (1000, 'text1');
INSERT INTO `CollectionRelation` VALUES (2000, 'text1');

-- ----------------------------
-- Table structure for Comment
-- ----------------------------

CREATE TABLE `Comment`  (
  `id` int(255) UNSIGNED NOT NULL AUTO_INCREMENT,
  `songId` int(255) NOT NULL,
  `accountId` int(255) NOT NULL,
  `comment` varchar(255)  NOT NULL,
  `points` int(255) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) AUTO_INCREMENT = 120 ;

-- ----------------------------
-- Records of Comment
-- ----------------------------
INSERT INTO `Comment` VALUES (101, 1, 101, '测试评论', 12345);
INSERT INTO `Comment` VALUES (102, 1, 102, '评论', 101);
INSERT INTO `Comment` VALUES (103, 1, 100, '测试', 25);
INSERT INTO `Comment` VALUES (104, 3, 102, '“尝尽人间绚烂，难补一生辛酸遗憾”', 0);
INSERT INTO `Comment` VALUES (105, 5, 102, 'fgfdgfd', 0);
INSERT INTO `Comment` VALUES (106, 7, 102, 'qimiaonenglige', 0);
INSERT INTO `Comment` VALUES (107, 3000, 106, '好听!!!!', 1);
INSERT INTO `Comment` VALUES (108, 4, 106, '个大概的', 0);
INSERT INTO `Comment` VALUES (109, 4, 107, '还听', 0);
INSERT INTO `Comment` VALUES (110, 7, 109, '真好听', 1);
INSERT INTO `Comment` VALUES (111, 4, 109, '被天使吻过的喉咙', 2);
INSERT INTO `Comment` VALUES (112, 5, 109, '好好听啊啊啊啊', 0);
INSERT INTO `Comment` VALUES (113, 10, 109, '真好听', 0);
INSERT INTO `Comment` VALUES (115, 4, 101, '刚进大学寝室的时候，发现床板上有人用记号笔画了一张请假条，请假原因是毕业', 0);
INSERT INTO `Comment` VALUES (116, 4, 102, '听歌的时候，旋律永远是第一感觉', 0);
INSERT INTO `Comment` VALUES (117, 1000, 110, '真好听！！！', 0);
INSERT INTO `Comment` VALUES (118, 4, 110, '好好听啊', 1);

-- ----------------------------
-- Table structure for FanRelation
-- ----------------------------

CREATE TABLE `FanRelation`  (
  `userName` char(50)  NOT NULL,
  `fanName` char(50)  NOT NULL
) ;

-- ----------------------------
-- Table structure for FindMusicSong
-- ----------------------------

CREATE TABLE `FindMusicSong`  (
  `id` char(30)  NOT NULL,
  `name` char(30)  NOT NULL,
  `source` char(50)  NOT NULL,
  `singer` char(30)  NOT NULL,
  `album` char(30)  NOT NULL,
  `playQuantity` int(11) NOT NULL,
  `downloadQuantity` int(11) NOT NULL,
  `shareQuantity` int(11) NOT NULL
);

-- ----------------------------
-- Table structure for Song

CREATE TABLE `Song`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` char(30)  NOT NULL,
  `source` char(50)  NOT NULL,
  `singer` char(30)  NOT NULL,
  `album` char(30)  NOT NULL,
  `playQuantity` int(11) NOT NULL,
  `downloadQuantity` int(11) NOT NULL,
  `shareQuantity` int(11) NOT NULL,
  `time` char(30)  NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
)  AUTO_INCREMENT = 21 ;

-- ----------------------------
-- Records of Song
-- ----------------------------
INSERT INTO `Song` VALUES (1, '渡口', 'rtsp://192.168.8.79/music/dukou.mp3', '蔡琴', '再爱我一次', 0, 0, 0, '03:32');
INSERT INTO `Song` VALUES (2, '最美', 'rtsp://192.168.8.79/music/zuimei.mp3', '羽泉', '最美', 10, 20, 30, '04:59');
INSERT INTO `Song` VALUES (3, '一路向北', 'rtsp://192.168.8.79/music/yiluxiangbei.mp3', '周杰伦', 'J III MP3 Player', 100, 0, 20, '04:55');
INSERT INTO `Song` VALUES (4, '走马', 'rtsp://192.168.8.79/music/zouma.mp3', '不靠谱组合', '不靠谱的日常', 33, 0, 12, '04:01');
INSERT INTO `Song` VALUES (5, '搁浅', 'rtsp://192.168.8.79/music/geqian.mp3', '周杰伦', '七里香', 100, 0, 20, '04:00');
INSERT INTO `Song` VALUES (6, '男孩', 'rtsp://192.168.8.79/music/nanhai.mp3', '梁博', '歌手 第十期', 62, 0, 20, '05:11');
INSERT INTO `Song` VALUES (7, '奇妙能力歌', 'rtsp://192.168.8.79/music/qimiaonenglige.mp3', '陈粒', '陈粒的单曲列表', 1, 0, 20, '04:13');
INSERT INTO `Song` VALUES (8, '曾经的你', 'rtsp://192.168.8.79/music/cengjingdeni.mp3', '许巍', '每一刻都是崭新的', 34, 0, 20, '04:19');
INSERT INTO `Song` VALUES (9, '匆匆那年', 'rtsp://192.168.8.79/music/congcongnanian.mp3', '王菲', '匆匆那年', 102, 0, 20, '04:01');
INSERT INTO `Song` VALUES (10, '理想三旬', 'rtsp://192.168.8.79/music/lixiangsanxun.mp3', '陈鸿宇', '浓烟下的诗歌电台', 110, 0, 20, '03:30');
INSERT INTO `Song` VALUES (11, '五颜六色的', '', 'Hush！', '17', 12, 0, 0, '04:40');
INSERT INTO `Song` VALUES (12, 'With me remix', '', 'P-MM 6.3', 'remix1', 134, 0, 34, '02:27');
INSERT INTO `Song` VALUES (13, '你只管努力 其他的交给天意', '', 'Young Xuc', '你迟到的许多年', 34, 0, 3, '02:05');
INSERT INTO `Song` VALUES (14, '太阳系', '', '草莓救星', '太阳系', 21, 0, 0, '09:01');
INSERT INTO `Song` VALUES (15, '逆流', '', '橙草', '乌鸦', 3, 0, 0, '04:36');
INSERT INTO `Song` VALUES (16, '故事与她（终极版）', '', '泪鑫', '一只傻泪鑫', 43, 0, 0, '03:23');
INSERT INTO `Song` VALUES (17, '少年', '', '彭坦', 'Easy', 31, 0, 0, '04:14');
INSERT INTO `Song` VALUES (18, '小美人鱼', '', '雀斑', '像星星一样', 6, 0, 0, '04:26');
INSERT INTO `Song` VALUES (19, '我家也有绿油精', '', '丝袜小姐', '就等故事都经过', 78, 0, 0, '06:54');
INSERT INTO `Song` VALUES (20, '过境', '', '熊宝贝', '年年', 43, 0, 0, '07:23');

-- ----------------------------
-- Table structure for SongAlbum
-- ----------------------------

CREATE TABLE `SongAlbum`  (
  `songAlbumID` int(11) NOT NULL AUTO_INCREMENT,
  `songAlbumName` char(100)  NOT NULL,
  `songAlbumSource` char(100)  NOT NULL,
  PRIMARY KEY (`songAlbumID`) USING BTREE
)AUTO_INCREMENT = 21 ;

-- ----------------------------
-- Records of SongAlbum
-- ----------------------------
INSERT INTO `SongAlbum` VALUES (1, '再爱我一次', 'zaiaiwoyici.jpg');
INSERT INTO `SongAlbum` VALUES (2, '最美', 'zuimei.jpg');
INSERT INTO `SongAlbum` VALUES (3, 'J III MP3 Player', 'J III MP3 Player.jpg');
INSERT INTO `SongAlbum` VALUES (4, '不靠谱的日常', 'bukaopuderichang.jpg');
INSERT INTO `SongAlbum` VALUES (5, '七里香', 'qilixiang.jpg');
INSERT INTO `SongAlbum` VALUES (6, '歌手 第十期', 'geshou dishiqi.jpg');
INSERT INTO `SongAlbum` VALUES (7, '陈粒的单曲列表', 'chenlidedanquliebiao.jpg');
INSERT INTO `SongAlbum` VALUES (8, '每一刻都是崭新的', 'meiyikedoushizhanxinde.jpg');
INSERT INTO `SongAlbum` VALUES (9, '匆匆那年', 'congcongnanian.jpg');
INSERT INTO `SongAlbum` VALUES (10, '浓烟下的诗歌电台', 'nongyanxiadeshigediantai.jpg');
INSERT INTO `SongAlbum` VALUES (11, '17', '17.png');
INSERT INTO `SongAlbum` VALUES (12, 'remix1', 'remix1.png');
INSERT INTO `SongAlbum` VALUES (13, '你迟到的许多年', 'nichidaodexuduonian.png');
INSERT INTO `SongAlbum` VALUES (14, '太阳系', 'taiyangxi.png');
INSERT INTO `SongAlbum` VALUES (15, '乌鸦', 'wuya.png');
INSERT INTO `SongAlbum` VALUES (16, '一只傻泪鑫', 'yizhishaleixing');
INSERT INTO `SongAlbum` VALUES (17, 'Easy', 'easy.png');
INSERT INTO `SongAlbum` VALUES (18, '像星星一样', 'xiangxingxingyiyang.png');
INSERT INTO `SongAlbum` VALUES (19, '就等故事都经过', 'jiudenggushidoujingguo.png');
INSERT INTO `SongAlbum` VALUES (20, '年年', 'niannian.png');

-- ----------------------------
-- Table structure for SongAlbumRelation
-- ----------------------------

CREATE TABLE `SongAlbumRelation`  (
  `songID` int(11) NOT NULL,
  `songAlbumID` int(11) NOT NULL
) ;

-- ----------------------------
-- Records of SongAlbumRelation
-- ----------------------------
INSERT INTO `SongAlbumRelation` VALUES (1, 1);
INSERT INTO `SongAlbumRelation` VALUES (2, 2);
INSERT INTO `SongAlbumRelation` VALUES (3, 3);
INSERT INTO `SongAlbumRelation` VALUES (4, 4);
INSERT INTO `SongAlbumRelation` VALUES (5, 5);
INSERT INTO `SongAlbumRelation` VALUES (6, 6);
INSERT INTO `SongAlbumRelation` VALUES (7, 7);
INSERT INTO `SongAlbumRelation` VALUES (8, 8);
INSERT INTO `SongAlbumRelation` VALUES (9, 9);
INSERT INTO `SongAlbumRelation` VALUES (10, 10);
INSERT INTO `SongAlbumRelation` VALUES (11, 11);
INSERT INTO `SongAlbumRelation` VALUES (12, 12);
INSERT INTO `SongAlbumRelation` VALUES (13, 13);
INSERT INTO `SongAlbumRelation` VALUES (14, 14);
INSERT INTO `SongAlbumRelation` VALUES (15, 15);
INSERT INTO `SongAlbumRelation` VALUES (16, 16);
INSERT INTO `SongAlbumRelation` VALUES (17, 0);
INSERT INTO `SongAlbumRelation` VALUES (18, 18);
INSERT INTO `SongAlbumRelation` VALUES (19, 19);
INSERT INTO `SongAlbumRelation` VALUES (20, 20);

-- ----------------------------
-- Table structure for SongList
-- ----------------------------

CREATE TABLE `SongList`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` char(100)  NOT NULL,
  `author` char(30)  NOT NULL,
  `createTime` date NOT NULL,
  `label` char(30)  NOT NULL,
  `info` varchar(1000)  NOT NULL,
  `icon` char(50)  NOT NULL,
  `collectionQuantity` int(11) NOT NULL,
  `clickQuantity` int(11) NOT NULL,
  `shareQuantity` int(11) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) AUTO_INCREMENT = 20026 ;

-- ----------------------------
-- Records of SongList
-- ----------------------------
INSERT INTO `SongList` VALUES (1000, '你的嘴角 说话的时候有浅浅的笑', '鮭魚先森', '2016-11-05', '流行 华语', ' 你的嘴角,说话的时候,有浅浅的笑,那道线条,像一个记号,永远都擦不掉.', '1.jpg', 10, 20, 30);
INSERT INTO `SongList` VALUES (2000, '大海奇遇记 | 是谁的海浪打在我心上', '原创君', '2018-02-01', '流行 华语 民谣', ' 有谁会不喜欢大海呢？那无与伦比的配色，浩瀚辽阔的风景，深深深处的秘密……它让人感到渺小又伟大，拨弄着内心蠢蠢欲动的精灵。快来！一起领略海边的奇妙际遇~', '2.jpg', 77, 88, 99);
INSERT INTO `SongList` VALUES (3000, '愿有光落在你身上，可爱一往如常。', '不要乱来啦', '2018-07-03', '流行 韩语', '  愿你是披荆斩棘的女英雄，也是被人疼爱的小朋友。', '3.jpg', 12, 20, 56);
INSERT INTO `SongList` VALUES (4000, '《中国新说唱》入围选手作品合集', '云音乐歌单之友', '2018-06-28', '说唱', '中国新说唱入围Rapper全阵容正式放榜！是时候展示真正的技术了，见识一下真正的华语说唱新势力！这个夏天注定要被说唱占领！想好你要PICK哪位选手了吗？', '4.jpg', 55, 4, 0);
INSERT INTO `SongList` VALUES (5000, '【经典】聼一首老歌，想念一段时光', 'Romantic丶Notes', '2018-05-22', '华语 怀旧 粤语', '寂静的黄昏，总让人怀念，总是深深沦陷...那些个细数光阴在手中沉淀的日子，一去不复返...偶尔，我一个人站在黄昏的角落，代替你主持夕阳的葬礼...想着想着，痛凝重了时间，曳落了容颜...青春的羽翼...', '5.jpg', 77, 10, 0);
INSERT INTO `SongList` VALUES (6000, '就想傻傻看着你，谁叫我喜欢你', '井屿森', '2018-04-26', '流行 华语 放松', '  我喜欢你的眼睛，你的睫毛，你的微笑，和你在的每个瞬间，都很奇妙', '6.jpg', 160, 20, 13);
INSERT INTO `SongList` VALUES (7000, '【创造101】最全参赛曲目及其BGM', '101', '2018-04-21', 'R&B/Soul 华语 影视原声', '《创造101》召集了101位偶像女团练习生，通过任务、训练、考核，让选手在明星导师训练下成长，循环人气投票、暂时淘汰的流程，最终通过人气投票选出11位女练习生，组成全新的偶像团体出道。', '7.jpg', 123, 12, 21);
INSERT INTO `SongList` VALUES (8000, '华语电影台词对白｜念念有声', '101', '2018-04-01', '影视原声', '电影原声中除了收录歌曲、配乐，还会选择部分电影对白、旁白，这类台词对电影背景交代、情节推动、人物性格塑造往往有重要意义。例如《阿飞正传》中的“无脚鸟”、《倩女幽魂》里宁采臣与聂小倩的“只羡鸳鸯不羡仙”、《花样年华》中慕云、丽珍的“如果有多一张船票”。而这些淫浸了光影魅力的词句段落，如今便成了电影粉丝的心头好。', '8.jpg', 112, 2, 0);
INSERT INTO `SongList` VALUES (9000, '午睡计划', '枫叶', '2019-05-02', '独立 摇滚 夜晚', '他唯独喜欢月光。月光不分颜色，只是淡淡地绘出地形的轮廓。它把大地盖得灰蒙蒙的，窒息生命达一夜之久。在这个像是用铅铸出来的世界里，除了有时像个影子落到灰蒙蒙的树林上的风以外，就没有什么在动，除了光秃秃的土地的气味就没有什么是活着，这样的世界就是他所承认的唯一的世界，因为这与他的灵魂世界相似。', '9.png', 23, 1, 3);
INSERT INTO `SongList` VALUES (10000, '虞姬、7妹、糖糖、承利、梦洛伊、兮雅、金6', '无上落雨', '2019-03-14', '摇滚 电子', '嗨爆全场的中文DJ\r\n歌曲数\r\n82  \r\n播放数\r\n39万\r\n\r\n无伤落雨\r\n2018-04-21创建\r\n播放全部\r\n收藏(5142)\r\n分享(17)\r\n下载全部\r\n标签： 摇滚 / 电子 / 华语\r\n嗨爆全场 ', '10.png', 54, 1, 0);
INSERT INTO `SongList` VALUES (11000, '华语速爆新歌', '网易云音乐', '2019-05-14', '华语 流行', '优质华语新歌，网易云音乐&台湾KKBOX联合推荐！每周二精选推荐。', '11.png', 21, 3, 32);
INSERT INTO `SongList` VALUES (12000, '优秀翻唱合集', '玉苏克', '2019-03-14', '华语 翻唱 午休', '你与明月清风一样 都是小宝藏。', '12.png', 23, 45, 6);
INSERT INTO `SongList` VALUES (13000, 'Jay', 'minxy', '2019-05-08', '0', '0', 'songListIcon.png', 0, 0, 0);
INSERT INTO `SongList` VALUES (20000, 'Eson', 'minxy', '2019-05-08', '0', '0', 'songListIcon.png', 0, 0, 0);
INSERT INTO `SongList` VALUES (20001, 'GME', 'minxy', '2019-05-08', '0', '0', 'songListIcon.png', 0, 0, 0);
INSERT INTO `SongList` VALUES (20008, 'Jay', 'mxy', '2019-05-08', '0', '0', 'songListIcon.png', 0, 0, 0);
INSERT INTO `SongList` VALUES (20009, 'Eson', 'mxy', '2019-05-08', '0', '0', 'songListIcon.png', 0, 0, 0);

-- ----------------------------
-- Table structure for SongListRelation
-- ----------------------------

CREATE TABLE `SongListRelation`  (
  `songlistID` int(11) NOT NULL,
  `songID` int(11) NOT NULL
) ;

-- ----------------------------
-- Records of SongListRelation
-- ----------------------------
INSERT INTO `SongListRelation` VALUES (1000, 1);
INSERT INTO `SongListRelation` VALUES (1000, 2);
INSERT INTO `SongListRelation` VALUES (1000, 3);
INSERT INTO `SongListRelation` VALUES (1000, 4);
INSERT INTO `SongListRelation` VALUES (1000, 5);
INSERT INTO `SongListRelation` VALUES (1000, 6);
INSERT INTO `SongListRelation` VALUES (1000, 7);
INSERT INTO `SongListRelation` VALUES (1000, 8);
INSERT INTO `SongListRelation` VALUES (1000, 9);
INSERT INTO `SongListRelation` VALUES (1000, 10);
INSERT INTO `SongListRelation` VALUES (2000, 1);
INSERT INTO `SongListRelation` VALUES (3000, 9);
INSERT INTO `SongListRelation` VALUES (3000, 8);
INSERT INTO `SongListRelation` VALUES (3000, 7);
INSERT INTO `SongListRelation` VALUES (4000, 10);
INSERT INTO `SongListRelation` VALUES (4000, 9);
INSERT INTO `SongListRelation` VALUES (4000, 8);
INSERT INTO `SongListRelation` VALUES (4000, 7);
INSERT INTO `SongListRelation` VALUES (4000, 6);
INSERT INTO `SongListRelation` VALUES (4000, 4);
INSERT INTO `SongListRelation` VALUES (5000, 6);
INSERT INTO `SongListRelation` VALUES (5000, 3);
INSERT INTO `SongListRelation` VALUES (6000, 6);
INSERT INTO `SongListRelation` VALUES (7000, 3);
INSERT INTO `SongListRelation` VALUES (7000, 6);
INSERT INTO `SongListRelation` VALUES (7000, 7);
INSERT INTO `SongListRelation` VALUES (8000, 6);
INSERT INTO `SongListRelation` VALUES (8000, 5);
INSERT INTO `SongListRelation` VALUES (8000, 4);
INSERT INTO `SongListRelation` VALUES (8000, 3);
INSERT INTO `SongListRelation` VALUES (9000, 13);
INSERT INTO `SongListRelation` VALUES (9000, 11);
INSERT INTO `SongListRelation` VALUES (9000, 12);
INSERT INTO `SongListRelation` VALUES (9000, 14);
INSERT INTO `SongListRelation` VALUES (9000, 15);
INSERT INTO `SongListRelation` VALUES (10000, 18);
INSERT INTO `SongListRelation` VALUES (10000, 16);
INSERT INTO `SongListRelation` VALUES (10000, 17);
INSERT INTO `SongListRelation` VALUES (10000, 19);
INSERT INTO `SongListRelation` VALUES (10000, 20);
INSERT INTO `SongListRelation` VALUES (11000, 1);
INSERT INTO `SongListRelation` VALUES (11000, 2);
INSERT INTO `SongListRelation` VALUES (11000, 11);
INSERT INTO `SongListRelation` VALUES (11000, 18);
INSERT INTO `SongListRelation` VALUES (11000, 20);
INSERT INTO `SongListRelation` VALUES (11000, 4);
INSERT INTO `SongListRelation` VALUES (12000, 2);
INSERT INTO `SongListRelation` VALUES (12000, 3);
INSERT INTO `SongListRelation` VALUES (12000, 7);
INSERT INTO `SongListRelation` VALUES (12000, 11);
INSERT INTO `SongListRelation` VALUES (12000, 15);
INSERT INTO `SongListRelation` VALUES (12000, 18);
INSERT INTO `SongListRelation` VALUES (13000, 7);
INSERT INTO `SongListRelation` VALUES (13000, 8);
INSERT INTO `SongListRelation` VALUES (13000, 18);
INSERT INTO `SongListRelation` VALUES (13000, 19);
INSERT INTO `SongListRelation` VALUES (13000, 20);
INSERT INTO `SongListRelation` VALUES (13000, 11);
INSERT INTO `SongListRelation` VALUES (14000, 1);
INSERT INTO `SongListRelation` VALUES (14000, 3);
INSERT INTO `SongListRelation` VALUES (14000, 5);
INSERT INTO `SongListRelation` VALUES (14000, 13);
INSERT INTO `SongListRelation` VALUES (14000, 15);
INSERT INTO `SongListRelation` VALUES (15000, 17);
INSERT INTO `SongListRelation` VALUES (15000, 16);
INSERT INTO `SongListRelation` VALUES (15000, 15);
INSERT INTO `SongListRelation` VALUES (16000, 6);
INSERT INTO `SongListRelation` VALUES (16000, 16);
INSERT INTO `SongListRelation` VALUES (16000, 12);
INSERT INTO `SongListRelation` VALUES (16000, 11);
INSERT INTO `SongListRelation` VALUES (17000, 10);
INSERT INTO `SongListRelation` VALUES (17000, 11);
INSERT INTO `SongListRelation` VALUES (17000, 12);
INSERT INTO `SongListRelation` VALUES (17000, 13);
INSERT INTO `SongListRelation` VALUES (18000, 9);
INSERT INTO `SongListRelation` VALUES (18000, 8);
INSERT INTO `SongListRelation` VALUES (18000, 7);
INSERT INTO `SongListRelation` VALUES (18000, 6);
INSERT INTO `SongListRelation` VALUES (19000, 19);
INSERT INTO `SongListRelation` VALUES (19000, 18);
INSERT INTO `SongListRelation` VALUES (19000, 17);
INSERT INTO `SongListRelation` VALUES (19000, 16);
INSERT INTO `SongListRelation` VALUES (20000, 1);
INSERT INTO `SongListRelation` VALUES (20000, 9);
INSERT INTO `SongListRelation` VALUES (20000, 12);
INSERT INTO `SongListRelation` VALUES (20000, 19);

