create database Fsing;
use Fsing;
create table Song(id int not null AUTO_INCREMENT PRIMARY KEY,name char(30) not null,source char(50) not null,singer char(30) not null,album char(30) not null,playQuantity int not null,downloadQuantity int not null,shareQuantity int not null);
CREATE TABLE Account(id int not null AUTO_INCREMENT PRIMARY KEY,name char(30) not null,password char(30) not null,label char(50) not null,sex char(10) not null,birthday date not null,address char(50) not null,icon char(100) not null,isVaild bool);
create table SongList(id int not null AUTO_INCREMENT PRIMARY KEY,name char(100) not null,author char(30) not null,createTime date not null,label char(30) not null,info varchar(1000) not null,icon char(50) not null,collectionQuantity int not null,clickQuantity int not null,shareQuantity int not null);
create table FindMusicSong(id char(30) not null,name char(30) not null,source char(50) not null,singer char(30) not null,album char(30) not null ,playQuantity int not null,downloadQuantity int not null,shareQuantity int not null);
create table SongListRelation(songlistID int not null,songID int not null);

create table SongAlbumRelation(songID int not null,songAlbumID int not null);
create table SongAlbum(songAlbumID int not null AUTO_INCREMENT PRIMARY KEY,songAlbumName char(100) not null,songAlbumSource char(100) not null);

create table CollectionRelation(songlistID int not null,collectedUser char(50) not null);
create table FanRelation(userName char(50) not null,fanName char(50) not null);

insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(1,'渡口','rtsp://192.168.8.79/music/dukou.mp3','蔡琴','再爱我一次',0,0,0);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(2,'最美','rtsp://192.168.8.79/music/zuimei.mp3','羽泉','最美',10,20,30);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(3,'一路向北','rtsp://192.168.8.79/music/yiluxiangbei.mp3','周杰伦','J III MP3 Player',100,0,20);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(4,'走马','rtsp://192.168.8.79/music/zouma.mp3','不靠谱组合','不靠谱的日常',33,0,12);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(5,'搁浅','rtsp://192.168.8.79/music/geqian.mp3','周杰伦','七里香',100,0,20);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(6,'男孩','rtsp://192.168.8.79/music/nanhai.mp3','梁博','歌手 第十期',62,0,20);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(7,'奇妙能力歌','rtsp://192.168.8.79/music/qimiaonenglige.mp3','陈粒','陈粒的单曲列表',1,0,20);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(8,'曾经的你','rtsp://192.168.8.79/music/cengjingdeni.mp3','许巍','每一刻都是崭新的',34,0,20);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(9,'匆匆那年','rtsp://192.168.8.79/music/congcongnanian.mp3','王菲','匆匆那年',102,0,20);
insert into Song(id,name,source,singer,album,playQuantity,downloadQuantity,shareQuantity) values(10,'理想三旬','rtsp://192.168.8.79/music/lixiangsanxun.mp3','陈鸿宇','浓烟下的诗歌电台',110,0,20);

insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(1,'再爱我一次','zaiaiwoyici.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(2,'最美','zuimei.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(3,'J III MP3 Player','J III MP3 Player.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(4,'不靠谱的日常','bukaopuderichang.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(5,'七里香','qilixiang.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(6,'歌手 第十期','geshou dishiqi.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(7,'陈粒的单曲列表','chenlidedanquliebiao.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(8,'每一刻都是崭新的','meiyikedoushizhanxinde.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(9,'匆匆那年','congcongnanian.jpg');
insert into SongAlbum(songAlbumID,songAlbumName,songAlbumSource) values(10,'浓烟下的诗歌电台','nongyanxiadeshigediantai.jpg');


insert into SongAlbumRelation(songID,songAlbumID) values(1,1);
insert into SongAlbumRelation(songID,songAlbumID) values(2,2);
insert into SongAlbumRelation(songID,songAlbumID) values(3,3);
insert into SongAlbumRelation(songID,songAlbumID) values(4,4);
insert into SongAlbumRelation(songID,songAlbumID) values(5,5);
insert into SongAlbumRelation(songID,songAlbumID) values(6,6);
insert into SongAlbumRelation(songID,songAlbumID) values(7,7);
insert into SongAlbumRelation(songID,songAlbumID) values(8,8);
insert into SongAlbumRelation(songID,songAlbumID) values(9,9);
insert into SongAlbumRelation(songID,songAlbumID) values(10,10);


insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(1,'你的嘴角 说话的时候有浅浅的笑','鮭魚先森','2016-11-5 17:00:00','流行 华语',' 你的嘴角,说话的时候,有浅浅的笑,那道线条,像一个记号,永远都擦不掉.','1.jpg',10,20,30);
insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(2,'大海奇遇记 | 是谁的海浪打在我心上','原创君','2018-2-1 21:00:00','流行 华语 民谣',' 有谁会不喜欢大海呢？那无与伦比的配色，浩瀚辽阔的风景，深深深处的秘密……它让人感到渺小又伟大，拨弄着内心蠢蠢欲动的精灵。快来！一起领略海边的奇妙际遇~','2.jpg',77,88,99);
insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(3,'愿有光落在你身上，可爱一往如常。','不要乱来啦','2018-07-03 15:00:00','流行 韩语','  愿你是披荆斩棘的女英雄，也是被人疼爱的小朋友。','3.jpg',12,20,56);
insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(4,'《中国新说唱》入围选手作品合集','云音乐歌单之友','2018-06-28 17:00:00','说唱','中国新说唱入围Rapper全阵容正式放榜！是时候展示真正的技术了，见识一下真正的华语说唱新势力！这个夏天注定要被说唱占领！想好你要PICK哪位选手了吗？','4.jpg',55,4,0);
insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(5,'【经典】聼一首老歌，想念一段时光','Romantic丶Notes','2018-05-22 08:00:00','华语 怀旧 粤语','寂静的黄昏，总让人怀念，总是深深沦陷...那些个细数光阴在手中沉淀的日子，一去不复返...偶尔，我一个人站在黄昏的角落，代替你主持夕阳的葬礼...想着想着，痛凝重了时间，曳落了容颜...青春的羽翼...','5.jpg',77,10,0);
insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(6,'就想傻傻看着你，谁叫我喜欢你','井屿森','2018-04-26 15:00:00','流行 华语 放松','  我喜欢你的眼睛，你的睫毛，你的微笑，和你在的每个瞬间，都很奇妙','6.jpg',160,20,13);
insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(7,'【创造101】最全参赛曲目及其BGM','101','2018-04-21 18:00:00','R&B/Soul 华语 影视原声','《创造101》召集了101位偶像女团练习生，通过任务、训练、考核，让选手在明星导师训练下成长，循环人气投票、暂时淘汰的流程，最终通过人气投票选出11位女练习生，组成全新的偶像团体出道。','7.jpg',123,12,21);
insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) 
values(8,'华语电影台词对白｜念念有声','101','2018-04-01 14:00:00','影视原声','电影原声中除了收录歌曲、配乐，还会选择部分电影对白、旁白，这类台词对电影背景交代、情节推动、人物性格塑造往往有重要意义。例如《阿飞正传》中的“无脚鸟”、《倩女幽魂》里宁采臣与聂小倩的“只羡鸳鸯不羡仙”、《花样年华》中慕云、丽珍的“如果有多一张船票”。而这些淫浸了光影魅力的词句段落，如今便成了电影粉丝的心头好。','8.jpg',112,2,0);

insert into SongListRelation(songlistID,songId) values(1,1);
insert into SongListRelation(songlistID,songId) values(1,2);
insert into SongListRelation(songlistID,songId) values(1,3);
insert into SongListRelation(songlistID,songId) values(1,4);
insert into SongListRelation(songlistID,songId) values(1,5);
insert into SongListRelation(songlistID,songId) values(1,6);
insert into SongListRelation(songlistID,songId) values(1,7);
insert into SongListRelation(songlistID,songId) values(1,8);
insert into SongListRelation(songlistID,songId) values(1,9);
insert into SongListRelation(songlistID,songId) values(1,10);


insert into SongListRelation(songlistID,songId) values(2,1);

insert into SongListRelation(songlistID,songId) values(3,9);
insert into SongListRelation(songlistID,songId) values(3,8);
insert into SongListRelation(songlistID,songId) values(3,7);

insert into SongListRelation(songlistID,songId) values(4,10);
insert into SongListRelation(songlistID,songId) values(4,9);
insert into SongListRelation(songlistID,songId) values(4,8);
insert into SongListRelation(songlistID,songId) values(4,7);
insert into SongListRelation(songlistID,songId) values(4,6);
insert into SongListRelation(songlistID,songId) values(4,4);

insert into SongListRelation(songlistID,songId) values(5,6);
insert into SongListRelation(songlistID,songId) values(5,3);

insert into SongListRelation(songlistID,songId) values(6,6);

insert into SongListRelation(songlistID,songId) values(7,3);
insert into SongListRelation(songlistID,songId) values(7,6);
insert into SongListRelation(songlistID,songId) values(7,7);
insert into SongListRelation(songlistID,songId) values(8,6);
insert into SongListRelation(songlistID,songId) values(8,5);
insert into SongListRelation(songlistID,songId) values(8,4);
insert into SongListRelation(songlistID,songId) values(8,3);

INSERT INTO `Account` VALUES (100, 'huangjz', 'huangjz', 'test label 1', 'boy', '2019-04-19', 'test address code', 'huangjz.jpg', 1);
INSERT INTO `Account` VALUES (101, 'minxy', 'minxy', 'test lable 2', 'girl', '2019-04-19', 'test address', 'minxy.jpg', 1);
INSERT INTO `Account` VALUES (102, 'zhenhy', 'zhenhy', 'test lable3', 'girl', '2019-04-19', 'test address code', 'zhenhy.jpg', 1);

