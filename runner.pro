TEMPLATE = app
TARGET = declarativewidgets
DEPENDPATH += .
INCLUDEPATH += . lib/

macx:CONFIG -= app_bundle

LIBS += -ldeclarativewidgets

QT += qml widgets

# Input
SOURCES += \
    main.cpp
