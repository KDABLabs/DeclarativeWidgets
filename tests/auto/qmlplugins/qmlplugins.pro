QT += testlib qml widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

# Required to find the declarativewidgets library on macOS, as we are not using an app bundle
LIBS += -L../../../lib

SOURCES +=  tst_qmlplugins.cpp
