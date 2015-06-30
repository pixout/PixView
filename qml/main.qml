import QtQuick 2.0
import Painter 1.0

Rectangle {
    id: col1
    width: 600
    height: 600

        PainterItem {
            id: painter
            objectName: "painter"
	    anchors.fill: parent
            anchors.centerIn: parent
        }
}
