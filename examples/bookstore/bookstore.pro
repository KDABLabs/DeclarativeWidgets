include("$$PWD/../examples.pri")

QT += sql quickwidgets

SOURCES += \
    main.cpp \
    bookstore.cpp \
    booksofauthormodel.cpp \
    booklistproxymodel.cpp

HEADERS += \
    bookstore.h \
    booksofauthormodel.h \
    booklistproxymodel.h

OTHER_FILES += \
    README.txt \
    qtquick/Shop.qml \
    widgets/Admin.qml \
    widgets/Developer.qml \
    widgets/Staff.qml

RESOURCES += \
    bookstore.qrc

mac {
    QT_WIDGETS.files = $${PLUGIN_DESTDIR}
    QT_WIDGETS.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += QT_WIDGETS
}
