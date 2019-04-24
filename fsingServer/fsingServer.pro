TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fsingservice.cpp \
    DB/database.cpp \
    DB/rediscontrol.cpp \
    Controller/commentController.cpp \
    Controller/listenMusicController.cpp \
    Controller/loginController.cpp \
    Controller/searchController.cpp \
    Controller/songListController.cpp \
    Entity/fan.cpp \
    Entity/fanbroker.cpp \
    Entity/songbroker.cpp \
    Entity/songlist.cpp \
    Entity/songlistbroker.cpp

LIBS += -lpthread -lboost_system -lboost_thread -ljsoncpp -lmysqlclient  -lhiredis

DISTFILES += \
    文本文件

HEADERS += \
    fsingservice.h \
    Include/macro.h \
    Include/user.h \
    DB/database.h \
    DB/rediscontrol.h \
    Controller/listenMusicController.h \
    Controller/loginController.h \
    Controller/searchController.h \
    Controller/songlistController.h \
    Controller/commentControler.h \
    Entity/fan.h \
    Entity/fanbroker.h \
    Entity/ralationbroker.h \
    Entity/song.h \
    Entity/songbroker.h \
    Entity/songlist.h \
    Entity/songlistbroker.h
