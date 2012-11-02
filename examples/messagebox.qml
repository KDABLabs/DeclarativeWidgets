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
      onClicked: MessageBox.about(aboutButton, qsTr("About DeclarativeWidgets"), qsTr("This is a text about declarative widgets."))
    }

    PushButton {
      text: qsTr("MessageBox::aboutQt")
      onClicked: MessageBox.aboutQt(0, qsTr("About Qt"))
    }

    PushButton {
      text: qsTr("MessageBox::critical")
      onClicked: {
        var button = MessageBox.critical(0, qsTr("Error"), qsTr("An error occurred!"))
        console.log("MessageBox.critical returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::information")
      onClicked: {
        var button = MessageBox.information(0, qsTr("Information"), qsTr("The taxi is here"))
        console.log("MessageBox.information returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::question")
      onClicked: {
        var button = MessageBox.question(0, qsTr("Network error"), qsTr("Can not connect to host"), MessageBox.Retry | MessageBox.Abort | MessageBox.Ignore, MessageBox.Abort)
        console.log("MessageBox.question returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::warning")
      onClicked: {
        var button = MessageBox.warning(0, qsTr("Warning"), qsTr("Do you really want to quit?"), MessageBox.Ok | MessageBox.Cancel, MessageBox.Ok)
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
