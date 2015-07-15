import QtQuick 2.4
import Painter 1.0
import QtQuick.Controls 1.3

ApplicationWindow {
    id: col1
    width: 600
    height: 600
    visible: true
    color: "black"
    title: "PixView, Art-Net preview"

    PainterItem {
        id: painter
        objectName: "painter"
        anchors.fill: parent
        anchors.centerIn: parent
    }
}

