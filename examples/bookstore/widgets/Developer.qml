import QtGui 1.0

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
            Admin {
            }
        }
    }


    Dialog {
        id: staffWindow
        windowTitle: qsTr("Staff")
        width: 640
        height: 480

        VBoxLayout {
            Staff {
            }
        }
    }

    Dialog {
        id: shopWindow
        windowTitle: qsTr("Shop")

        VBoxLayout {
            DeclarativeView {
                source: "qrc:///qtquick/Shop.qml"

                rootContext: DeclarativeContext {
                    DeclarativeContextProperty {
                        name: "_store"
                        value: _store
                    }
                }
            }
        }
    }
}
