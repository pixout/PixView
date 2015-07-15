import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

    Rectangle {

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
