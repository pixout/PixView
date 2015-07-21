import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

    Dialog {
        modality: Qt.WindowModal
        visible: false
        title: "About"

        contentItem: Rectangle {
            implicitWidth: 400
            implicitHeight: 200

            RowLayout {
                anchors { fill: parent; bottomMargin: 40; leftMargin: 5 }

                Rectangle {
                    width: 150
                    height: 150
                    anchors.leftMargin: 5

                    color: "red"
                }

                ColumnLayout{

                Text {
                    text: "Software Version: 0.0.1"
                }

                Text {
                    text: "Copyright 2013-2015 The Pixout SIA"
                }

                Text {
                    text: "License: GNU GPL v2"
                }

                Text {
                    wrapMode: Text.Wrap
                    text: "The program is provided AS IS<br>with NO WARRANTY OF ANY KIND,<br>INCLUDING THE WARRANTY OF DESIGN,<br>MERCHANTABILITY AND FITNESS<br>FOR A PARTICULAR PURPOSE."
                }


                }
            }

            RowLayout {
                id: layout
                anchors { bottom: parent.bottom; left: parent.left; right: parent.right;  }

                Button{
                    id: acceptButton
                    text: "OK"
                    height: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottomMargin: 5
                    onClicked: {
                        about.close()
                    }
                }
            }
        }

    }
