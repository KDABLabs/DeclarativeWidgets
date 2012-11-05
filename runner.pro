TEMPLATE = app
TARGET = declarativewidgets
DEPENDPATH += .
INCLUDEPATH += . lib/

LIBS += -L lib -ldeclarativewidgets

QT += declarative

# Input
SOURCES += \
    main.cpp
    