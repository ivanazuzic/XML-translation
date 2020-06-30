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
        loadDocument(false);
    }

    Q_INVOKABLE void openList(QString path) {
        clearAll();
        m_path = path;
        m_source = m_path.toUtf8().constData();
        loadDocument(true);
    }

    Q_INVOKABLE void saveList() {
        //qDebug() << m_path;
        //qDebug() << "Svi tagovi";
        for (int i = 0; i < mItems.size(); i++) {
            //qDebug() << mItems[i].tag << " " << mItems[i].original << " " << mItems[i].translation;
            if(!mItems[i].translation.isEmpty()){
                mNodes[i].remove_child(mNodes[i].first_child());
                mNodes[i].append_child("source").text().set(mItems[i].original.toUtf8().constData());
                mNodes[i].append_child("target").text().set(mItems[i].translation.toUtf8().constData());
            }
        }

        m_doc.save_file(m_path.toUtf8().constData());
        //importList(m_path); // bez ovoga se UI ne azurira, ali ovo vise ne treba jer se promijenila strategija spremanja
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
    void loadDocument(bool forOpening);
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

    void traverseTags(pugi::xml_node &root, bool forOpening);

};

#endif // TAGLIST_H
