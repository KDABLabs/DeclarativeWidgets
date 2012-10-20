import QtGui 1.0

MainWindow {
  windowTitle: textEdit.modified ? qsTr("Declarative Widget Editor *modified*") : qsTr("Declarative Widget Editor")

  size: Qt.size(500, 300)

  Dialog {
    id: myDialog

    size: Qt.size(300, 200)
    visible: false

    VBoxLayout {
      Label {
        text: "Hello World"
      }
      DialogButtonBox {
        standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

        onAccepted: myDialog.accept()
        onRejected: myDialog.reject()
      }
    }
  }

  MenuBar {
    Menu {
      title: qsTr("File")

      Action {
        text: qsTr("New")
        onTriggered: {
          var result = myDialog.exec()
          console.log("result="+result)
        }
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
        onTriggered: MessageBox.about(0, qsTr("About Declarative Widgets Editor Example"),
                                      qsTr("This is an example of a simple text editor written in QML using DeclarativeWidgets"))
      }

      Action {
        text: qsTr("About Qt")
        onTriggered: MessageBox.aboutQt(0, qsTr("About Qt"))
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
  }

  StatusBar {
    Label {
      StatusBar.stretch: 2
      text: "Pos:"
    }
  }
}
