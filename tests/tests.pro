CONFIG += testcase
CONFIG += parallel_test

INCLUDEPATH += . ../lib/

LIBS += -ldeclarativewidgets

windows { # Hack while we don't have a proper build system
    release {
        LIBS +=-L$$PWD/../lib/Release
    } else {
        LIBS +=-L$$PWD/../lib/Debug
    }
} else:mac {
    LIBS +=-L../lib
} else {
    LIBS +=-L$$PWD/../lib
}

QT += qml widgets testlib gui-private quickwidgets

SOURCES += \
    tst_declarativeview.cpp

macos:CONFIG -= app_bundle

DISTFILES += \
    rectangle.qml \
    rectangle-context.qml

RESOURCES += \
    tests.qrc
