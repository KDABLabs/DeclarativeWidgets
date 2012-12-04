import QtQuick 1.1

Rectangle {
  width: 600
  height: 400

  color: "lightsteelblue"

  Text {
    text: qsTr("Click anywhere on rectangle to clear text")
    
    anchors.top: parent.top
    anchors.horizontalCenter: parent.horizontalCenter

    font.pointSize: 24
  }

  Text {
    text: _textInput.text

    anchors.centerIn: parent

    font.pointSize: 48
  }

  MouseArea {
    anchors.fill: parent

    onClicked: _textInput.clear()
  }
}
