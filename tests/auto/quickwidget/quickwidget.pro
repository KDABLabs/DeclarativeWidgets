include("$$PWD/../auto.pri")

QT += gui-private quickwidgets

SOURCES += \
    tst_quickwidget.cpp

DISTFILES += \
    rectangle.qml \
    rectangle-context.qml

RESOURCES += \
    quickwidgets.qrc
