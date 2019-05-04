#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "./fsingClient/fsingclient.h"
#include "./rtspClient/qmlrtspclient.h"
#include "./localMusicPlay/localplay.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);



    qmlRegisterType<FSingClient>("FSingClient", 1, 0, "FSingClient");
    qmlRegisterType<QmlRtspClient>("RtspClient", 1, 0, "RtspClient");
    qmlRegisterType<LocalPlay>("LocalPlay", 1, 0, "LocalPlay");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath",
            QGuiApplication::applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
