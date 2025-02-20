# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

add_executable(bookstore main.cpp bookstore.cpp booksofauthormodel.cpp
                         booklistproxymodel.cpp bookstore.qrc)

target_link_libraries(
  bookstore PRIVATE Qt${QTMAJOR}::Qml Qt${QTMAJOR}::Widgets
                    Qt${QTMAJOR}::QuickWidgets Qt${QTMAJOR}::Sql)

if(Qt${QTMAJOR}WebEngineWidgets_FOUND)
  target_link_libraries(bookstore PRIVATE Qt${QTMAJOR}::WebEngineWidgets)
endif()

target_compile_definitions(
  bookstore PRIVATE -DPLUGIN_IMPORT_PATH=${DW_PLUGIN_IMPORT_PATH})

set(QML_FILES main.qml)
