#include "taglist.h"

TagList::TagList(QObject *parent) : QObject(parent)
{
    /*mItems.append({QStringLiteral("a"), QStringLiteral("sadfgsa"), QStringLiteral("fgshjtukfdjhbsg")});
    mItems.append({QStringLiteral("tekst"), QStringLiteral("macka"), QStringLiteral("cat")});
    mItems.append({QStringLiteral("img"), QStringLiteral("pas"), QStringLiteral("dog")});*/
}

QVector<TagItem> TagList::items() const
{
    return mItems;
}

bool TagList::setItemAt(int index, const TagItem &item)
{
    if (index < 0 || index >= mItems.size()) {
        return false;
    }
    const TagItem &oldItem = mItems.at(index);
    if(item.tag == oldItem.tag && item.original == oldItem.original && item.translation == oldItem.translation) {
        return false;
    }
    mItems[index] = item;
    return true;
}

void TagList::appendItem(QString tag, QString original, QString translation)
{
    emit preItemAppended();

    TagItem item;
    item.tag = tag;
    item.original = original;
    item.translation = translation;
    mItems.append(item);

    emit postItemAppended();
}

void TagList::removeItems()
{
    for (int i = mItems.size()-1; i >= 0; i--) {
        emit preItemRemoved(i);

        mItems.removeAt(i);

        emit postItemRemoved();
    }
}
