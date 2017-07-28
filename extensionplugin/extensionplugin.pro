TEMPLATE = lib
TARGET = declarativewidgetsplugin
QT += core-private qml widgets webenginewidgets quickwidgets
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = QtWidgets

# Input
SOURCES += \
    extensionplugin_plugin.cpp

HEADERS += \
    extensionplugin_plugin.h

INCLUDEPATH += . ../lib/

LIBS += -ldeclarativewidgets

windows { # Hack while we don't have a proper build system
    release {
        LIBS +=-L$$PWD/../lib/Release
    } else {
        LIBS +=-L$$PWD/../lib/Debug
    }
} else {
    LIBS +=-L$$PWD/../lib
}
OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
installPath = $$[QT_INSTALL_IMPORTS]/$$replace(uri, \\., /)
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir

