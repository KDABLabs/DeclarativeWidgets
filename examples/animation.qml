/*
  animation.qml

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Tobias Koenig <tobias.koenig@kdab.com>
  Author: Kevin Krammer <kevin.krammer@kdab.com>

  Licensees holding valid commercial KDAB DeclarativeWidgets licenses may use this file in
  accordance with DeclarativeWidgets Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import QtWidgets 1.0

Widget {
  width: 600
  height: 200

  GridLayout {

    PushButton {
      id: button
      text: anim.running ? qsTr( "Stop animation" ) : qsTr( "Start animation" )
      checkable: true

      GridLayout.row: 0
      GridLayout.column: 0
      GridLayout.columnSpan: 3
    }

    PushButton {
      id: pulsingButton
      text: "Pulsing"

      property int delta: 0;
      property variant origGeometry: geometry;

      geometry: Qt.rect( origGeometry.x - delta, origGeometry.y - delta,
                         origGeometry.width + 2*delta, origGeometry.height + 2*delta )


      GridLayout.row: 1
      GridLayout.column: 1

      SequentialAnimation {
        running: button.checked
        loops: Animation.Infinite
        onRunningChanged: {
          if (running) {
            // save geometry at begin of animation
            pulsingButton.origGeometry = pulsingButton.geometry;
          }
        }
        NumberAnimation {
          target: pulsingButton
          property: "delta"
          from: 0
          to: 10
          duration: 500
          easing.type: Easing.InOutQuad
        }
        NumberAnimation {
          target: pulsingButton
          property: "delta"
          from: 10
          to: 0
          duration: 500
          easing.type: Easing.InOutQuad
        }
      }
    }

    PushButton {
      id: bouncingButton
      text: "Bouncing"

      property int delta: 0;
      property variant origGeometry: geometry;

      geometry: Qt.rect( origGeometry.x, origGeometry.y - delta,
                         origGeometry.width, origGeometry.height )

      GridLayout.row: 1
      GridLayout.column: 2

      SequentialAnimation {
        running: button.checked
        loops: Animation.Infinite
        onRunningChanged: {
          if (running) {
            // save geometry at begin of animation
            bouncingButton.origGeometry = bouncingButton.geometry;
          }
        }
        NumberAnimation {
          target: bouncingButton
          property: "delta"
          from: 0
          to: 50
          duration: 500
          easing.type: Easing.OutQuad
        }
        NumberAnimation {
          target: bouncingButton
          property: "delta"
          from: 50
          to: 0
          duration: 500
          easing.type: Easing.OutBounce
        }
      }
    }

    Slider {
      id: slider

      orientation: Qt.Horizontal
      minimum: 0
      maximum: 100

      GridLayout.row: 2
      GridLayout.column: 0
      GridLayout.columnSpan: 3

      SequentialAnimation {
        id: anim
        running: button.checked
        loops: Animation.Infinite

        PropertyAnimation {
          target: slider
          property: "value"
          from: slider.minimum
          to: slider.maximum
          duration: 1500
          easing.type: Easing.InOutQuad
        }
        PropertyAnimation {
          target: slider
          property: "value"
          from: slider.maximum
          to: slider.minimum
          duration: 1500
          easing.type: Easing.InOutQuad
        }
      }
    }

    Label {
      id: marqueeLabel

      GridLayout.row: 3
      GridLayout.column: 0
      GridLayout.columnSpan: 3

      SequentialAnimation {
        running: button.checked
        loops: Animation.Infinite
        onRunningChanged: {
          if (running) {
            marqueeLabel.maximumWidth = slider.width;
            marqueeLabel.text = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr"
          }
        }

        PauseAnimation {
          duration: 3000
        }
        NumberAnimation {
          target: marqueeLabel
          property: "indent"
          from: marqueeLabel.width
          to: 0
          duration: 3000
        }
      }
    }
  }
}
