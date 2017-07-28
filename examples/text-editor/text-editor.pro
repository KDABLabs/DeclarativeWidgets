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
    APP_LIBS.files = $${OUT_PWD}/../../lib/libdeclarativewidgets.1.0.0.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.1.0.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.1.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.dylib
    APP_LIBS.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += APP_LIBS
}
