TEMPLATE = lib
TARGET = declarativewidgetsplugin
QT += core-private qml widgets quickwidgets

qtHaveModule(webenginewidgets) {
    QT += webenginewidgets
}

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
        LIBS +=-L../../lib/Release
    } else {
        LIBS +=-L../../lib/Debug
    }
} else {
    LIBS +=-L../lib
}
OTHER_FILES = qmldir

# Deploy the plugin to a more accessible location
DESTDIR = ../qml/QtWidgets

!equals(_PRO_FILE_PWD_, $$DESTDIR) {
    copy_qmldir.target = $$DESTDIR/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir

