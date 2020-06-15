#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    const QString PATH = "../../plugin_imports";

    QGuiApplication app(argc, argv);

    // solution 1: set environment variable QML2_IMPORT_PATH
//     qputenv("QML2_IMPORT_PATH",PATH.toUtf8());

    QQmlApplicationEngine engine;

    // solution 2
    engine.addImportPath(PATH);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
