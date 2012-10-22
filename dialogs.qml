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

  VBoxLayout {
    PushButton {
      text: qsTr("InputDialog::getInt()")
      onClicked: {
        var value = InputDialog.getInt(0, qsTr("Integer Input"), qsTr("Percentage..."), 25)
        console.log("InputDialog.getInt returned " + value)
      }
    }

    PushButton {
      text: qsTr("InputDialog::getDouble()")
      onClicked: {
        var value = InputDialog.getDouble(0, qsTr("Double Input"), qsTr("Amount:"), 37.56)
        console.log("InputDialog.getDouble returned " + value)
      }
    }

    PushButton {
      text: qsTr("InputDialog::getItem()")
      onClicked: {
        var items = [ qsTr("Spring"), qsTr("Summer"), qsTr("Autem"), qsTr("Winter") ]
        var item = InputDialog.getItem(0, qsTr("Item Selection"), qsTr("Season:"), items)
        console.log("InputDialog.getItem returned " + item)
      }
    }

    PushButton {
      text: qsTr("InputDialog::getText()")
      onClicked: {
        var text = InputDialog.getText(0, qsTr("Text Input"), qsTr("User name:"))
        console.log("InputDialog.getText returned " + text)
      }
    }

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

  }
}
