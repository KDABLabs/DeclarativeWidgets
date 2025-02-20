# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

if(USE_QT6)
  find_package(Qt6 6.5 NO_MODULE REQUIRED COMPONENTS Sql QuickWidgets)
else()
  find_package(Qt5 5.15 NO_MODULE REQUIRED COMPONENTS Sql QuickWidgets)
endif()

add_subdirectory(bookstore)
add_subdirectory(config-editor)
add_subdirectory(text-editor)
