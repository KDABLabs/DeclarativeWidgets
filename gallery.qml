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
  }
}
