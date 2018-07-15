#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "src/commoninterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");
    QQmlApplicationEngine engine;

    CommonInterface commonInterface;

#ifdef Q_OS_WIN
    engine.rootContext()->setContextProperty("pt", 0.75);
#else
    engine.rootContext()->setContextProperty("pt", 1);
#endif

    engine.rootContext()->setContextProperty(QLatin1String("commonInterface"), &commonInterface);
    engine.rootContext()->setContextProperty(QLatin1String("memberModel"), commonInterface.memberModel());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
