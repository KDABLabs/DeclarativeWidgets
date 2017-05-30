TEMPLATE = app
TARGET = declarativewidgets
DEPENDPATH += .
INCLUDEPATH += . lib/

macx:CONFIG -= app_bundle

LIBS += -L lib -ldeclarativewidgets

QT += qml widgets

# Input
SOURCES += \
    main.cpp
