/*
  main.qml

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

MainWindow {
    id: mainWindow

    windowTitle: qsTr("Configuration Editor") + (_editor.fileName == "" ? "" : ": " + _editor.fileName)
    width: 1024
    height:768

    MenuBar {
        Menu {
            title: qsTr("File")

            Action {
                id: openAction

                text: qsTr("&Open")
                icon: Icon.fromTheme("document-open");

                onTriggered: {
                    FileDialog.nameFilters = [ "Config Files (*.ini *rc *.conf *.cfg)", "All Files (*.*)" ]
                    var file = FileDialog.getOpenFileName();
                    if (file != "") {
                        _editor.openFile(file);
                    }
                }
            }

            Action {
                id: saveAction

                text: qsTr("&Save")
                icon: Icon.fromTheme("document-save");

                onTriggered: {
                    if (editorStack.currentIndex == 0) {
                        _editor.saveText();
                    } else {
                        _editor.saveSettings();
                    }
                }
            }

            Action {
                text: qsTr("&Quit")
                icon: Icon.fromTheme("application-exit")

                onTriggered: mainWindow.close()
            }

        }
    }

    ToolBar {
        ActionItem {
            action: openAction
        }
        ActionItem {
            action: saveAction
        }
    }

    StackedWidget {
        id: editorStack

        currentIndex: customEditorLoader.source == "" ? 0 : 1

        TextEdit {
            document: _editor.textDocument;
        }

        LoaderWidget {
            id: customEditorLoader

            source: _editor.editorQml
        }
    }
}
