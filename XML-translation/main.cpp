#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QQuickStyle>
#include <QSortFilterProxyModel>

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

    TagModel *XMLtagsModel = new TagModel;
    XMLtagsModel->setList(&tagList);
    QSortFilterProxyModel *XMLtagsProxyModel = new QSortFilterProxyModel;
    XMLtagsProxyModel->setSourceModel(qobject_cast<QAbstractListModel *>(XMLtagsModel));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("tagList"), &tagList);

    engine.rootContext()->setContextProperty("XMLtagsProxyModel", XMLtagsProxyModel);
    //XMLtagsProxyModel->setSortRole(TagModel::TagRole);
    XMLtagsProxyModel->setDynamicSortFilter(true);
    //XMLtagsProxyModel->sort(0, Qt::AscendingOrder);
    XMLtagsProxyModel->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,
                                                QRegExp::FixedString));
    XMLtagsProxyModel->setFilterKeyColumn(0);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
