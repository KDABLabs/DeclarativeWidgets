import QtQuick 1.1

Rectangle {
  width: 600
  height: 400

  color: "lightsteelblue"

  Text {
    text: qsTr("Click anywhere on rectangle to clear text")
    
    anchors.top: parent.top
    anchors.horizontalCenter: parent.horizontalCenter
  }

  TextInput {
    text: _textInput.text

    onTextChanged: _textInput.text = text

    anchors.centerIn: parent
  }

  MouseArea {
    anchors.fill: parent

    onClicked: _textInput.clear()
  }
}
