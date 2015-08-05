import QtQuick 2.4
import AppSettings 1.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

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
                text: settings.port.toString()

                onEditingFinished: {
                    settings.port = text
                    console.log(" Port updated to "+settings.port)
                }
            }

            Text {
                text: "Position";
                color: "white";
                Layout.alignment: Qt.AlignCenter;
            }

            ComboBox {
                currentIndex: settings.position === AppSettings.Vertical ? 0 : 1
                model: [ "Vertical", "Horizontal" ]

                onCurrentIndexChanged: {
                    console.log(" Position changed to "+currentIndex)

                    if( currentIndex == 0 ) {
                        settings.position = AppSettings.Vertical;
                    } else {
                        settings.position = AppSettings.Horizontal;
                    }
                }
            }

            Text {
                text: "Pixel Mapping";
                color: "white";
                Layout.alignment: Qt.AlignCenter;
            }

            RowLayout {
                TextField {
                    text: settings.fixturePath
                    Layout.fillWidth: true
                }
                Button {
                    text: "Browse"

                    onClicked: {
                        browseDialog.title = "Browse fixtures";
                        browseDialog.selectExisting = true;
                        browseDialog.open()

                    }
                }
            }
        } // grid.layout
    }
}
