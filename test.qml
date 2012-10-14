import QtQuick 1.0
import qtgui.widgets 1.0

Widget {
  VBoxLayout {
    Label {
      text: "Hallo ASCII-safe Kevin!!!"
    }
    Label {
      id: secondLabel
      text: "Wie geht es"
    }
    Label {
      id: lastLabel
      text: secondLabel.text
    }
    Label {
      id: urlLabel
      text: "Hallo <a href=\"http://www.kde.org\">Welt</a>"

      onLinkActivated: console.log("link=" + link)
    }
    PushButton {
      text: "Click me"
      onClicked: secondLabel.text = "Changed"
    }
  }
}
