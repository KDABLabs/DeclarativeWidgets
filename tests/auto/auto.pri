QT += testlib qml widgets

CONFIG += qt console warn_on depend_includepath testcase parallel_test
macos:CONFIG -= app_bundle

INCLUDEPATH += . $$PWD/../../lib/

LIBS += -ldeclarativewidgets

windows { # Hack while we don't have a proper build system
    release {
        LIBS +=-L../../lib/Release
    } else {
        LIBS +=-L../../lib/Debug
    }
} else {
    LIBS +=-L../../../lib
}
