/*
  dialogs.qml

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

import QtWidgets 1.0

Widget {
  ColorDialog {
    id: colorDialog
  }

  FileDialog {
    id: fileDialog

    fileMode: FileDialog.ExistingFile
    viewMode: FileDialog.List
  }

  FontDialog {
    id: fontDialog
  }

  VBoxLayout {
    PushButton {
      text: qsTr("InputDialog::getInt()")
      onClicked: {
        var value = InputDialog.getInt()
        console.log("InputDialog.getInt returned " + value)
      }
    }

    PushButton {
      text: qsTr("InputDialog::getInt() with options")
      onClicked: {
        InputDialog.title = qsTr("Integer Input")
        InputDialog.label = qsTr("Percentage...")
        InputDialog.value = 25
        InputDialog.min = 0
        InputDialog.max = 100
        InputDialog.step = 10
        var value = InputDialog.getInt()
        console.log("InputDialog.getInt " + (InputDialog.ok ? "returned " + value : "was cancelled"))
      }
    }

    PushButton {
      text: qsTr("InputDialog::getDouble()")
      onClicked: {
        var value = InputDialog.getDouble()
        console.log("InputDialog.getDouble returned " + value)
      }
    }

    PushButton {
      text: qsTr("InputDialog::getDouble() with options")
      onClicked: {
        InputDialog.title = qsTr("Double Input")
        InputDialog.label = qsTr("Amount:")
        InputDialog.value = 37.56
        InputDialog.decimals = 2
        var value = InputDialog.getDouble()
        console.log("InputDialog.getDouble " + (InputDialog.ok ? "returned " + value : "was cancelled"))
      }
    }

    PushButton {
      text: qsTr("InputDialog::getItem()")
      onClicked: {
        var items = [ qsTr("Spring"), qsTr("Summer"), qsTr("Autumn"), qsTr("Winter") ]
        var item = InputDialog.getItem(items)
        console.log("InputDialog.getItem returned " + item)
      }
    }

    PushButton {
      text: qsTr("InputDialog::getItem() with options")
      onClicked: {
         InputDialog.title = qsTr("Item Selection")
        InputDialog.label = qsTr("Season:")
        InputDialog.current = 2
        var items = [ qsTr("Spring"), qsTr("Summer"), qsTr("Autumn"), qsTr("Winter") ]
        var item = InputDialog.getItem(items)
        console.log("InputDialog.getItem " + (InputDialog.ok ? "returned " + item : "was cancelled"))
      }
    }

    PushButton {
      text: qsTr("InputDialog::getText()")
      onClicked: {
        var text = InputDialog.getText()
        console.log("InputDialog.getText returned " + text)
      }
    }

    PushButton {
      text: qsTr("InputDialog::getText() with options")
      onClicked: {
        InputDialog.title = qsTr("Text Input")
        InputDialog.label = qsTr("Password:")
        InputDialog.echoMode = LineEdit.Password
        InputDialog.text = "secret"
        var text = InputDialog.getText()
        console.log("InputDialog.getText " + (InputDialog.ok ? "returned " + text : "was cancelled"))
      }
    }

    PushButton {
      text: qsTr("Color Dialog...")
      onClicked: {
        if (colorDialog.exec())
          console.log("Selected color: " + colorDialog.currentColor)
      }
    }

    PushButton {
      text: qsTr("Color Dialog::getColor")
      onClicked: {
        console.log("Selected color: " + ColorDialog.getColor())
      }
    }

    PushButton {
      text: qsTr("Color Dialog::getColor with initial color")
      onClicked: {
        console.log("Selected color: " + ColorDialog.getColor("#ff0000"))
      }
    }

    PushButton {
      text: qsTr("Color Dialog::getColor with title")
      onClicked: {
        ColorDialog.title = "Pick a color"
        console.log("Selected color: " + ColorDialog.getColor())
      }
    }

    PushButton {
      text: qsTr("Color Dialog::getColor with options")
      onClicked: {
        ColorDialog.options = ColorDialog.NoButtons | ColorDialog.ShowAlphaChannel
        console.log("Selected color: " + ColorDialog.getColor())
      }
    }

    PushButton {
      text: qsTr("File Dialog...")
      onClicked: {
        if (fileDialog.exec())
          console.log("Selected files: " + fileDialog.selectedFiles)
      }
    }

    PushButton {
      text: qsTr("Font Dialog...")
      onClicked: {
        if (fontDialog.exec())
          console.log("Selected font: " + fontDialog.currentFont)
      }
    }

    PushButton {
      text: qsTr("Font Dialog::getFont")
      onClicked: {
          var font = FontDialog.getFont()
          console.log("FontDialog.getFont " + (FontDialog.ok ? "returned " + font : "was cancelled"))
      }
    }

    PushButton {
      text: qsTr("Font Dialog::getFont with initial")
      onClicked: {
          var font = FontDialog.getFont(Qt.fontFamilies()[0])
          console.log("FontDialog.getFont " + (FontDialog.ok ? "returned " + font : "was cancelled"))
      }
    }

    PushButton {
      text: qsTr("Font Dialog::getFont with title")
      onClicked: {
          FontDialog.title = "Pick a font"
          var font = FontDialog.getFont()
          console.log("FontDialog.getFont " + (FontDialog.ok ? "returned " + font : "was cancelled"))
      }
    }

    PushButton {
      text: qsTr("Font Dialog::getFont with options")
      onClicked: {
          FontDialog.options = FontDialog.NoButtons
          var font = FontDialog.getFont()
          console.log("FontDialog.getFont " + (FontDialog.ok ? "returned " + font : "was cancelled"))
      }
    }

  }
}
