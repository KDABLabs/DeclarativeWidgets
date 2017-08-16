include("$$PWD/../examples.pri")

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

mac {
    QT_WIDGETS.files = $${PLUGIN_DESTDIR}
    QT_WIDGETS.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += QT_WIDGETS
}
