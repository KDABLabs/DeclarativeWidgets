/*
  test.qml

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

import QtCore 1.0
import QtWidgets 1.0

Widget {
  windowTitle: qsTr("Cool Test App")
  size: Qt.size(300, 500)


  property int counter: 0

  function myFunc()
  {
    counter++;
  }

  Timer {
    id: timer
    interval: 1000
    onTimeout: myFunc()
  }

  VBoxLayout {
    Label {
      text: "Hallo ASCII-safe Kevin!!! " + counter
    }
    PushButton {
      text: "Run Timer"
      checkable: true
      onToggled: checked ? timer.start() : timer.stop()
    }
    Label {
      id: secondLabel
      text: "Wie geht es"
    }
    Label {
      id: lastLabel
      text: secondLabel.text
    }
    Label {
      id: urlLabel
      text: "Hallo <a href=\"http://www.kde.org\">Welt</a>"

      onLinkActivated: console.log("link=" + link)
    }
    PushButton {
      text: "Click me"
      onClicked: {
        secondLabel.text = "Changed"
        counter++
      }
    }
    HBoxLayout {
      CheckBox {
        id: checkBox
      }
      Label {
        text: checkBox.checked ? "Is checked" : "Is not checked"
      }
    }
    TabWidget {
      Label {
        TabWidget.label: qsTr("Title 1")

        text: "Page 1"
      }
      Widget {
        TabWidget.label: "Title 2"

        ButtonGroup {
          buttons: [ button1, button2, button3, button4 ]
        }

        VBoxLayout {
          RadioButton {
            id: button1
            text: qsTr("Apple")
          }
          RadioButton {
            id: button2
            text: qsTr("Banana")
          }
          RadioButton {
            id: button3
            text: qsTr("Peach")
          }

          PushButton {
            id: button4
            checkable: true
            text: qsTr("Peas")
          }
        }
      }
      Label {
        TabWidget.label: "Title 3"

        text: "Page 3"
      }
    }
  }
}
