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

void TagList::loadItems()
{
    std::string m_source = "/home/ivana/Documents/PNP/XML-translation/XML-translation/test.xml";
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
    dfs(m_doc);
}

void TagList::dfs(pugi::xml_node root) {
    if (root.parent() && strlen(root.name()) == 0) {
        //qDebug() << root.parent().name() << "-" << root.text().as_string();
        QString parent = root.parent().name();
        appendItem(parent, root.text().as_string(), "");
    }
    for (auto child:root.children()) {
        dfs(child);
    }
}


