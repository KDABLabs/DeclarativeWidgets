include("$$PWD/../auto.pri")

SOURCES +=  tst_layouts.cpp \
    hboxlayoutwidget.cpp \
    vboxlayoutwidget.cpp

RESOURCES += \
    qml.qrc

FORMS += \
    hboxlayout.ui \
    vboxlayout.ui

HEADERS += \
    hboxlayoutwidget.h \
    vboxlayoutwidget.h
