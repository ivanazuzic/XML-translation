import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

//import Tag 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("XML translation")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Open...")
                onTriggered: tagList.openList()
            }
            Action {
                text: qsTr("&Save")
            }
            Action {
                text: qsTr("Save &As...")
            }
            MenuSeparator { }
            Action {
                text: qsTr("&Quit")
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
            }
        }
    }

    TagList{
        width: parent.width
        height: parent.height
    }

}
