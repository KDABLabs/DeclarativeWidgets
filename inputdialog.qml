import QtGui 1.0

Widget {
  VBoxLayout {
    PushButton {
      text: "InputDialog::getDouble"
      onClicked: {
        var value = InputDialog.getDouble(0, "Double Input", "A Double number")
        console.log("InputDialog.getDouble returned " + value)
      }
    }

    PushButton {
      text: "InputDialog::getInt"
      onClicked: {
        var value = InputDialog.getInt(0, "Integer Input", "An Integer number")
        console.log("InputDialog.getInt returned " + value)
      }
    }

    PushButton {
      text: "InputDialog::getItem"
      onClicked: {
        var items = [ "Item 1", "Item 2", "Item 3"]
        var item = InputDialog.getItem(0, "Item Selection", "Select an item", items)
        console.log("InputDialog.getItem returned " + item)
      }
    }

    PushButton {
      text: "InputDialog::getText"
      onClicked: {
        var text = InputDialog.getText(0, "Text Input", "Any text")
        console.log("InputDialog.getText returned " + text)
      }
    }
  }
}
