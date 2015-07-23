import QtQuick 2.4
import QtQuick.Dialogs 1.2

    FileDialog {
        id: fileDialog
        visible: false
        title: "Please choose a fixture file"
        folder: settings.appPath
        nameFilters: [ "Pixout fixtues (*.pxm)","MADRIX fixtures files (*.mpx)", "All files (*)" ]
    }
