TEMPLATE = app
TARGET = declarativewidgets
DEPENDPATH += .
INCLUDEPATH += .

macx:CONFIG -= app_bundle

QT += qml widgets

# Input
SOURCES += \
    main.cpp
