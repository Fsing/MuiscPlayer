#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include "DB/database.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <Include/macro.h>
#include "json/json.h"

using namespace std;
class SearchController
{
public:
    SearchController();
    string search(string songKey);
};

#endif // SEARCHCONTROLLER_H
