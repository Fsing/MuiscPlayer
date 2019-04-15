#ifndef MACRO_H
#define MACRO_H

#define PW_INVALID              "p"  //密码错误
#define NAME_INVALID            "n"  //用户名错误,用户不存在
#define USER_EXIST              "e"  //用户已经存在
#define SUCCESS                 "s"  //请求事务执行成功成功
#define FAILD                   "f"  //请求事务执行成功失败

#define LOGIN                   "1"  //请求登录
#define REGISTER                "2"  //请求注册
#define ADD_CREATESONGLIST      "3"  //创建新歌单
#define ADD_COLLECTIONSONGLIST  "4"  //添加收藏歌单
#define ADD_ATTENTION           "5"  //添加关注好友
#define DELETE_ATTENTION        "6"  //取消关注
#define ADD_BEATTENTION         "7"  //添加粉丝
#define DELETE_BEATTENTION      "8"  //减少粉丝
#define ADD_SONG                "7"  //添加歌曲（只有原创歌单才能添加歌曲）
#define SONGINFORMATION         "9"



#endif // MACRO_H
