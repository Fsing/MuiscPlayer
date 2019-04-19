TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Sock.cpp \
    TcpSock.cpp \
    Thread.cpp \
    PrintLog.cpp \
    Server/DataSrc.cpp \
    Server/RtspSession.cpp \
    Server/RtspSvr.cpp \
    Server/TsFileReader.cpp \
    Mutex.cpp \
    NTime.cpp \
    Def.cpp \
    ListenSock.cpp

HEADERS += \
    TsHeader.h \
    Sock.h \
    TcpSock.h \
    Thread.h \
    NTime.h \
    PrintLog.h \
    Server/DataSrc.h \
    Server/RtspSession.h \
    Server/RtspSvr.h \
    Server/TsFileReader.h \
    Mutex.h \
    Def.h \
    ListenSock.h \
    RtpSession.h
LIBS += -lpthread
