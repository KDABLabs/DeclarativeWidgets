include("$$PWD/../auto.pri")

SOURCES +=  tst_layouts.cpp \
    hboxlayoutwidget.cpp \
    vboxlayoutwidget.cpp \
    formlayoutwidget.cpp

RESOURCES += \
    qml.qrc

FORMS += \
    hboxlayout.ui \
    vboxlayout.ui \
    formlayout.ui

HEADERS += \
    hboxlayoutwidget.h \
    vboxlayoutwidget.h \
    formlayoutwidget.h
