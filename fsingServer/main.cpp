#include <iostream>
#include <mysql/mysql.h>    //用的是c++的API
#include <cstring>
#include <algorithm>
#include <string>
#include <database.h>
#include <sstream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "database.h"
#include "fsingservice.h"

using namespace std;
using namespace boost::asio;
using boost::asio::io_service;

int main()
{
    Server server;
    //thread dis(&Server::display,&server);
    //dis.detach();
    server.waitingForConnect();
    return 0;
}
