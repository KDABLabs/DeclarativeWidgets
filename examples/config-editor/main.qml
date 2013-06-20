import QtGui 1.0

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
