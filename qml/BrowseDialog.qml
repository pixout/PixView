import QtQuick 2.4
import QtQuick.Dialogs 1.2

    FileDialog {
        id: fileDialog
        visible: false
        title: "Please choose a fixture file"
        nameFilters: [ "Pixout fixtues (*.pxm)","MADRIX fixtures files (*.mpx)", "All files (*)" ]
        onAccepted: {
            if( fileDialog.selectExisting ) {
                console.log(fileDialog.fileUrl)
            } else {
                console.log(fileDialog.fileUrl)
            }
        }
        onRejected: {
            console.log("Canceled")
        }
    }
