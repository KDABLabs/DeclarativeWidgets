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

import QtGui 1.0

Widget {
  VBoxLayout {
    PushButton {
      text: "FileDialog::getExistingDirectory"
      onClicked: {
        var file = FileDialog.getExistingDirectory()
        console.log("FileDialog.getExistingDirectory returned " + file)
      }
    }
    PushButton {
      text: "FileDialog::getExistingDirectory non-native dialog"
      onClicked: {
        FileDialog.options = FileDialog.ShowDirsOnly | FileDialog.DontUseNativeDialog
        var file = FileDialog.getExistingDirectory()
        console.log("FileDialog.getExistingDirectory returned " + file)
      }
    }
    PushButton {
      text: "FileDialog::getOpenFileName"
      onClicked: {
        var file = FileDialog.getOpenFileName()
        console.log("FileDialog.getOpenFileName returned " + file)
      }
    }
    PushButton {
      text: "FileDialog::getOpenFileName, with options"
      onClicked: {
        FileDialog.caption = "Select a file to open";
        FileDialog.nameFilters = [ "Headers (*.h)", "Sources (*.cpp)", "All Files (*.*)" ]
        var file = FileDialog.getOpenFileName()
        console.log("FileDialog.getOpenFileName returned " + file)
        console.log("Selected filter " + FileDialog.selectedFilter)
      }
    }
    PushButton {
      text: "FileDialog::getOpenFileNames"
      onClicked: {
        var files = FileDialog.getOpenFileNames()
        console.log("FileDialog.getOpenFileNames returned " + files)
      }
    }
    PushButton {
      text: "FileDialog::getSaveFileName"
      onClicked: {
        var file = FileDialog.getSaveFileName()
        console.log("FileDialog.getSaveFileName returned " + file)
      }
    }
  }
}
