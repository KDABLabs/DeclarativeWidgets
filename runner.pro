TEMPLATE = app
TARGET = declarativewidgets
DEPENDPATH += .
INCLUDEPATH += . lib/

macx:CONFIG -= app_bundle

LIBS += -ldeclarativewidgets
windows { # Hack while we don't have a proper build system
    release {
        LIBS +=-L$$PWD/lib/Release
    } else {
        LIBS +=-L$$PWD/lib/Debug
    }
} else {
    LIBS +=-L$$PWD/lib
}

QT += qml widgets

# Input
SOURCES += \
    main.cpp
