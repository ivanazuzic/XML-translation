#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QQuickStyle>

#include "taglist.h"
#include "tagmodel.h"
#include "pugixml.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("name");
    app.setOrganizationDomain("name");

    QQuickStyle::setStyle("Material");

    qmlRegisterType<TagModel>("Tag", 1, 0, "TagModel");
    qmlRegisterUncreatableType<TagList>("Tag", 1, 0, "TagList", QStringLiteral("TagList should not be created in QML"));

    TagList tagList;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("tagList"), &tagList);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
