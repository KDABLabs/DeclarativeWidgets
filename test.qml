import QtQuick 1.0
import QtGui 1.0

Widget {
  windowTitle: qsTr("Cool Test App")
  size: Qt.size(300, 500)

  property int counter: 0

  function myFunc()
  {
    counter++;
  }

  Component.onCompleted: _timer.timeout.connect(myFunc)

  VBoxLayout {
    Label {
      text: "Hallo ASCII-safe Kevin!!! " + counter
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
      onClicked: {
        secondLabel.text = "Changed"
        counter++
      }
    }
    HBoxLayout {
      CheckBox {
        id: checkBox
      }
      Label {
        text: checkBox.checked ? "Is checked" : "Is not checked"
      }
    }
    TabWidget {
      Label {
        TabWidget.label: "Title 1"

        text: "Page 1"
      }
      Widget {
        TabWidget.label: "Title 2"

        ButtonGroup {
          buttons: [ button1, button2, button3, button4 ]
        }

        VBoxLayout {
          RadioButton {
            id: button1
            text: qsTr("Apple")
          }
          RadioButton {
            id: button2
            text: qsTr("Banana")
          }
          RadioButton {
            id: button3
            text: qsTr("Peach")
          }

          PushButton {
            id: button4
            checkable: true
            text: qsTr("Peas")
          }
        }
      }
      Label {
        TabWidget.label: "Title 3"

        text: "Page 3"
      }
    }
  }
}
