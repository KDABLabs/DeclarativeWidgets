/*
  GridLayoutTest.qml

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2017-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Nathan Collins <nathan.collins@kdab.com>

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

Widget {
  GridLayout {
    PushButton {
        text: "Num"

        GridLayout.row: 0
        GridLayout.column: 0
    }
    PushButton {
        text: "/"

        GridLayout.row: 0
        GridLayout.column: 1
    }
    PushButton {
        text: "*"

        GridLayout.row: 0
        GridLayout.column: 2
    }
    PushButton {
        text: "-"

        GridLayout.row: 0
        GridLayout.column: 3
    }
    PushButton {
        text: "7"

        GridLayout.row: 1
        GridLayout.column: 0
    }
    PushButton {
        text: "8"

        GridLayout.row: 1
        GridLayout.column: 1
    }
    PushButton {
        text: "9"

        GridLayout.row: 1
        GridLayout.column: 2
    }
    PushButton {
        text: "+"
        sizePolicy {
            horizontalPolicy: SizePolicy.Minimum
            verticalPolicy: SizePolicy.Minimum
        }

        GridLayout.row: 1
        GridLayout.column: 3
        GridLayout.rowSpan: 2
    }
    PushButton {
        text: "4"

        GridLayout.row: 2
        GridLayout.column: 0
    }
    PushButton {
        text: "5"

        GridLayout.row: 2
        GridLayout.column: 1
    }
    PushButton {
        text: "6"

        GridLayout.row: 2
        GridLayout.column: 2
    }
    PushButton {
        text: "1"

        GridLayout.row: 3
        GridLayout.column: 0
    }
    PushButton {
        text: "2"

        GridLayout.row: 3
        GridLayout.column: 1
    }
    PushButton {
        text: "3"

        GridLayout.row: 3
        GridLayout.column: 2
    }
    PushButton {
        text: "Enter"
        sizePolicy {
            horizontalPolicy: SizePolicy.Minimum
            verticalPolicy: SizePolicy.Minimum
        }

        GridLayout.row: 3
        GridLayout.column: 3
        GridLayout.rowSpan: 2
    }
    PushButton {
        text: "0"

        GridLayout.row: 4
        GridLayout.column: 0
        GridLayout.columnSpan: 2
    }
    PushButton {
        text: "."

        GridLayout.row: 4
        GridLayout.column: 2
    }
  }
}
