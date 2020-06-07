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
    Q_INVOKABLE void gimmeText() {
        qDebug() << "new text";
    }
    Q_INVOKABLE void openList(QString m_source) {
        removeItems();
        loadItems(m_source.toUtf8().constData());
    }
    Q_INVOKABLE void saveList() {

    }

    Q_INVOKABLE void saveListAs() {
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
    void loadItems(std::string m_source);

private:
    QVector<TagItem> mItems;

    void dfs(pugi::xml_node root);

};

#endif // TAGLIST_H
