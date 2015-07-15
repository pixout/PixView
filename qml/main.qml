import QtQuick 2.4
import Painter 1.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: col1
    width: 600
    height: 600
    visible: true
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
            title: qsTr("&About")
        }
    }

    PainterItem {
        id: painter
        objectName: "painter"
        anchors.centerIn: parent
        anchors { fill: parent; bottomMargin: 150 }
    }

    Rectangle {
        id: nodeActions
        border.width: 1
        border.color: "#9d9d9d"
        height: 150
        anchors { top: painter.bottom; left: parent.left; right: parent.right; bottom: parent.bottom }
        color: "gray"

        GroupBox {
        title: "Settings"
        anchors { fill:parent; topMargin: 5 }

        GridLayout {
            anchors { fill:parent; topMargin: 5 }
            columns: 2

            Text {
                text: "Port";
                color: "white";
                Layout.alignment: Qt.AlignCenter;
            }

            TextField {
                placeholderText: qsTr("6454")
            }

            Text {
                text: "Position";
                color: "white";
                Layout.alignment: Qt.AlignCenter;
            }

            TextField {
                placeholderText: qsTr("vertical")
            }

            Text {
                text: "Fixture Path";
                color: "white";
                Layout.alignment: Qt.AlignCenter;
            }

            RowLayout {
                TextField {
                    placeholderText: qsTr("C:\\aa.pxm")
                    Layout.fillWidth: true
                }
                Button {
                    text: "Browse"
                }
            }


        } // grid.layout

        }
    }
}

