/*
  layouts.qml

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

import QtWidgets 1.0

TabWidget {
  width: 600
  height: 800

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

      Widget {
          HBoxLayout {
              Spacer {
                sizeHint: Qt.size(100, 50)

                horizontalSizePolicy: Spacer.Maximum
              }
              Label {
                text: "Label between spacers"
              }
              Spacer {
                sizeHint: Qt.size(20, 0)

                horizontalSizePolicy: Spacer.Fixed
              }
              Label {
                text: "Label after fixed spacer"

                HBoxLayout.stretch: 1
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

  Widget {
    TabWidget.label: "Contents Margins"

    GridLayout {
      Slider {
        id: marginSlider

        GridLayout.row: 0
        GridLayout.column: 0
        GridLayout.columnSpan: 2

        orientation: Qt.Horizontal
      }

      GroupBox {
        GridLayout.row: 1
        GridLayout.column: 0
        title: "HBox"

        HBoxLayout {
          contentsMargins {
            left: marginSlider.value
            top: marginSlider.value
            right: marginSlider.value
            bottom: marginSlider.value
          }

          TextEdit {}
        }
      }
      GroupBox {
        GridLayout.row: 1
        GridLayout.column: 1
        title: "VBox"

        HBoxLayout {
          contentsMargins {
            left: marginSlider.value
            top: marginSlider.value
            right: marginSlider.value
            bottom: marginSlider.value
          }

          TextEdit {}
        }
      }
      GroupBox {
        GridLayout.row: 2
        GridLayout.column: 0
        title: "Form"

        HBoxLayout {
          contentsMargins {
            left: marginSlider.value
            top: marginSlider.value
            right: marginSlider.value
            bottom: marginSlider.value
          }

          TextEdit {}
        }
      }
      GroupBox {
        GridLayout.row: 2
        GridLayout.column: 1
        title: "Grid"

        HBoxLayout {
          contentsMargins {
            left: marginSlider.value
            top: marginSlider.value
            right: marginSlider.value
            bottom: marginSlider.value
          }

          TextEdit {}
        }
      }
      GroupBox {
        GridLayout.row: 3
        GridLayout.column: 0
        title: "Stacked"

        HBoxLayout {
          contentsMargins {
            left: marginSlider.value
            top: marginSlider.value
            right: marginSlider.value
            bottom: marginSlider.value
          }

          TextEdit {}
        }
      }
    }
  }
}
