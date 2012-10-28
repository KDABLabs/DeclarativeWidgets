import QtGui 1.0

TabWidget {
  windowTitle: qsTr("Widget Gallery")
  size: Qt.size(700, 500)

  Widget {
    TabWidget.label: "Buttons"

    VBoxLayout {
      PushButton {
        text: qsTr("PushButton")
      }

      ToolButton {
        text: qsTr("ToolButton")
      }

      CheckBox {
        text: qsTr("CheckBox")
      }

      DialogButtonBox {
        standardButtons: DialogButtonBox.Save | DialogButtonBox.Cancel
      }
    }
  }

  Widget {
    TabWidget.label: "ItemViews"
  }

  Widget {
    TabWidget.label: "Containers"

    VBoxLayout {
      GroupBox {
        title: "GroupBox"
        minimumWidth: 100
        minimumHeight: 100
      }
      Frame {
        frameShape: Frame.Panel
        frameShadow: Frame.Sunken
        minimumWidth: 100
        minimumHeight: 100
      }
    }
  }

  Widget {
    TabWidget.label: "Input Widgets"

    VBoxLayout {
      LineEdit {
        text: qsTr("LineEdit")
        onTextChanged: console.log("Types: " + text)
      }

      TextEdit {
        plainText: qsTr("TextEdit")
      }

      PlainTextEdit {
        plainText: qsTr("PlainTextEdit")
      }

      TimeEdit {}

      DateEdit {}

      DateTimeEdit {}

      Slider {}
    }
  }

  Widget {
    TabWidget.label: "Display Widgets"

    VBoxLayout {
      Label {
        text: qsTr("Label")
      }

      TextBrowser {
        openExternalLinks: true
        html: "<html><body>TextBrowser <a href=\"http://www.kde.org\">Coolest project ever</a></body></html>"
      }

      CalendarWidget {}

      WebView {
        url: "http://www.kdab.com"
      }
    }
  }
}
