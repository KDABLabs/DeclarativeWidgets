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

      RadioButton {
        text: qsTr("RadioButton")
      }

      CheckBox {
        text: qsTr("CheckBox")
      }

      CommandLinkButton {
        text: qsTr("CommandLinkButton")
        description: qsTr("A short description")
      }

      DialogButtonBox {
        standardButtons: DialogButtonBox.Save | DialogButtonBox.Cancel
      }
    }
  }

  Widget {
    TabWidget.label: "ItemViews"

    VBoxLayout {
      ListView {
        model: _fileSystemModel
      }
      TreeView {
        model: _fileSystemModel
      }
      TableView {
        model: _fileSystemModel
      }
      ColumnView {
        model: _fileSystemModel
      }
    }
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
      StackedWidget {
        Label {
          text: "Page 1"
        }
        Label {
          text: "Page 2"
        }
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

      SpinBox {}

      DoubleSpinBox {}

      TimeEdit {}

      DateEdit {}

      DateTimeEdit {}

      Dial {}

      ScrollBar {
        minimum: 0
        maximum: 100
        value: 50
        orientation: Qt.Horizontal
      }

      Slider {
        minimum: 0
        maximum: 100
        value: 50
        orientation: Qt.Horizontal
      }
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

      LCDNumber {
        value: 42
      }

      ProgressBar {
        minimum: 0
        maximum: 100
        value: 42
        textVisible: true
      }

      WebView {
        url: "http://www.kdab.com"
      }
    }
  }
}
