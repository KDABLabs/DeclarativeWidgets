/*
  Developer.qml

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer <kevin.krammer@kdab.com>
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

import "qrc:///widgets"

MainWindow {
    id: mainWindow
    windowTitle: qsTr("Book Store");
    geometry: Qt.rect(0, 0, 1024, 768)

    MenuBar {
        Menu {
            title: qsTr("&File");

            Action {
                text: qsTr("Quit")
                icon: Icon.fromTheme("application-exit")
                onTriggered: mainWindow.close()
            }
        }

        Menu {
            title: qsTr("&Window");

            Action {
                text: qsTr("Admin")
                checkable: true
                checked: adminWindow.visible;

                onTriggered: {
                    adminWindow.visible = checked;
                }
            }
            Action {
                text: qsTr("Staff")
                checkable: true
                checked: staffWindow.visible;

                onTriggered: {
                    staffWindow.visible = checked;
                }
            }
            Action {
                text: qsTr("Shop")
                checkable: true
                checked: shopWindow.visible;

                onTriggered: {
                    shopWindow.visible = checked;
                }
            }
        }

        Menu {
          title: qsTr("&Help")

          Action {
            text: qsTr("About")
            icon: mainWindow.windowIcon
            onTriggered: MessageBox.about(qsTr("About Declarative Widgets Bookstore Example"),
                                          qsTr("This is an example of using Declarative Widgets for multiple UIs on the same application core"))
          }

          Action {
            text: qsTr("About Qt")
            onTriggered: MessageBox.aboutQt(qsTr("About Qt"))
          }
        }
    }

    // central widget
    Widget {
        GridLayout {
            GroupBox {
                GridLayout.row: 0
                GridLayout.column: 0
                GridLayout.columnSpan: 2

                title: qsTr("Book Table")
                HBoxLayout {
                    TableView {
                        model: _store.bookTable
                    }
                }
            }
            GroupBox {
                GridLayout.row: 1
                GridLayout.column: 0

                title: qsTr("Author Table")
                HBoxLayout {
                    TableView {
                        model: _store.authorTable

                        onActivated: _store.booksOfAuthorTable.setAuthor(_store.authorId(index))
                    }
                }
            }
            GroupBox {
                GridLayout.row: 1
                GridLayout.column: 1

                title: qsTr("Books Of Author Table")
                HBoxLayout {
                    TableView {
                        model: _store.booksOfAuthorTable
                    }
                }
            }
        }
    }


    Dialog {
        id: adminWindow
        windowTitle: qsTr("Admin")
        width: 640
        height: 480

        VBoxLayout {
            margin: 0

            LoaderWidget {
                source: "qrc:///widgets/Admin.qml"
            }
        }
    }


    Dialog {
        id: staffWindow
        windowTitle: qsTr("Staff")
        width: 640
        height: 480

        VBoxLayout {
            margin: 0

            LoaderWidget {
                source: "qrc:///widgets/Staff.qml"
            }
        }
    }

    Dialog {
        id: shopWindow
        windowTitle: qsTr("Shop")

        VBoxLayout {
            QuickWidget {
                source: "qrc:///qtquick/Shop.qml"

                rootContext: QmlContext {
                    QmlContextProperty {
                        name: "_store"
                        value: _store
                    }
                }
            }
        }
    }
}
