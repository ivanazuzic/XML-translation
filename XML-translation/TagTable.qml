import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

import Tag 1.0


Row {
    width: parent.width
    height: parent.height
    Column {
        width: parent.width * 0.5
        height: parent.height
        TextField {
            width: parent.width
            height: 0.1 * parent.height
            id: filtering
        }

        Frame {
            width: parent.width
            height: 0.9 * parent.height
            TableView {
                id: list
                property int selectedItemID
                property string originalValue
                property string translation
                width: parent.width
                height: parent.height


                TableViewColumn {
                    role: "tag"
                    title: "Tag"
                    width: 100
                }
                TableViewColumn {
                    role: "original"
                    title: "Original"
                    width: 200
                }
                TableViewColumn {
                    role: "translation"
                    title: "Translation"
                    width: 200
                }

                model: TagModel{
                    list: tagList
                }

                onClicked:  {
                    selectedItemID = row
                    // Column is always zero as it's a list
                    var column_number = 0;
                    // get `QModelIndex`
                    var q_model_index = list.model.index(selectedItemID, column_number);

                    originalValue = list.model.data(q_model_index, 1);
                    translation = list.model.data(q_model_index, 2);
                    console.log(originalValue)
                    console.log(translation)
                }

            }

        }
    }
    Column{
        width: parent.width * 0.5
        height: parent.height
        Frame {
            width: parent.width
            height: 0.4 * parent.height
            Text{
                font.family: "Helvetica"
                font.pointSize: 12
                text: list.originalValue
            }
        }
        Frame {
            width: parent.width
            height: 0.4 * parent.height
            ScrollView {
                id: translationScrollView
                width: parent.width
                height: parent.height
                TextArea{
                    id: translationfield
                    width: parent.width
                    height: parent.height
                    text: "list.originalValue"
                    wrapMode: TextArea.WordWrap
                    font.family: "Helvetica"
                    font.pointSize: 12
                    //onEditingFinished: list.model.setData(list.currentIndex, "3", 2) //list.model.setProperty(list.currentIndex, "translation", text)
                }
            }
        }
        Row {
            width: parent.width
            height: 0.2 * parent.height
            Button {
                width: 0.5 * parent.width
                height: parent.height
                text: "Confirm"
                onClicked: {
                    // Column is always zero as it's a list
                    var column_number = 0;
                    // get `QModelIndex`
                    var q_model_index = list.model.index(list.currentIndex, column_number);

                    // see for list of roles:
                    // http://doc.qt.io/qt-5/qabstractitemmodel.html#roleNames
                    var role = 2

                    var data_changed = list.model.setData(q_model_index, translationfield.text, role);
                }
            }
            Button {
                width: 0.5 * parent.width
                height: parent.height
                text: "Reset"
                onClicked: {
                    // Column is always zero as it's a list
                    var column_number = 0;
                    // get `QModelIndex`
                    var q_model_index = list.model.index(list.currentIndex, column_number);

                    // see for list of roles:
                    // http://doc.qt.io/qt-5/qabstractitemmodel.html#roleNames
                    var role = 2

                    var data_changed = list.model.setData(q_model_index, "", role);
                    translationfield.text = ""
                }
            }
        }

    }
}
