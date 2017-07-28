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
    APP_LIBS.files = $${OUT_PWD}/../../lib/libdeclarativewidgets.1.0.0.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.1.0.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.1.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.dylib
    APP_LIBS.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += APP_LIBS
}
