import QtGui 1.0

Widget {
  ColorDialog {
    id: colorDialog
  }

  FileDialog {
    id: fileDialog

    fileMode: FileDialog.ExistingFile
    viewMode: FileDialog.List
  }

  FontDialog {
    id: fontDialog
  }

  InputDialog {
    id: intInputDialog

    labelText: qsTr("Percentage")
  }

  VBoxLayout {
    PushButton {
      text: qsTr("Color Dialog...")
      onClicked: {
        if (colorDialog.exec())
          console.log("Selected color: " + colorDialog.currentColor)
      }
    }

    PushButton {
      text: qsTr("Color Dialog::getColor")
      onClicked: {
          console.log("Selected color: " + ColorDialog.getColor("#ff0000"))
      }
    }

    PushButton {
      text: qsTr("Color Dialog::getColor with title")
      onClicked: {
          console.log("Selected color: " + ColorDialog.getColor("#ff0000", 0, "Pick a color"))
      }
    }

    PushButton {
      text: qsTr("File Dialog...")
      onClicked: {
        if (fileDialog.exec())
          console.log("Selected files: " + fileDialog.selectedFiles)
      }
    }

    PushButton {
      text: qsTr("Font Dialog...")
      onClicked: {
        if (fontDialog.exec())
          console.log("Selected font: " + fontDialog.currentFont)
      }
    }

    PushButton {
      text: qsTr("Input Dialog (Int)...")
      onClicked: {
        if (intInputDialog.exec())
          console.log(intInputDialog.intValue + "%")
      }
    }
  }
}
