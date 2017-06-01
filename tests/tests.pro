CONFIG += testcase
CONFIG += parallel_test

INCLUDEPATH += . ../lib/

LIBS += -L../lib -ldeclarativewidgets

QT += qml widgets testlib gui-private quickwidgets

SOURCES += \
    tst_declarativeview.cpp

macos:CONFIG -= app_bundle

DISTFILES += \
    rectangle.qml

RESOURCES += \
    tests.qrc
