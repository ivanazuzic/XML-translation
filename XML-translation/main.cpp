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

    TagModel *m_messageModel = new TagModel;
    m_messageModel->setList(&tagList);
    QSortFilterProxyModel *m_messageProxyModel = new QSortFilterProxyModel;
    m_messageProxyModel->setSourceModel(qobject_cast<QAbstractListModel *>(m_messageModel));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("tagList"), &tagList);


    engine.rootContext()->setContextProperty("messages", m_messageProxyModel);
    //m_messageProxyModel->setSortRole(TagModel::TagRole);
    m_messageProxyModel->setDynamicSortFilter(true);
    //m_messageProxyModel->sort(0, Qt::AscendingOrder);
    m_messageProxyModel->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,
                                                QRegExp::FixedString));
    m_messageProxyModel->setFilterKeyColumn(0);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
