import QtGui 1.0

Widget {
  VBoxLayout
  {
    CalendarWidget {}
    LineEdit {
      onTextChanged: console.log("Types: " + text)
    }
  }
}
