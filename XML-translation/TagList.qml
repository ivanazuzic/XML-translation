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
                            }
                        }
                    }
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
            ScrollView {
                id: originalScrollView
                width: parent.width
                height: parent.height
                clip: true
                Text{
                    font.family: "Helvetica"
                    font.pointSize: 12
                    text: list.model.data(list.model.index(list.currentIndex, 0), 1)
                    width: parent.width
                    height: parent.height
                    wrapMode: Text.WordWrap
                }
            }
        }
        Frame {
            width: parent.width
            height: 0.5 * parent.height
            ScrollView {
                id: translationScrollView
                width: parent.width
                height: parent.height
                TextArea{
                    id: translationfield
                    width: parent.width
                    height: parent.height
                    placeholderText: qsTr("Enter translation")
                    text: list.model.data(list.model.index(list.currentIndex, 0), 2)
                    wrapMode: TextArea.WordWrap
                    font.family: "Helvetica"
                    font.pointSize: 12
                    onTextChanged: {
                        list.model.setData(list.model.index(list.currentIndex, 0), translationfield.text, 2);
                    }
                    selectByMouse: true
                }
            }
        }
    }
}
