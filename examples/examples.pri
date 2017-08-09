TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += . $$PWD/../lib
QT += qml widgets
LIBS += -ldeclarativewidgets

windows {
    release {
        LIBS +=-L../../lib/Release
    } else {
        LIBS +=-L../../lib/Debug
    }
} else {
    LIBS +=-L../../lib
}
