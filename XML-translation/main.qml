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
        id: fileSaveAsDialog
        title: "Save As"
        folder: shortcuts.home
        onAccepted: {
            var path = fileSaveAsDialog.fileUrl.toString();
            // remove prefixed "file://"
            path = path.replace(/^(file:\/{2})/,"");
            // unescape html codes like '%23' for '#'
            console.log(decodeURIComponent(path));
            tagList.saveListAs(decodeURIComponent(path))
            fileSaveAsDialog.close()
        }
        onRejected: {
            console.log("Canceled")
            fileSaveAsDialog.close()
        }
        Component.onCompleted: visible = false
        nameFilters: [ "XML files (*.xml)" ]
        selectMultiple: false
        selectExisting: false
    }

    MessageDialog {
        id: discardChangesDialog
        title: "Discard changes?"
        icon: StandardIcon.Question
        text: "The file was changed. Are you sure you want to discard changes?"
        detailedText: "If you choose Yes, your changes will be discarded. If you choose No you will be able to keep editing the file."
        standardButtons: StandardButton.Yes | StandardButton.No
        Component.onCompleted: visible = false
        onYes: {
            fileOpenDialog.open()
            discardChangesDialog.close()
        }
        onNo: discardChangesDialog.close()
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Open...")
                onTriggered: {
                    console.log(tagList.modified())
                    if (tagList.modified()){
                        discardChangesDialog.open()
                    } else {
                        fileOpenDialog.open() //tagList.openList()
                    }
                }
            }
            Action {
                text: qsTr("&Save")
                onTriggered: tagList.saveList()
            }
            Action {
                text: qsTr("Save &As...")
                onTriggered: fileSaveAsDialog.open()
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
    Column {
        width: parent.width
        height: parent.height
        TagList{
            width: parent.width
            height: parent.height
        }

        /*TagTable {
            width: parent.width
            height: parent.height
        }*/
    }

}
