#ifndef TAGMODEL_H
#define TAGMODEL_H

#include <QAbstractListModel>

class TagList;

class TagModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TagList *list READ list WRITE setList)

public:
    explicit TagModel(QObject *parent = nullptr);

    enum {
        TagRole,
        OriginalRole,
        TranslationRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    TagList *list() const;
    void setList(TagList *list);

private:
    TagList *mList;
};

#endif // TAGMODEL_H
