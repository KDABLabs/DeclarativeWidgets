/*
  Copyright (C) 2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

Widget {
  id: root

  width: 1000
  height: 800

  PushButton {
    id: button

    x: 100
    y: 100
    height: 80

    text: "Button"

    onClicked: itemView.model = null
  }

  ComboBox {
    x: 100
    y: 200
    height: 80

  }

  SpinBox {
    x: button.x + button.width + 100
    y: button.y
    height: button.height
    width: root.width - x - 100
  }

  TextEdit {
    id: textEdit
    x: 100
    y: 300
    width: root.width - 2*x
    height: 200
  }

  TreeView {
    id: itemView

    x: 100
    y: textEdit.height + textEdit.y + 100

    width: root.width - 2*x
    height: root.height - y

    model: FileSystemModel {}

    onModelChanged: console.log ("model changed")
    header.showSortIndicator: true
  }
}
