#include "tagmodel.h"

#include "taglist.h"

TagModel::TagModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

int TagModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant TagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const TagItem item = mList->items().at(index.row());

    switch (role) {
    case TagRole:
        return QVariant(item.tag);
        break;
    case OriginalRole:
        return QVariant(item.original);
        break;
    case TranslationRole:
        return QVariant(item.translation);
        break;
    }

    return QVariant();
}

bool TagModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //qDebug() << value.toString();
    if (!mList) {
        return false;
    }
    TagItem item = mList->items().at(index.row());
    switch (role) {
    case TagRole:
        item.tag = value.toString();
        break;
    case OriginalRole:
        item.original = value.toString();
        break;
    case TranslationRole:
        item.translation = value.toString();
        break;
    }
    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TagModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> TagModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TagRole] = "tag";
    names[OriginalRole] = "original";
    names[TranslationRole] = "translation";
    return names;
}

TagList *TagModel::list() const
{
    return mList;
}

void TagModel::setList(TagList *list)
{
    beginResetModel();

    if(mList) {
        mList->disconnect(this);
    }

    mList = list;

    if(mList) {
        connect(mList, &TagList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &TagList::postItemAppended, this, [=]() {
            endInsertRows();
        });
        connect(mList, &TagList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &TagList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
