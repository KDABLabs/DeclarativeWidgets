# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

add_executable(config-editor main.cpp configeditor.cpp settingsadaptor.cpp
                             config-editor.qrc)

target_link_libraries(config-editor PRIVATE Qt${QTMAJOR}::Qml
                                            Qt${QTMAJOR}::Widgets)

if(Qt${QTMAJOR}WebEngineWidgets_FOUND)
  target_link_libraries(config-editor PRIVATE Qt${QTMAJOR}::WebEngineWidgets)
endif()

target_compile_definitions(
  config-editor PRIVATE -DPLUGIN_IMPORT_PATH=${DW_PLUGIN_IMPORT_PATH})

set(QML_FILES main.qml)
