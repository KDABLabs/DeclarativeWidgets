import QtGui 1.0

MainWindow {
  windowTitle: qsTr("Declarative Widget Editor")

  size: Qt.size(500, 300)

  MenuBar {
    Menu {
      title: qsTr("File")

      Action {
        text: qsTr("New")
      }

      Action {
        text: qsTr("Save")
      }

      Separator {}

      Action {
        text: qsTr("Print")
      }

      Separator {}

      Action {
        text: "Close"
        onTriggered: Qt.quit()
      }
    }

    Menu {
      title: qsTr("Edit")

      Action {
        text: qsTr("Undo")
        onTriggered: textEdit.undo()
      }

      Action {
        text: qsTr("Redo")
        onTriggered: textEdit.redo()
      }

      Separator {}

      Action {
        text: qsTr("Cut")
        onTriggered: textEdit.cut()
      }

      Action {
        text: qsTr("Copy")
        onTriggered: textEdit.copy()
      }

      Action {
        text: qsTr("Paste")
        onTriggered: textEdit.paste()
      }

      Separator {}

      Action {
        text: qsTr("Select All")
        onTriggered: textEdit.selectAll()
      }
    }

    Menu {
      title: qsTr("View")

      Action {
        text: qsTr("Enlarge Font")
        onTriggered: textEdit.zoomIn()
      }

      Action {
        text: qsTr("Shrink Font")
        onTriggered: textEdit.zoomOut()
      }
    }

    Menu {
      title: qsTr("Help")

      Action {
        text: qsTr("About")
      }

      Action {
        text: qsTr("About Qt")
      }
    }
  }

  ToolBar {
    Action {
      text: qsTr("New")
    }

    Separator {}

    Label {
      text: "Zoom"
    }
  }

  TextEdit {
    id: textEdit

    contextMenuPolicy: Qt.ActionsContextMenu

    Action {
      text: "Copy"
    }
    Action {
      text: "Paste"
    }
  }

  StatusBar {
    Label {
      StatusBar.stretch: 2
      text: "Pos:"
    }
  }
}
