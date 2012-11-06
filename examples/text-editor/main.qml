import QtQuick 1.0
import QtGui 1.0

MainWindow {
  id: mainWindow

  windowTitle: textEdit.modified ? qsTr("Declarative Widget Editor *modified*") : qsTr("Declarative Widget Editor")

  size: Qt.size(800, 600)

  MenuBar {
    Menu {
      title: qsTr("File")

      Action {
        id: newAction
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
        text: qsTr("Close")
        onTriggered: mainWindow.close()
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
        id: cutAction
        text: qsTr("Cut")
        onTriggered: textEdit.cut()
      }

      Action {
        id: copyAction
        text: qsTr("Copy")
        onTriggered: textEdit.copy()
      }

      Action {
        id: pasteAction
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
        onTriggered: MessageBox.about(qsTr("About Declarative Widgets Editor Example"),
                                      qsTr("This is an example of a simple text editor written in QML using DeclarativeWidgets"))
      }

      Action {
        text: qsTr("About Qt")
        onTriggered: MessageBox.aboutQt(qsTr("About Qt"))
      }
    }
  }

  ToolBar {
    ActionItem {
      action: newAction
    }

    Separator {}

    Label {
      text: "Zoom"
    }
  }

  TextEdit {
    id: textEdit

    contextMenuPolicy: Qt.ActionsContextMenu

    ActionItem {
      action: cutAction
    }

    ActionItem {
      action: copyAction
    }

    ActionItem {
      action: pasteAction
    }
  }

  StatusBar {
    Label {
      StatusBar.stretch: 2
      text: "Pos:"
    }
  }

  Component.onCompleted: textEdit.document = _editor.document
}
