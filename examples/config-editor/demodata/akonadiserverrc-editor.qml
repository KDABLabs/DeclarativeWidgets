/*
  akonadiserverrc-editor.qml

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

import QtCore 1.0
import QtWidgets 1.0
import QtQml 2.0 // for Component.onCompleted

Widget {
    VBoxLayout {
        GroupBox {
            id: general
            title: qsTr("General");

            FormLayout {
                ComboBox {
                    id: driverCombo

                    FormLayout.label: qsTr("Driver")

                    model: StringListModel {
                        id: driverModel
                        stringList: [ qsTr("QMYSQL"), qsTr("QPGSQL"), qsTr("QSLITE3") ]
                    }

                    currentIndex: driverModel.stringList.indexOf(_editor.settings.value("General/Driver"))
                }

                SpinBox {
                    id: sizeThreshold
                    FormLayout.label: qsTr("Size Threshold");

                    minimum: 0
                    maximum: 100000
                    suffix: qsTr(" KB");

                    value: _editor.settings.value("General/SizeThreshold")
                }

                CheckBox {
                    id: externalPayload
                    FormLayout.label: qsTr("External Payload")

                    checked: _editor.settings.value("General/ExternalPayload")
                }
            }

            function updateOnSave() {
                _editor.settings.setValue("General/Driver", driverModel.stringList[driverCombo.currentIndex]);
                _editor.settings.setValue("General/SizeThreshold", sizeThreshold.value);
                _editor.settings.setValue("General/ExternalPayload", externalPayload.checked);
            }
        }

        StackedWidget {
            currentIndex: driverCombo.currentIndex

            GroupBox {
                id: mySQL
                title: qsTr("MySQL")

                FormLayout {
                    LineEdit {
                        id: mySQL_name

                        FormLayout.label: qsTr("Database Name")

                        text: _editor.settings.valueWithDefault("QMYSQL/Name", "akonadi")
                    }

                    Widget {
                        HBoxLayout {
                            RadioButton {
                                id: internalMySQLServer
                                text: qsTr("Start internal server")

                                checked: _editor.settings.valueWithDefault("QMYSQL/StartServer", true)
                            }
                            RadioButton {
                                text: qsTr("Connect to external server")
                            }
                        }
                    }

                    LineEdit {
                        id: mySQL_serverPath

                        FormLayout.label: qsTr("Server path")

                        text: _editor.settings.value("QMYSQL/ServerPath")

                        enabled: internalMySQLServer.checked
                    }

                    LineEdit {
                        id: mySQL_options

                        FormLayout.label: qsTr("Options")

                        text: _editor.settings.value("QMYSQL/Options")

                        enabled: internalMySQLServer.checked
                    }

                    LineEdit {
                        id: mySQL_host

                        FormLayout.label: qsTr("Host")

                        text: _editor.settings.value("QMYSQL/Host")

                        enabled: !internalMySQLServer.checked
                    }

                    LineEdit {
                        id: mySQL_user

                        FormLayout.label: qsTr("User")

                        text: _editor.settings.value("QMYSQL/User")

                        enabled: !internalMySQLServer.checked
                    }

                    LineEdit {
                        id: mySQL_password

                        FormLayout.label: qsTr("Password")

                        text: _editor.settings.value("QMYSQL/Password")
                        echoMode: LineEdit.PasswordEchoOnEdit

                        enabled: !internalMySQLServer.checked
                    }
                }

                function updateOnSave() {
                    _editor.settings.setValue("QMYSQL/Name", mySQL_name.text);
                    _editor.settings.setValue("QMYSQL/StartServer", internalMySQLServer.checked);
                    if (internalMySQLServer.checked) {
                        _editor.settings.setValue("QMYSQL/ServerPath", mySQL_serverPath.text);
                        _editor.settings.setValue("QMYSQL/Options", mySQL_options.text);
                    } else {
                        _editor.settings.setValue("QMYSQL/Host", mySQL_host.text);
                        _editor.settings.setValue("QMYSQL/User", mySQL_user.text);
                        _editor.settings.setValue("QMYSQL/Password", mySQL_password.text);
                    }
                }
            }

            // almost the same settings as for MySQL so showing use of ButtonGroup
            // for managing exclusivness across different button parents
            GroupBox {
                id: postgreSQL

                title: qsTr("PostgreSQL")

                FormLayout {
                    LineEdit {
                        id: postgreSQL_name

                        FormLayout.label: qsTr("Database Name")

                        text: _editor.settings.valueWithDefault("QPGSQL/Name", "akonadi")
                    }

                    LineEdit {
                        id: postgreSQL_options

                        FormLayout.label: qsTr("Connection Options")

                        text: _editor.settings.value("QPGSQL/Options")
                    }

                    Widget {
                        HBoxLayout {
                            Widget {
                                FormLayout {
                                    RadioButton {
                                        id: internalPostgreSQLServer
                                        text: qsTr("Start internal server")

                                        checked: _editor.settings.valueWithDefault("QPGSQL/StartServer", true)
                                    }

                                    LineEdit {
                                        id: postgreSQL_serverPath

                                        FormLayout.label: qsTr("Server path")

                                        text: _editor.settings.value("QPGSQL/ServerPath")

                                        enabled: internalPostgreSQLServer.checked
                                    }
                                }
                            }
                            Widget {
                                FormLayout {
                                    RadioButton {
                                        id: externalPostgreSQLServer
                                        text: qsTr("Connect to external server")
                                    }

                                    LineEdit {
                                        id: postgreSQL_host

                                        FormLayout.label: qsTr("Host")

                                        text: _editor.settings.value("QPGSQL/Host")

                                        enabled: !internalPostgreSQLServer.checked
                                    }

                                    LineEdit {
                                        id: postgreSQL_user

                                        FormLayout.label: qsTr("User")

                                        text: _editor.settings.value("QPGSQL/User")

                                        enabled: !internalPostgreSQLServer.checked
                                    }

                                    LineEdit {
                                        id: postgreSQL_password

                                        FormLayout.label: qsTr("Password")

                                        text: _editor.settings.value("QPGSQL/Password")
                                        echoMode: LineEdit.PasswordEchoOnEdit

                                        enabled: !internalPostgreSQLServer.checked
                                    }
                                }
                            }
                        }
                        ButtonGroup {
                            buttons: [ internalPostgreSQLServer, externalPostgreSQLServer ]
                        }
                    }
                }

                function updateOnSave() {
                    _editor.settings.setValue("QPGSQL/Name", postgreSQL_name.text);
                    _editor.settings.setValue("QPGSQL/StartServer", internalPostgreSQLServer.checked);
                    _editor.settings.setValue("QPGSQL/Options", postgreSQL_options.text);

                    if (internalPostgreSQLServer.checked) {
                        _editor.settings.setValue("QPGSQL/ServerPath", postgreSQL_serverPath.text);
                    } else {
                        _editor.settings.setValue("QPGSQL/Host", postgreSQL_host.text);
                        _editor.settings.setValue("QPGSQL/User", postgreSQL_user.text);
                        _editor.settings.setValue("QPGSQL/Password", postgreSQL_password.text);
                    }
                }
            }

            GroupBox {
                title: qsTr("Sqlite")

                FormLayout {
                    Widget {
                        FormLayout.label: qsTr("Database File")

                        HBoxLayout {
                            LineEdit {
                                id: sqliteName

                                text: _editor.settings.value("QSQLITE3/Name")
                                placeholderText: qsTr("SQLite database file with path")
                            }
                            PushButton {
                                text: qsTr("Browse...")
                                icon: Icon.fromTheme("document-open")

                                onClicked: {
                                    FileDialog.caption = qsTr("Select an QSLite database file")
                                    FileDialog.nameFilters = [ qsTr("SQLite Files (*.db)"), qsTr("All Files (*.*)") ]
                                    var file = FileDialog.getOpenFileName()

                                    if ( file != "" ) {
                                        sqliteName.text = file;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    function updateOnSave() {
        general.updateOnSave();
        switch (driverCombo.currentIndex) {
        case 0:
            mySQL.updateOnSave();
            break;
        case 1:
            postgreSQL.updateOnSave();
            break;
        case 2:
            _editor.settings.setValue("QSQLITE3/Name", sqliteName.text);
            break;
        }

        _editor.updateOnSaveDone();
    }

    Component.onCompleted: {
        // we update values on request
        _editor.settings.updatesOnSave = true;
        _editor.requestUpdateOnSave.connect(updateOnSave);
    }
}
