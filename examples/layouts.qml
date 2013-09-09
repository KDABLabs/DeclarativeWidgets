/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com
  Author: Tobias Koenig, tobias.koenig@kdab.com

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

import QtWidgets 1.0

TabWidget {
  Widget {
    TabWidget.label: "Box Layouts"

    VBoxLayout {
      Widget {
        HBoxLayout {
          PushButton {
            HBoxLayout.stretch: 1
            text: "1"
          }
          PushButton {
            HBoxLayout.stretch: 1
            text: "1"
          }
          PushButton {
            HBoxLayout.stretch: 2
            text: "2"
          }
        }
      }
      Widget {
        HBoxLayout {
          Label {
            HBoxLayout.alignment: Qt.AlignTop
            text: "Top"
          }
          Label {
            HBoxLayout.alignment: Qt.AlignVCenter
            text: "VCenter"
          }
          Label {
            HBoxLayout.alignment: Qt.AlignBottom
            text: "Bottom"
          }
          Label { // just for increasing the parent's height
            text: "\n\n\n"
          }
        }
      }

      HBoxLayout {
        VBoxLayout {
          Label {
            VBoxLayout.alignment: Qt.AlignLeft
            text: "Left"
          }
          Label {
            VBoxLayout.alignment: Qt.AlignHCenter
            text: "HCenter"
          }
          Label {
            VBoxLayout.alignment: Qt.AlignRight
            text: "Right"
          }
        }
        VBoxLayout {
          TextEdit {
            VBoxLayout.stretch: 1
          }
          TextEdit {
            VBoxLayout.stretch: 2
          }
        }
      }
    }
  }

  Widget {
    TabWidget.label: "Form Layout"

    VBoxLayout {
      FormLayout {
        PushButton {
          FormLayout.label: "Label 1"
          text: "Row 1"
        }
        CheckBox {
          FormLayout.label: qsTr("Label 2")
          text: "Row 2"
        }
      }
      FormLayout {
        HBoxLayout {
          FormLayout.label: "Label 1"

          Label {
            text: "row"
          }
          Label {
            text: "1"
          }
        }
        HBoxLayout {
          Label {
            text: "row"
          }
          Label {
            text: "2"
          }
        }
      }
    }
  }
  Widget {
    TabWidget.label: "Grid Layout"

    GridLayout {
      PushButton {
        GridLayout.row: 0
        GridLayout.column: 0

        text: "0/0"
      }
      PushButton {
        GridLayout.row: 0
        GridLayout.column: 2

        text: "0/2"
      }
      PushButton {
        GridLayout.row: 1
        GridLayout.column: 0

        text: "1/0"
      }
      PushButton {
        GridLayout.row: 1
        GridLayout.column: 1
        GridLayout.columnSpan: 2

        text: "1/1, 1/2"
      }
      TextEdit {
        GridLayout.row: 2
        GridLayout.column: 0
        GridLayout.columnSpan: 2
        GridLayout.rowSpan: 2

        plainText: "2/0, 2/2"
      }
      PushButton {
        GridLayout.row: 2
        GridLayout.column: 2
        GridLayout.alignment: Qt.AlignBottom

        text: "2/2"
      }
      PushButton {
        GridLayout.row: 3
        GridLayout.column: 2
        GridLayout.alignment: Qt.AlignTop

        text: "3/2"
      }
    }
  }

  Widget {
    TabWidget.label: "Stacked Layout"
    VBoxLayout {
      PushButton {
        text: "Next Page"
        onClicked: {
          stackedLayout.currentIndex = ((stackedLayout.currentIndex + 1) % stackedLayout.count)
        }
      }
      StackedLayout {
        id: stackedLayout
        Label {
          text: "Page 1"
        }
        Label {
          text: "Page 2"
        }
        Label {
          text: "Page 3"
        }
      }
    }
  }
}
