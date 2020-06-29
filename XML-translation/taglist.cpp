#include "taglist.h"

TagList::TagList(QObject *parent) : QObject(parent)
{
    clearAll();
}

QVector<TagItem> TagList::items() const
{
    return mItems;
}

bool TagList::setItemAt(int index, const TagItem &item)
{
    //qDebug() << "Value" << mNodes[index].text().as_string();
    //qDebug() << "Setting item " << index << " from " << item.original << " to " << item.translation;
    if (index < 0 || index >= mItems.size()) {
        return false;
    }
    const TagItem &oldItem = mItems.at(index);
    if(item.tag == oldItem.tag && item.original == oldItem.original && item.translation == oldItem.translation) {
        return false;
    }
    mItems[index] = item;
    if (item.translation == "") {
        mNodes[index].last_child().set_value(item.original.toUtf8().constData());
    } else {
        mNodes[index].last_child().set_value(item.translation.toUtf8().constData());
    }
    /*qDebug() << "Value" << mNodes[index].text().as_string();
    for (auto no: mNodes){
        qDebug() << "Node " << no.text().as_string();
    }*/
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

void TagList::loadDocument(bool forOpening)
{
    result = m_doc.load_file(m_source.c_str(),
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
    traverseTags(m_doc, forOpening);
}

void TagList::clearAll()
{
    removeItems();
    mNodes.clear();
    m_path = "";
    m_source = "";
}

bool TagList::modified()
{
    for (int i = mItems.size()-1; i >= 0; i--) {
        if (!mItems[i].translation.isEmpty()) {
            return true;
        }
    }
    return false;
}

void TagList::traverseTags(pugi::xml_node &root, bool forOpening) {
    if (strncmp(root.first_child().name(), "source", 6) == 0 && strncmp(root.last_child().name(), "target", 6) == 0 && forOpening) {
        QString parent = root.name();
        QString source = root.first_child().text().as_string();
        QString target = root.last_child().text().as_string();
        appendItem(parent, source, target);
        root.remove_child(root.first_child());
        root.remove_child(root.first_child());
        root.text().set(target.toUtf8().constData());
        mNodes.append(root);
    } else {
        if (root.parent() && strlen(root.name()) == 0) {
            //qDebug() << root.parent().name() << "-" << root.text().as_string();
            QString parent = root.parent().name();
            appendItem(parent, root.text().as_string(), "");
            mNodes.append(root.parent());
        }
        for (auto child:root.children()) {
            traverseTags(child, forOpening);
        }
    }
}


