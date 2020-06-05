import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import Tag 1.0

Column{
    width: parent.width
    height: parent.height
    Row{
        width: parent.width
        height: parent.height
        Column{
            width: parent.width * 0.5
            height: parent.height
            Frame {
                width: parent.width
                height: parent.height
                ListView {
                    id: list
                    property int selectedItemID
                    property string originalValue
                    property string translation
                    implicitWidth: 250
                    implicitHeight: 250
                    clip: true

                    model: TagModel{
                        list: tagList
                    }

                    delegate: Component {
                        Rectangle {
                            height: tagrow.height
                            width: parent.width
                            color:  ListView.isCurrentItem ? "lightsteelblue" : "white"
                            radius: 5
                            property var view: ListView.view
                            property int itemIndex: index
                            RowLayout{
                                id: tagrow
                                Text { text: tag }
                                Text { text: original }
                                Text { text: translation }
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    view.currentIndex = itemIndex;
                                    //list.model.setProperty(itemIndex, "tag", "cost * 2")
                                }
                            }
                        }
                    }
                    onCurrentItemChanged: {
                        selectedItemID = list.currentIndex
                        //originalValue = list.model.get(list.currentIndex).original;
                        //translation = list.model.get(list.currentIndex).translation;
                    }
                }
            }

        }
        Column{
            width: parent.width * 0.5
            height: parent.height
            Frame {
                width: parent.width
                height: 0.5 * parent.height
                Text{
                    text: list.originalValue
                }
            }
            Frame {
                width: parent.width
                height: 0.5 * parent.height
                TextField{
                    text: list.translation
                    onEditingFinished: list.model.setProperty(list.currentIndex, "translation", text)
                }
            }

        }
    }
}
