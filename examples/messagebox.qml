import QtGui 1.0

Widget {
  VBoxLayout {
    PushButton {
      text: qsTr("MessageBox instance")

      onClicked: messageBox.show()
    }

    PushButton {
      id: aboutButton
      text: qsTr("MessageBox::about")
      onClicked: {
        MessageBox.parent = aboutButton
        MessageBox.about(qsTr("About DeclarativeWidgets"), qsTr("This is a text about declarative widgets."))
      }
    }

    PushButton {
      text: qsTr("MessageBox::aboutQt")
      onClicked: MessageBox.aboutQt()
    }

    PushButton {
      text: qsTr("MessageBox::aboutQt with title")
      onClicked: MessageBox.aboutQt(qsTr("About Qt message box"))
    }

    PushButton {
      text: qsTr("MessageBox::critical")
      onClicked: {
        var button = MessageBox.critical(qsTr("Error"), qsTr("An error occurred!"))
        console.log("MessageBox.critical returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::information")
      onClicked: {
        var button = MessageBox.information(qsTr("Information"), qsTr("The taxi is here"))
        console.log("MessageBox.information returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::question")
      onClicked: {
        MessageBox.buttons = MessageBox.Retry | MessageBox.Abort | MessageBox.Ignore
        var button = MessageBox.question(qsTr("Network error"), qsTr("Can not connect to host"))
        console.log("MessageBox.question returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::question with default abort")
      onClicked: {
        MessageBox.buttons = MessageBox.Retry | MessageBox.Abort | MessageBox.Ignore
        MessageBox.defaultButton = MessageBox.Abort
        var button = MessageBox.question(qsTr("Network error"), qsTr("Can not connect to host"))
        console.log("MessageBox.question returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::warning")
      onClicked: {
        MessageBox.buttons = MessageBox.Ok | MessageBox.Cancel
        var button = MessageBox.warning(0, qsTr("Warning"), qsTr("Do you really want to quit?"))
        console.log("MessageBox.warning returned " + button)
      }
    }
  }

  MessageBox {
    id: messageBox

    windowTitle: qsTr("MessageBox instance")
    text: qsTr("text")
    detailedText: qsTr("detailedText")
  }
}
