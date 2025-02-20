# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

set(TARGET declarativewidgets)

add_library(
  ${TARGET} MODULE
  abstractdeclarativeobject.cpp
  declarativeaction.cpp
  declarativeactionitem.cpp
  declarativeboxlayout.cpp
  declarativebuttongroupextension.cpp
  declarativecolordialog.cpp
  declarativecomboboxextension.cpp
  declarativefiledialog.cpp
  declarativefilesystemmodelextension.cpp
  declarativefontdialog.cpp
  declarativeformlayout.cpp
  declarativegridlayout.cpp
  declarativehboxlayout.cpp
  declarativeicon.cpp
  declarativeinputdialog.cpp
  declarativeitemviewextension.cpp
  declarativelabelextension.cpp
  declarativelayoutextension.cpp
  declarativeline.cpp
  declarativeloaderwidget.cpp
  declarativemessagebox.cpp
  declarativeobjectextension.cpp
  declarativepixmap.cpp
  declarativeqmlcontext.cpp
  declarativequickwidgetextension.cpp
  declarativeseparator.cpp
  declarativespaceritem.cpp
  declarativestackedlayout.cpp
  declarativestatusbar.cpp
  declarativestringlistmodelextension.cpp
  declarativetableviewextension.cpp
  declarativetabstops.cpp
  declarativetabwidget.cpp
  declarativetexteditextension.cpp
  declarativetreeviewextension.cpp
  declarativevboxlayout.cpp
  declarativewidgetextension.cpp
  declarativewidgets_plugin.cpp
  defaultobjectcontainer.cpp
  defaultwidgetcontainer.cpp
  mainwindowwidgetcontainer.cpp
  menubarwidgetcontainer.cpp
  menuwidgetcontainer.cpp
  objectadaptors.cpp
  scrollareawidgetcontainer.cpp
  stackedwidgetwidgetcontainer.cpp
  staticdialogmethodattached.cpp
  toolbarwidgetcontainer.cpp
  declarativesizepolicy.cpp)

target_link_libraries(
  ${TARGET}
  PRIVATE Qt${QTMAJOR}::Core Qt${QTMAJOR}::CorePrivate Qt${QTMAJOR}::Qml
          Qt${QTMAJOR}::Widgets Qt${QTMAJOR}::QuickWidgets)

if(Qt${QTMAJOR}WebEngineWidgets_FOUND)
  target_link_libraries(${TARGET} PRIVATE Qt${QTMAJOR}::WebEngineWidgets)
endif()

target_compile_definitions(${TARGET} PRIVATE BUILDING_DECLARATIVEWIDGETS)

set(PLUGIN_DESTDIR ${CMAKE_BINARY_DIR}/qml)

set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                           "${PLUGIN_DESTDIR}/QtWidgets")

if(NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL "${PLUGIN_DESTDIR}/QtWidgets")
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMENT "Copy qmldir to build directory"
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qmldir
            ${PLUGIN_DESTDIR}/QtWidgets/qmldir)
endif()

install(TARGETS ${TARGET}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt${QTMAJOR}/qml/QtWidgets)

install(FILES qmldir
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt${QTMAJOR}/qml/QtWidgets)
