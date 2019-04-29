TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Server/datasrc.cpp \
    Server/rtspsession.cpp \
    Server/rtspsvr.cpp \
    Server/tsfilereader.cpp \
    decodesrc.cpp \
    def.cpp \
    listensock.cpp \
    mutex.cpp \
    myrtpsession.cpp \
    ntime.cpp \
    printlog.cpp \
    sock.cpp \
    tcpsock.cpp \
    thread.cpp

HEADERS += \
    Server/datasrc.h \
    Server/rtspsvr.h \
    Server/tsfilereader.h \
    decodesrc.h \
    def.h \
    mutex.h \
    Server/rtspsession.h \
    listensock.h \
    myrtpsession.h \
    ntime.h \
    printlog.h \
    sock.h \
    tcpsock.h \
    thread.h \
    tsheader.h
LIBS += -lpthread -lavformat  -lavcodec -lavutil -lm -lz -lswscale  -lswresample -ljrtp
