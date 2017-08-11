QT += testlib qml widgets

CONFIG += qt console warn_on depend_includepath testcase parallel_test
macos:CONFIG -= app_bundle

INCLUDEPATH += . $$PWD/../../lib/

LIBS += -ldeclarativewidgets
