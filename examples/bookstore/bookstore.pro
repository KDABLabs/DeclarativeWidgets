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
    APP_LIBS.files = $${LIB_DESTDIR}/libdeclarativewidgets.1.0.0.dylib
    APP_LIBS.files += $${LIB_DESTDIR}/libdeclarativewidgets.1.0.dylib
    APP_LIBS.files += $${LIB_DESTDIR}/libdeclarativewidgets.1.dylib
    APP_LIBS.files += $${LIB_DESTDIR}/libdeclarativewidgets.dylib
    APP_LIBS.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += APP_LIBS

    DECLARATIVE_WIDGETS.files = $${OUT_PWD}/../../qml/QtWidgets
    DECLARATIVE_WIDGETS.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += DECLARATIVE_WIDGETS
}
