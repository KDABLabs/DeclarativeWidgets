import QtGui 1.0

Widget {
  VBoxLayout {
    HBoxLayout {
      Label {
        text: qsTr("Source:")
      }

      LineEdit {
        id: sourceInput

        placeholderText: qsTr("Please enter URL of a QtQuick1 QML file")

        onEditingFinished: setSource()

        function setSource() {
          declarativeView.source = text
        }
      }

      PushButton {
        text: qsTr("Choose...");

        onClicked: {
          FileDialog.nameFilters = [ qsTr("QML files (*.qml)"), qsTr("All Files (*.*)") ]
          var file = FileDialog.getOpenFileName();

          if (file.length > 0) {
            sourceInput.text = "file://" + file;
            sourceInput.setSource();
          }
        }
      }
    }

    DeclarativeView {
      id: declarativeView

      VBoxLayout.stretch: 1

      rootContext: DeclarativeContext {
        DeclarativeContextProperty {
          name: "_textInput"
          value: textInput
        }
      }
    }

    LineEdit {
      id: textInput

      placeholderText: qsTr("Type any text here")
    }
  }
}
