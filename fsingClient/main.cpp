#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "fsingclient.h"
#include "./rtspClient/qmlrtspclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<FSingClient>("FSingClient", 1, 0, "FSingClient");
    qmlRegisterType<QmlRtspClient>("RtspClient", 1, 0, "RtspClient");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath",
            QGuiApplication::applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
