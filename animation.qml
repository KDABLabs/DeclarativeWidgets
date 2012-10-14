import QtQuick 1.0
import QtGui 1.0

Widget {
  VBoxLayout {
    PushButton {
      id: button
      text: anim.running ? qsTr("Stop animation") : qsTr("Start animation")
      checkable: true
    }

    Slider {
      id: slider

      minimum: 0
      maximum: 100
      PropertyAnimation {
        id: anim

        running: button.checked
        target: slider
        property: "value"
        from: 0
        to: 100
        duration: 3000
        easing.type: Easing.InOutBounce
        loops: Animation.Infinite
      }
    }
  }
}
