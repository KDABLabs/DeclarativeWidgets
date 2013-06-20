TEMPLATE = app

INCLUDEPATH += . ../../lib

LIBS += -L ../../lib -ldeclarativewidgets

QT += declarative

TARGET = config-editor

SOURCES += main.cpp \
    configeditor.cpp \
    settingsadaptor.cpp

OTHER_FILES += \
    main.qml \
    demodata/akonadiserverrc-editor.qml \
    README.txt

RESOURCES += \
    config-editor.qrc

HEADERS += \
    configeditor.h \
    settingsadaptor.h
