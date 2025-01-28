#include "TransferDataHandler.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

static constexpr const quint16 SERVER_PORT = 8888;


int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    TcpServerHandler tcpServerHandler(SERVER_PORT);
    TransferDataHandler transferDataHandler(&tcpServerHandler);

    engine.rootContext()->setContextProperty("tcpServerHandler", &tcpServerHandler);
    engine.rootContext()->setContextProperty("transferDataHandler", &transferDataHandler);

    engine.addImportPath("qrc:/qml");
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
