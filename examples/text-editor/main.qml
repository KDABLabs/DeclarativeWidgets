import QtQuick 1.0
import QtGui 1.0

MainWindow {
  id: mainWindow

  windowTitle: textEdit.modified ? qsTr("Declarative Widget Editor *modified*") : qsTr("Declarative Widget Editor")
  windowIcon: _editor.iconFromFile(":/editor.png")

  size: Qt.size(800, 600)

  MenuBar {
    Menu {
      title: qsTr("File")

      Action {
        id: newAction
        text: qsTr("New")
        icon: _editor.iconFromTheme("document-new");
        onTriggered: _editor.newDocument()
      }

      Action {
        id: openAction
        text: qsTr("Open")
        icon: _editor.iconFromTheme("document-open")
        onTriggered: {
          FileDialog.nameFilters = [ qsTr("Plain text files (*.txt)"), qsTr("All files (*.*)") ]
          var fileName = FileDialog.getOpenFileName()
          if (fileName.length > 0)
            _editor.open(fileName);
        }
      }

      Action {
        id: saveAction
        text: qsTr("Save")
        icon: _editor.iconFromTheme("document-save")
        onTriggered: _editor.save()
      }

      Separator {}

      Action {
        text: qsTr("Print")
        icon: _editor.iconFromTheme("document-print")
      }

      Separator {}

      Action {
        text: qsTr("Close")
        icon: _editor.iconFromTheme("application-exit")
        onTriggered: mainWindow.close()
      }
    }

    Menu {
      title: qsTr("Edit")

      Action {
        id: undoAction
        text: qsTr("Undo")
        icon: _editor.iconFromTheme("edit-undo")
        onTriggered: textEdit.undo()
      }

      Action {
        id: redoAction
        text: qsTr("Redo")
        icon: _editor.iconFromTheme("edit-redo")
        onTriggered: textEdit.redo()
      }

      Separator {}

      Action {
        id: cutAction
        text: qsTr("Cut")
        icon: _editor.iconFromTheme("edit-cut")
        onTriggered: textEdit.cut()
      }

      Action {
        id: copyAction
        text: qsTr("Copy")
        icon: _editor.iconFromTheme("edit-copy")
        onTriggered: textEdit.copy()
      }

      Action {
        id: pasteAction
        text: qsTr("Paste")
        icon: _editor.iconFromTheme("edit-paste")
        onTriggered: textEdit.paste()
      }

      Separator {}

      Action {
        text: qsTr("Select All")
        icon: _editor.iconFromTheme("edit-select-all")
        onTriggered: textEdit.selectAll()
      }
    }

    Menu {
      title: qsTr("View")

      Action {
        text: qsTr("Enlarge Font")
        icon: _editor.iconFromTheme("zoom-in")
        onTriggered: textEdit.zoomIn()
      }

      Action {
        text: qsTr("Shrink Font")
        icon: _editor.iconFromTheme("zoom-out")
        onTriggered: textEdit.zoomOut()
      }
    }

    Menu {
      title: qsTr("Help")

      Action {
        text: qsTr("About")
        icon: mainWindow.windowIcon
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

    ActionItem {
      action: openAction
    }

    ActionItem {
      action: saveAction
    }
  }

  ToolBar {
    ActionItem {
      action: undoAction
    }

    ActionItem {
      action: redoAction
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

  Component.onCompleted: {
    textEdit.document = _editor.document
    _editor.requestSaveFileName.connect(askForSaveFileName)
  }

  function askForSaveFileName() {
    var fileName = FileDialog.getSaveFileName()
    if (fileName.length > 0) {
      _editor.fileName = fileName
      _editor.save()
    }
  }
}
