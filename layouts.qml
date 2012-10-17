import QtGui 1.0

Widget {
  VBoxLayout {
    Widget {
      HBoxLayout {
        PushButton {
          HBoxLayout.stretch: 1
          text: "1"
        }
        PushButton {
          HBoxLayout.stretch: 1
          text: "1"
        }
        PushButton {
          HBoxLayout.stretch: 2
          text: "2"
        }
      }
    }
    Widget {
      HBoxLayout {
        Label {
          HBoxLayout.alignment: Qt.AlignRight
          text: "Top"
        }
        Label {
          HBoxLayout.alignment: Qt.AlignVCenter
          text: "VCenter"
        }
        Label {
          HBoxLayout.alignment: Qt.AlignBottom
          text: "Bottom"
        }
      }
    }

    HBoxLayout {
      VBoxLayout {
        Label {
          VBoxLayout.alignment: Qt.AlignLeft
          text: "Left"
        }
        Label {
          VBoxLayout.alignment: Qt.AlignHCenter
          text: "HCenter"
        }
        Label {
          VBoxLayout.alignment: Qt.AlignRight
          text: "Right"
        }
      }
      VBoxLayout {
        TextEdit {
          VBoxLayout.stretch: 1
        }
        TextEdit {
          VBoxLayout.stretch: 2
        }
      }
    }
  }
}
