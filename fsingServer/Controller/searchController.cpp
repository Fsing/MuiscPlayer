#include "searchController.h"

SearchController::SearchController()
{
}
string SearchController::search(string songKey)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,nullptr,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return "FAILD";
    }

    char sql[512];
    memset(sql,0,sizeof(char)*512);
    auto key = songKey.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from Song WHERE name like '%%%s%%' or singer like '%%%s%%'",key,key);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Song failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            Json::Value root;
            Json::Value arrayObj;
            root["type"] = "SEARCH";

            while((row = mysql_fetch_row(result))){
                //                m_userNameFlag = true;
                Json::Value item;

                item["id"] = row[0];
                item["type"] = "SONGINFO";
                item["name"] = row[1];
                item["source"] = row[2];
                item["singer"] = row[3];
                item["album"] = row[4];
                item["playQuantity"] = row[5];
                item["shareQuantity"] = row[6];
                item["downloadQuantity"] = row[7];
                arrayObj.append(item);
            }
            root["array"] = arrayObj;

            root.toStyledString();
            std::string out = root.toStyledString();
            return out.data();
        }
    }
    return "null infomation";
}
