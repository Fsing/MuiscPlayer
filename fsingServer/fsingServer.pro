TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    database.cpp \
    fsingservice.cpp \
    fan.cpp \
    songlist.cpp \
    fanbroker.cpp \
    songlistbroker.cpp \
    songbroker.cpp \
    rediscontrol.cpp \
    Controller/commentController.cpp \
    Controller/listenMusicController.cpp \
    Controller/loginController.cpp \
    Controller/searchController.cpp \
    Controller/songListController.cpp
LIBS += -lmysqlclient  -lhiredis

HEADERS += \
    database.h \
    fsingservice.h \
    macro.h \
    song.h \
    songlist.h \
    user.h \
    ralationbroker.h \
    fan.h \
    fanbroker.h \
    songbroker.h \
    songlistbroker.h \
    rediscontrol.h \
    Controller/commentControler.h \
    Controller/listenMusicController.h \
    Controller/loginController.h \
    Controller/searchController.h \
    Controller/songlistController.h
LIBS += -lpthread -lboost_system -lboost_thread -ljsoncpp

DISTFILES += \
    文本文件
