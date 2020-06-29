#ifndef TAGLIST_H
#define TAGLIST_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "pugixml.hpp"

struct TagItem
{
    QString tag;
    QString original;
    QString translation;
};

class TagList : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void importList(QString path) {
        clearAll();
        m_path = path;
        m_source = m_path.toUtf8().constData();
        loadItems(false);
    }

    Q_INVOKABLE void openList(QString path) {
        clearAll();
        m_path = path;
        m_source = m_path.toUtf8().constData();
        loadItems(true);
    }

    Q_INVOKABLE void saveList() {
        qDebug() << m_path;
        m_doc.save_file(m_path.toUtf8().constData());
        importList(m_path); // bez ovoga se UI ne azurira
    }

    Q_INVOKABLE void saveListAs(QString path) {
        m_path = path;
        m_source = m_path.toUtf8().constData();
        saveList();
    }


    Q_INVOKABLE void exportList(QString path) {
        m_doc.save_file(path.toUtf8().constData());
    }

    explicit TagList(QObject *parent = nullptr);

    QVector<TagItem> items() const;

    bool setItemAt(int index, const TagItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem(QString tag, QString original, QString translation);
    void removeItems();
    void loadItems(bool forOpening);
    void clearAll();
    bool modified();

private:
    QVector<TagItem> mItems;

    QVector<pugi::xml_node> mNodes;

    QString m_path;
    std::string m_source;

    pugi::xml_document m_doc;
    pugi::xml_node m_root;

    pugi::xml_parse_result result;

    void dfs(pugi::xml_node root, bool forOpening);

};

#endif // TAGLIST_H
