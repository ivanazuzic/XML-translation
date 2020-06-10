import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

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
            placeholderText: qsTr("Enter a tag to filter")
        }

        Frame {
            width: parent.width
            height: 0.9 * parent.height
            ListView {
                id: list
                property int selectedItemID
                property string originalValue
                property string translation
                implicitWidth: parent.width
                implicitHeight: parent.height
                clip: true

                model: TagModel{
                    list: tagList
                }

                delegate: Component {
                    Rectangle {
                        visible: currtag.text.includes(filtering.text)
                        height: currtag.text.includes(filtering.text) ? tagrow.height : 0
                        width: parent.width
                        color:  ListView.isCurrentItem ? "lightsteelblue" : "transparent"
                        radius: 5
                        property var view: ListView.view
                        property int itemIndex: index
                        RowLayout{
                            id: tagrow
                            Text {
                                id: currtag
                                text: tag
                                color: "blue"
                                font.family: "Helvetica"
                                font.pointSize: 12
                            }
                            Text {
                                id: curroriginal
                                text: original
                                font.family: "Helvetica"
                                font.pointSize: 12
                                visible: translation.length === 0
                            }
                            Text {
                                id: currtranslation
                                text: translation
                                font.family: "Helvetica"
                                font.pointSize: 12
                                color: "green"
                                visible: translation.length > 0
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                view.currentIndex = itemIndex;
                                //list.model.setProperty(itemIndex, "tag", "cost * 2")
                                //console.log(list.model.rowCount())
                                //console.log(currtag.text)
                                //list.originalValue = curroriginal.text
                                //list.translation = currtranslation.text


                            }
                        }
                    }
                }
                onCurrentItemChanged: {
                    selectedItemID = list.currentIndex
                    //originalValue = list.model.get(list.currentIndex).original;
                    //translation = list.model.get(list.currentIndex).translation;

                    // Column is always zero as it's a list
                    var column_number = 0;
                    // get `QModelIndex`
                    var q_model_index = list.model.index(selectedItemID, column_number);

                    // see for list of roles:
                    // http://doc.qt.io/qt-5/qabstractitemmodel.html#roleNames
                    var role = 1

                    //var data_changed = list.model.setData(q_model_index, "3", role);

                    originalValue = list.model.data(q_model_index, 1);
                    translation = list.model.data(q_model_index, 2);
                    console.log(originalValue)
                    console.log(translation)
                    translationfield.text = translation
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
                    placeholderText: qsTr("Enter translation")
                    text: list.translation
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
