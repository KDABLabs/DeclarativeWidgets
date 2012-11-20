TEMPLATE = app

INCLUDEPATH += . ../../lib

LIBS += -L ../../lib -ldeclarativewidgets

QT += declarative sql

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
    widgets/main.qml \
    qtquick/main.qml \
    README.txt

RESOURCES += \
    bookstore.qrc
