#include "collectcontroller.h"

//CollectController::CollectController()
//{

//}

CollectController::CollectController()
{

}

CollectController::~CollectController()
{

}

void CollectController::dealMessage(std::string type, Json::Value resultRoot)
{
    if (type == "COLLECTSONGLIST"){
        collectSongList(resultRoot);
    }
}

void CollectController::collectSongList(Json::Value resultRoot)
{

}
