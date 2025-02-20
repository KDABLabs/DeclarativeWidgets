# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

if(USE_QT6)
  find_package(Qt6 6.5 NO_MODULE REQUIRED COMPONENTS Test Quick QuickWidgets)
else()
  find_package(Qt5 5.15 NO_MODULE REQUIRED COMPONENTS Test Quick QuickWidgets)
endif()

enable_testing()
# Function to create a test executable with Qt dependencies Args: TEST_NAME:
# Name of the test executable to create ARGN: Additional source files for the
# test
function(add_test_executable test_name)
  add_executable(${test_name} ${ARGN})
  add_test(NAME ${test_name} COMMAND ${test_name})
  target_link_libraries(
    ${test_name} PRIVATE Qt${QTMAJOR}::Quick Qt${QTMAJOR}::Widgets
                         Qt${QTMAJOR}::QuickWidgets Qt${QTMAJOR}::Test)
  if(Qt${QTMAJOR}WebEngineWidgets_FOUND)
    target_link_libraries(${test_name} PRIVATE Qt${QTMAJOR}::WebEngineWidgets)
  endif()
  target_compile_definitions(
    ${test_name} PRIVATE -DPLUGIN_IMPORT_PATH=${DW_PLUGIN_IMPORT_PATH})
endfunction()

add_test_executable(
  tst_instantiatetypes auto/instantiatetypes/tst_instantiatetypes.cpp
  auto/instantiatetypes/qml.qrc)

add_test_executable(
  tst_layouts
  auto/layouts/formlayoutwidget.cpp
  auto/layouts/gridlayoutwidget.cpp
  auto/layouts/hboxlayoutwidget.cpp
  auto/layouts/stackedlayoutwidget.cpp
  auto/layouts/stackedwidget.cpp
  auto/layouts/tst_layouts.cpp
  auto/layouts/vboxlayoutwidget.cpp
  auto/layouts/qml.qrc
  auto/layouts/formlayout.ui
  auto/layouts/gridlayout.ui
  auto/layouts/hboxlayout.ui
  auto/layouts/stackedwidget.ui
  auto/layouts/vboxlayout.ui)

add_test_executable(tst_qmlplugins auto/qmlplugins/tst_qmlplugins.cpp)

add_test_executable(tst_quickwidget auto/quickwidget/tst_quickwidget.cpp
                    auto/quickwidget/quickwidgets.qrc)
