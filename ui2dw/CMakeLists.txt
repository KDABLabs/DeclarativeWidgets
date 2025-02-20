# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group
# company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    main.cpp
    uinode.cpp
    uinodevisitor.cpp
    uiwidgetnode.cpp
    parser.cpp
    uitopnode.cpp
    qmlwriter.cpp
    idvisitor.cpp
    uilayoutnode.cpp
    uiobjectnode.cpp
    uipropertynode.cpp
    elementnamevisitor.cpp
    uiactionnode.cpp
    uiaddactionnode.cpp
    uilayoutitemnode.cpp
    itemvisitor.cpp
    uispacernode.cpp
    fontproperyvisitor.cpp
    uiconnectionnode.cpp
    connectionnodevisitor.cpp
    layoutvisitor.cpp
    buddyvisitor.cpp
    uitabstopsnode.cpp
    tabstopsnodevisitor.cpp)

add_executable(ui2dw ${SOURCES})
target_link_libraries(ui2dw PRIVATE Qt${QTMAJOR}::Core)
