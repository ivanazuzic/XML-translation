#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "taglist.h"
#include "tagmodel.h"
#include "pugixml.hpp"

/*void dfs(TagList &results, pugi::xml_node root) {
    if (root.parent() && strlen(root.name()) == 0) {
        //qDebug() << root.parent().name() << "-" << root.text().as_string();
        QString parent = root.parent().name();
        results.appendItem(parent, root.text().as_string(), "");
    }
    for (auto child:root.children()) {
        dfs(results, child);
    }
}

void readXML(std::string m_source, pugi::xml_document m_doc, pugi::xml_node m_root) {
    // Load XML file into memory
    // Remark: to fully read declaration entries you have to specify
    // "pugi::parse_declaration"
    pugi::xml_parse_result result = m_doc.load_file(m_source.c_str(),
        pugi::parse_default|pugi::parse_declaration);
    if (!result)
    {
        qDebug() << "Parse error: " << result.description()
            << ", character pos= " << result.offset;
    }
    // A valid XML document must have a single root node
    m_root = m_doc.document_element();

    qDebug() << "Load result: " << result.description();
}*/

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("name");
    app.setOrganizationDomain("name");

    qmlRegisterType<TagModel>("Tag", 1, 0, "TagModel");
    qmlRegisterUncreatableType<TagList>("Tag", 1, 0, "TagList", QStringLiteral("TagList should not be created in QML"));

    TagList tagList;
    //tagList.appendItem("tag", "original", "/");

    /*std::string m_source = "/home/ivana/Documents/PNP/XML-translation/XML-translation/test.xml";
    pugi::xml_document m_doc;
    pugi::xml_node m_root;

    pugi::xml_parse_result result = m_doc.load_file(m_source.c_str(),
        pugi::parse_default|pugi::parse_declaration);
    if (!result)
    {
        qDebug() << "Parse error: " << result.description()
            << ", character pos= " << result.offset;
    }
    // A valid XML document must have a single root node
    m_root = m_doc.document_element();

    qDebug() << "Load result: " << result.description();

    //readXML(m_source, m_doc, m_root);
    dfs(tagList, m_doc);*/

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
