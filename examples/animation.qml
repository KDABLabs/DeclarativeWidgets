/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

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
