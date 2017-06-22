QT += testlib qml widgets

CONFIG += qt console warn_on depend_includepath testcase parallel_test
macos:CONFIG -= app_bundle

INCLUDEPATH += . $$PWD/../../lib/

LIBS += -ldeclarativewidgets

windows { # Hack while we don't have a proper build system
    release {
        LIBS +=-L$$PWD/../../lib/Release
    } else {
        LIBS +=-L$$PWD/../../lib/Debug
    }
} else:macos {
    LIBS +=-L../../../lib
} else {
    LIBS +=-L$$PWD/../../lib
}
