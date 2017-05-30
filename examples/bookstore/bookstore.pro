TEMPLATE = app

INCLUDEPATH += . ../../lib

LIBS += -L ../../lib -ldeclarativewidgets

QT += qml widgets sql

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
