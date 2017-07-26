include("$$PWD/../auto.pri")

SOURCES +=  tst_layouts.cpp \
    hboxlayoutwidget.cpp \
    vboxlayoutwidget.cpp \
    formlayoutwidget.cpp \
    gridlayoutwidget.cpp \
    stackedlayoutwidget.cpp \
    stackedwidget.cpp

RESOURCES += \
    qml.qrc

FORMS += \
    hboxlayout.ui \
    vboxlayout.ui \
    formlayout.ui \
    gridlayout.ui \
    stackedwidget.ui

HEADERS += \
    hboxlayoutwidget.h \
    vboxlayoutwidget.h \
    formlayoutwidget.h \
    gridlayoutwidget.h \
    stackedlayoutwidget.h \
    stackedwidget.h
