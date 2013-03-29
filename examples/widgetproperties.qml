import QtGui 1.0

Widget {
  id: root

  width: 1000
  height: 800

  PushButton {
    id: button

    x: 100
    y: 100
    height: 80

    text: "Button"

    onClicked: itemView.model = null
  }

  ComboBox {
    x: 100
    y: 200
    height: 80

  }

  SpinBox {
    x: button.x + button.width + 100
    y: button.y
    height: button.height
    width: root.width - x - 100
  }

  TextEdit {
    id: textEdit
    x: 100
    y: 300
    width: root.width - 2*x
    height: 200
  }

  TreeView {
    id: itemView

    x: 100
    y: textEdit.height + textEdit.y + 100

    width: root.width - 2*x
    height: root.height - y

    model: FileSystemModel {}

    onModelChanged: console.log ("model changed")
    header.showSortIndicator: true
  }
}
