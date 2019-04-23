QT += quick
CONFIG += c++11

INCLUDEPATH += -I /usr/local/ffmpeg/include\
-I /usr/local/include

LIBS += -L/usr/local/ffmpeg/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale\
 -L/usr/local/lib -ltag -ltag_c\
-L/usr/local/lib -lz

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    attentionorfansquerycontroller.cpp \
    attenusercontroller.cpp \
    collectcontroller.cpp \
    downloadmusiccontroller.cpp \
    fsingclient.cpp \
    fsingcontroller.cpp \
    listenmusiccontroller.cpp \
    logincontroller.cpp \
    lyric.cpp \
    searchcontroller.cpp \
    songinfo.cpp \
    localmusic.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    attentionorfansquerycontroller.h \
    attenusercontroller.h \
    collectcontroller.h \
    downloadmusiccontroller.h \
    fsingclient.h \
    fsingcontroller.h \
    listenmusiccontroller.h \
    logincontroller.h \
    lyric.h \
    searchcontroller.h \
    songinfo.h \
    localmusic.h

LIBS += -lpthread -lboost_system -lboost_thread -ljsoncpp
