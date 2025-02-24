# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

add_executable(text-editor main.cpp editor.cpp text-editor.qrc)

target_link_libraries(text-editor PRIVATE Qt${QTMAJOR}::Qml
                                          Qt${QTMAJOR}::Widgets)

if(Qt${QTMAJOR}WebEngineWidgets_FOUND)
  target_link_libraries(text-editor PRIVATE Qt${QTMAJOR}::WebEngineWidgets)
endif()

target_compile_definitions(
  text-editor PRIVATE -DPLUGIN_IMPORT_PATH=${DW_PLUGIN_IMPORT_PATH})

set(QML_FILES main.qml)
