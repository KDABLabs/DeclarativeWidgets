include("$$PWD/../examples.pri")

# Input
SOURCES += \
    main.cpp \
    editor.cpp

HEADERS += \
    editor.h

RESOURCES += \
    text-editor.qrc

OTHER_FILES += \
    main.qml

mac {
    QT_WIDGETS.files = $${PLUGIN_DESTDIR}
    QT_WIDGETS.path = Contents/PlugIns
    QMAKE_BUNDLE_DATA += QT_WIDGETS
}
