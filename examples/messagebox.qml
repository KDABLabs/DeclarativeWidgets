/*
  messagebox.qml

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

Widget {
  VBoxLayout {
    PushButton {
      text: qsTr("MessageBox instance")

      onClicked: messageBox.show()
    }

    PushButton {
      id: aboutButton
      text: qsTr("MessageBox::about")
      onClicked: {
        MessageBox.parent = aboutButton
        MessageBox.about(qsTr("About DeclarativeWidgets"), qsTr("This is a text about declarative widgets."))
      }
    }

    PushButton {
      text: qsTr("MessageBox::aboutQt")
      onClicked: MessageBox.aboutQt()
    }

    PushButton {
      text: qsTr("MessageBox::aboutQt with title")
      onClicked: MessageBox.aboutQt(qsTr("About Qt message box"))
    }

    PushButton {
      text: qsTr("MessageBox::critical")
      onClicked: {
        var button = MessageBox.critical(qsTr("Error"), qsTr("An error occurred!"))
        console.log("MessageBox.critical returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::information")
      onClicked: {
        var button = MessageBox.information(qsTr("Information"), qsTr("The taxi is here"))
        console.log("MessageBox.information returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::question")
      onClicked: {
        MessageBox.buttons = MessageBox.Retry | MessageBox.Abort | MessageBox.Ignore
        var button = MessageBox.question(qsTr("Network error"), qsTr("Can not connect to host"))
        console.log("MessageBox.question returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::question with default abort")
      onClicked: {
        MessageBox.buttons = MessageBox.Retry | MessageBox.Abort | MessageBox.Ignore
        MessageBox.defaultButton = MessageBox.Abort
        var button = MessageBox.question(qsTr("Network error"), qsTr("Can not connect to host"))
        console.log("MessageBox.question returned " + button)
      }
    }

    PushButton {
      text: qsTr("MessageBox::warning")
      onClicked: {
        MessageBox.buttons = MessageBox.Ok | MessageBox.Cancel
        var button = MessageBox.warning(0, qsTr("Warning"), qsTr("Do you really want to quit?"))
        console.log("MessageBox.warning returned " + button)
      }
    }
  }

  MessageBox {
    id: messageBox

    windowTitle: qsTr("MessageBox instance")
    text: qsTr("text")
    detailedText: qsTr("detailedText")
  }
}
