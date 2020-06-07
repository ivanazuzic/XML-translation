#ifndef TAGLIST_H
#define TAGLIST_H

#include <QObject>
#include <QVector>
#include <QDebug>

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
    Q_INVOKABLE void clearList() {
                removeItems();
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

private:
    QVector<TagItem> mItems;

};

#endif // TAGLIST_H
