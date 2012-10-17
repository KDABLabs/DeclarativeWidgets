import QtGui 1.0

MainWindow {

  MenuBar {
    Menu {
      title: qsTr("File")

      Action {
        text: "Close"
      }
    }

    Menu {
      title: qsTr("Edit")

      Action {
        text: "Copy"
      }

      Action {
        text: "Paste"
      }
    }

    Menu {
      title: qsTr("Help")

      Action {
        text: "About"
      }

      Action {
        text: "About Qt"
      }
    }
  }

  TextEdit {
    id: textEdit
  }
}
