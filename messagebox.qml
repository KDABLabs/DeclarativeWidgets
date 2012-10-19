import QtGui 1.0

Widget {
  VBoxLayout {
    PushButton {
      text: "MessageBox instance"

      onClicked: messageBox.show()
    }

    PushButton {
      id: aboutButton
      text: "MessageBox::about"
      onClicked: MessageBox.about(aboutButton, "title", "text")
    }
    PushButton {
      text: "MessageBox::aboutQt"
      onClicked: MessageBox.aboutQt(0, "text")
    }
    PushButton {
      text: "MessageBox::critical"
      onClicked: {
        var button = MessageBox.critical(0, "title", "text")
        console.log("MessageBox.critical returned " + button)
      }
    }
    PushButton {
      text: "MessageBox::information"
      onClicked: {
        var button = MessageBox.information(0, "title", "text")
        console.log("MessageBox.information returned " + button)
      }
    }
    PushButton {
      text: "MessageBox::question"
      onClicked: {
        var button = MessageBox.question(0, "title", "text", MessageBox.Retry | MessageBox.Abort | MessageBox.Ignore, MessageBox.Abort)
        console.log("MessageBox.question returned " + button)
      }
    }
    PushButton {
      text: "MessageBox::warning"
      onClicked: {
        var button = MessageBox.warning(0, "title", "text", MessageBox.Ok | MessageBox.Cancel)
        console.log("MessageBox.warning returned " + button)
      }
    }
  }

  MessageBox {
    id: messageBox

    windowTitle: "MessageBox instance"
    text: "text"
    detailedText: "detailedText"
  }
}
