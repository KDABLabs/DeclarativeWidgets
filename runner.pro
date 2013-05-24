TEMPLATE = app
TARGET = declarativewidgets
DEPENDPATH += .
INCLUDEPATH += . lib/

macx:CONFIG -= app_bundle

LIBS += -L lib -ldeclarativewidgets

QT += declarative

# Input
SOURCES += \
    main.cpp
