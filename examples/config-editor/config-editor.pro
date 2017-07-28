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
    APP_LIBS.files = $${OUT_PWD}/../../lib/libdeclarativewidgets.1.0.0.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.1.0.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.1.dylib
    APP_LIBS.files += $${OUT_PWD}/../../lib/libdeclarativewidgets.dylib
    APP_LIBS.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += APP_LIBS
}
