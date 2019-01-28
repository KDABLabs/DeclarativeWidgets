/*
  Shop.qml

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

Column {
  Text {
    text: qsTr("Currently available books")
    horizontalAlignment: Qt.AlignHCenter
    font.pointSize: 24
  }

  ListView {
    id: listView

    width: 800
    height: 600
    model: _store.bookList;
    highlightFollowsCurrentItem: true

    delegate: Column {
      property real price: bookPrice
      property string notes: bookNotes

      Text {
        text: bookTitle
        font.pointSize: 16
      }
      Text {
        text: qsTr("by %1, %2").arg(authorLastName).arg(authorFirstName)
      }
    }

    highlight: Rectangle {
      color: "#ADD8E6"

      width: listView.width
      height: listView.currentItem.height
      y: listView.currentItem.y
    }
  }

  Text {
    property real price: listView.currentIndex >= 0 ? listView.currentItem.price : 0

    text: qsTr("Price: %1").arg(price)
    horizontalAlignment: Qt.AlignHCenter
    font.pointSize: 24
  }
  Text {
    property string notes: listView.currentIndex >= 0 ? listView.currentItem.notes : qsTr("N/A")

    text: qsTr("Notes: %1").arg(notes)
    horizontalAlignment: Qt.AlignHCenter
  }
}
