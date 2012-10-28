import QtGui 1.0

Widget {
  id: mainWidget

  VBoxLayout {

    HBoxLayout {
      PushButton {
        text: qsTr("<")
        onClicked: webView.back()
      }

      PushButton {
        text: qsTr(">")
        onClicked: webView.forward()
      }

      LineEdit {
        id: urlInput
      }

      PushButton {
        text: qsTr("Go")
        onClicked: webView.url = urlInput.text
      }
    }

    WebView {
      id: webView

      onTitleChanged: mainWidget.windowTitle = title
      onUrlChanged: urlInput.text = url
    }
  }
}
