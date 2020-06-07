import QtQuick 2.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

//import Tag 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("XML translation")

    FileDialog {
        id: fileOpenDialog
        title: "Open"
        folder: shortcuts.home
        onAccepted: {
            var path = fileOpenDialog.fileUrl.toString();
            // remove prefixed "file://"
            path = path.replace(/^(file:\/{2})/,"");
            // unescape html codes like '%23' for '#'
            console.log(decodeURIComponent(path));
            tagList.openList(decodeURIComponent(path))
            fileOpenDialog.close()
        }
        onRejected: {
            console.log("Canceled")
            fileOpenDialog.close()
        }
        Component.onCompleted: visible = false
        selectMultiple: false
        nameFilters: [ "XML files (*.xml)" ]
    }

    FileDialog {
        id: fileSaveDialog
        title: "Save"
        folder: shortcuts.home
        onAccepted: {
            var path = fileSaveDialog.fileUrl.toString();
            // remove prefixed "file://"
            path = path.replace(/^(file:\/{2})/,"");
            // unescape html codes like '%23' for '#'
            console.log(decodeURIComponent(path));
            tagList.saveList(decodeURIComponent(path))
            fileSaveDialog.close()
        }
        onRejected: {
            console.log("Canceled")
            fileSaveDialog.close()
        }
        Component.onCompleted: visible = false
        selectMultiple: false
        nameFilters: [ "XML files (*.xml)" ]
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Open...")
                onTriggered: fileOpenDialog.open() //tagList.openList()
            }
            Action {
                text: qsTr("&Save")
                onTriggered: fileSaveDialog.open() //tagList.openList()
            }
            Action {
                text: qsTr("Save &As...")
            }
            MenuSeparator { }
            Action {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
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
