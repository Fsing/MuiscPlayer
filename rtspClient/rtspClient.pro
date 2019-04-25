TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    RtspClient.cpp \
    Def.cpp \
    Thread.cpp \
    Mutex.cpp \
    NTime.cpp \
    PrintLog.cpp \
    TcpSock.cpp \
    Sock.cpp \
    EncodeSrc.cpp \
    MyRtpSession.cpp

HEADERS += \
    RtspClient.h \
    Def.h \
    Thread.h \
    Mutex.h \
    NTime.h \
    PrintLog.h \
    TcpSock.h \
    Sock.h \
    EncodeSrc.h \
    MyRtpSession.h
LIBS += -lpthread
LIBS += -lSDL2main -lSDL2 -lavformat  -lavcodec -lavutil -lm -lz -lswscale  -lswresample -ljrtp
