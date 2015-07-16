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
                placeholderText: settings.port.toString()
            }

            Text {
                text: "Position";
                color: "white";
                Layout.alignment: Qt.AlignCenter;
            }

            TextField {
                placeholderText: settings.position === settings.Vertical ? qsTr("vertical") : qsTr("horizontal")
            }

            Text {
                text: "Fixture Path";
                color: "white";
                Layout.alignment: Qt.AlignCenter;
            }

            RowLayout {
                TextField {
                    placeholderText: settings.fixturePath
                    Layout.fillWidth: true
                }
                Button {
                    text: "Browse"
                }
            }


        } // grid.layout

        }
        Component.onCompleted: console.log("path "+settings.fixturePath )
    }
