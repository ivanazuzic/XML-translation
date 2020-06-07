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
                                Text {
                                    id: currtag
                                    text: tag
                                }
                                Text {
                                    id: curroriginal
                                    text: original
                                }
                                Text {
                                    id: currtranslation
                                    text: translation
                                }
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    view.currentIndex = itemIndex;
                                    //list.model.setProperty(itemIndex, "tag", "cost * 2")
                                    //console.log(list.model.rowCount())
                                    //console.log(currtag.text)
                                    list.originalValue = curroriginal.text
                                    list.translation = currtranslation.text

                                    // Column is always zero as it's a list
                                    var column_number = 0;
                                    // get `QModelIndex`
                                    var q_model_index = list.model.index(index, column_number);

                                    // see for list of roles:
                                    // http://doc.qt.io/qt-5/qabstractitemmodel.html#roleNames
                                    var role = 2

                                    var data_changed = list.model.setData(q_model_index, "3", role);

                                    console.log("data change successful?", data_changed);
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
                    onEditingFinished: list.model.setData() //list.model.setProperty(list.currentIndex, "translation", text)
                }
            }

        }
    }
}
