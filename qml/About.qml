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

                Image {
                    width: 150
                    height: 150
                    anchors.leftMargin: 5
                    source: "qrc:/logo.png"
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: 150
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
                anchors { bottom: parent.bottom; left: parent.left; right: parent.right; bottomMargin: 10 }

                Button{
                    id: acceptButton
                    text: qsTr("&Ok")
                    height: 20
                    focus: true
                    anchors.horizontalCenter: parent.horizontalCenter

                    onClicked: {
                        about.close()
                    }
                    Keys.onReturnPressed: {
                        about.close()
                    }
                }
            }
        }

    }
