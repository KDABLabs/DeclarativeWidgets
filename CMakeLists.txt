# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

cmake_minimum_required(VERSION 3.21)
project(declarativewidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIRS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(USE_QT6 "Use Qt6" OFF)
option(BUILD_EXAMPLES "Build the examples" ON)
option(ENABLE_SANITIZERS "Enable asan/ubsan sanitizers" OFF)

if(USE_QT6)
  find_package(Qt6 6.5 NO_MODULE REQUIRED COMPONENTS Qml Widgets QuickWidgets)
  find_package(Qt6 6.5 NO_MODULE QUIET COMPONENTS WebEngineWidgets)
  set(QTMAJOR 6)
  if(Qt6Core_VERSION VERSION_GREATER_EQUAL "6.10.0")
    set(QT_NO_PRIVATE_MODULE_WARNING ON)
    find_package(Qt6 6.5 NO_MODULE REQUIRED COMPONENTS WidgetsPrivate)
  endif()
else()
  find_package(Qt5 5.15 NO_MODULE REQUIRED COMPONENTS Qml Widgets QuickWidgets)
  find_package(Qt5 5.15 NO_MODULE QUIET COMPONENTS WebEngineWidgets)
  set(QTMAJOR 5)
endif()

if(ENABLE_SANITIZERS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
endif()

set(DW_PLUGIN_IMPORT_PATH \"${CMAKE_BINARY_DIR}/qml\")

add_executable(runner main.cpp)

target_compile_definitions(
  runner PRIVATE -DPLUGIN_IMPORT_PATH=${DW_PLUGIN_IMPORT_PATH})

target_link_libraries(runner PUBLIC Qt${QTMAJOR}::Qml Qt${QTMAJOR}::Widgets)

set_target_properties(runner PROPERTIES OUTPUT_NAME "declarativewidgets")

add_subdirectory(src)
add_subdirectory(ui2dw)
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
