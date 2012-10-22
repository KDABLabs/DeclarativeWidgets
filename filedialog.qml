import QtGui 1.0

Widget {
  VBoxLayout {
    PushButton {
      text: "FileDialog::getExistingDirectory"
      onClicked: {
        var file = FileDialog.getExistingDirectory()
        console.log("FileDialog.getExistingDirectory returned " + file)
      }
    }
    PushButton {
      text: "FileDialog::getOpenFileName"
      onClicked: {
        var file = FileDialog.getOpenFileName()
        console.log("FileDialog.getOpenFileName returned " + file)
      }
    }
    PushButton {
      text: "FileDialog::getOpenFileNames"
      onClicked: {
        var files = FileDialog.getOpenFileNames()
        console.log("FileDialog.getOpenFileNames returned " + files)
      }
    }
    PushButton {
      text: "FileDialog::getSaveFileName"
      onClicked: {
        var file = FileDialog.getSaveFileName()
        console.log("FileDialog.getSaveFileName returned " + file)
      }
    }
  }
}
