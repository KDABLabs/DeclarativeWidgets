TEMPLATE = app
TARGET = declarativewidgets
DEPENDPATH += .
INCLUDEPATH += . lib/

macx:CONFIG -= app_bundle

LIBS += -ldeclarativewidgets
windows { # Hack while we don't have a proper build system
    release {
        LIBS +=-Llib/Release
    } else {
        LIBS +=-Llib/Debug
    }
} else {
    LIBS +=-Llib
}

QT += qml widgets

# Input
SOURCES += \
    main.cpp
