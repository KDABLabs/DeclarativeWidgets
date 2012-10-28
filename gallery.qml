import QtGui 1.0

Widget {
  VBoxLayout
  {
    CalendarWidget {}
    LineEdit {
      onTextChanged: console.log("Types: " + text)
    }
    Frame {
      frameShape: Frame.Panel
      frameShadow: Frame.Sunken
      minimumWidth: 100
      minimumHeight: 100
    }
    GroupBox {
      title: qsTr("Hello World")
      minimumWidth: 100
      minimumHeight: 100
    }
    PlainTextEdit {
      plainText: qsTr("Hello World")
    }
  }
}
