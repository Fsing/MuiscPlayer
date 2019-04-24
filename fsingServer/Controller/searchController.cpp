#include "searchController.h"

SearchController::SearchController()
{
}
string SearchController::search(string songKey)
{
    MYSQL mysql;
    mysql_init(&mysql);
    Json::Value root;
    root["type"] = "SEARCH";
    try {
        if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,nullptr,0)){
            throw "findUser conect MYSQL failed!" ;
        }

        char sql[512];
        memset(sql,0,sizeof(char)*512);
        auto key = songKey.data();
        //    auto pw = password.data();
        std::sprintf(sql,"select * from Song WHERE name like '%%%s%%' or singer like '%%%s%%'",key,key);
        size_t length =strlen(sql);
        int res = mysql_real_query(&mysql,sql,length);
        if(res != 0){
            throw "fondUser select * from Song failed" ;
        }else{
            MYSQL_RES *result;
            MYSQL_ROW row;
            //    MYSQL_FIELD *fields;

            result = mysql_store_result(&mysql);
            if(result){
                Json::Value arrayObj;

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
            }
        }
        root["status"] = "800";
        return root.toStyledString();
    } catch (const char * e) {
        cout << "search receive exception " << e << endl;
        root["message"] = e;
    } catch (int & e){
        cout << "search receive exception " << e << endl;
        root["message"] = e;
    } catch (...){
        cout << "search receive exception " <<  endl;
        root["message"] = "unknon error";
    }
    root["status"] = "500";
    return root.toStyledString();
}
