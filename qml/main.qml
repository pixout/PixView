import QtQuick 2.4
import Painter 1.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: col1
    width: 600
    height: 600
    minimumHeight: 600      //todo: un-freeze window size
    maximumHeight: 600
    minimumWidth: 600
    maximumWidth: 600
    color: "black"
    title: "PixView, Art-Net preview"

    menuBar: MenuBar {

        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("&Help")

            MenuItem {
                text: "About"
                shortcut: "Ctrl+V"
                onTriggered: about.open()
            }

        }
    }

    PainterItem {
        id: painter
        objectName: "painter"
        anchors.centerIn: parent
        anchors { fill: parent; bottomMargin: 200 }
    }

    Rectangle {
        id: playbar
        height: 50
        color: "#373737"
        opacity: 0.3
        anchors { top: painter.bottom; left: parent.left; right: parent.right; }

        ColumnLayout {
            anchors { fill: parent; }
        Text {
            text: "Universes: 1";
            color: "white";
            opacity: 1
            font.pointSize: 10;
            font.underline: false;
            Layout.alignment: Qt.AlignRight;
        }
/*
        RowLayout {
            anchors { bottomMargin: 5 }

            Button {
                text: qsTr("Stop")
            }
            Button {
                text: qsTr("Start")
            }
            Button {
                text: qsTr("Fullscreen")
            }
        }
*/
        }
    }

    BoxSettings {
        id: nodeActions
        border.width: 1
        border.color: "#9d9d9d"
        color: "gray"
        anchors { top: playbar.bottom; left: parent.left; right: parent.right; bottom: parent.bottom }
    }

    BrowseDialog {
        id: browseDialog
        objectName: "browseDialog"

        onAccepted: {
            if( browseDialog.selectExisting ) {
                settings.fixturePath = settings.stripURLFromPath(browseDialog.fileUrl)
            }
        }
        onRejected: {
            browseDialog.close()
        }

    }

    About {
        id: about
    }
}

