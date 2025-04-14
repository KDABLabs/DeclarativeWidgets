TEMPLATE = lib
TARGET = declarativewidgets
QT += core-private qml widgets quickwidgets

!versionAtLeast(QT_VERSION, 5.11.0):error("DeclarativeWidgets requires at least Qt version 5.11.0")

qtHaveModule(webenginewidgets) {
    QT += webenginewidgets
}

CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = QtWidgets

OTHER_FILES = qmldir

DESTDIR = $${PLUGIN_DESTDIR}/QtWidgets

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

DEFINES += BUILDING_DECLARATIVEWIDGETS
CONFIG += c++11

HEADERS = \
    abstractdeclarativeobject_p.h \
    declarativeaction_p.h \
    declarativeactionitem_p.h \
    declarativeboxlayout_p.h \
    declarativebuttongroupextension_p.h \
    declarativecolordialog_p.h \
    declarativecomboboxextension_p.h \
    declarativecontainerwidgetextension_p.h \
    declarativefiledialog_p.h \
    declarativefilesystemmodelextension_p.h \
    declarativefontdialog_p.h \
    declarativeformlayout_p.h \
    declarativegridlayout_p.h \
    declarativehboxlayout_p.h \
    declarativeicon_p.h \
    declarativeinputdialog_p.h \
    declarativeitemviewextension_p.h \
    declarativelabelextension_p.h \
    declarativelayoutextension.h \
    declarativeline_p.h \
    declarativeloaderwidget_p.h \
    declarativemessagebox_p.h \
    declarativeobjectextension.h \
    declarativeobjectproxy_p.h \
    declarativepixmap_p.h \
    declarativeqmlcontext_p.h \
    declarativequickwidgetextension_p.h \
    declarativeseparator_p.h \
    declarativespaceritem_p.h \
    declarativestackedlayout_p.h \
    declarativestatusbar_p.h \
    declarativestringlistmodelextension_p.h \
    declarativetableviewextension_p.h \
    declarativetabstops_p.h \
    declarativetabwidget_p.h \
    declarativetexteditextension_p.h \
    declarativetreeviewextension_p.h \
    declarativevboxlayout_p.h \
    declarativewidgetextension.h \
    declarativewidgets_plugin.h \
    defaultobjectcontainer_p.h \
    defaultwidgetcontainer.h \
    layoutcontainerinterface_p.h \
    mainwindowwidgetcontainer_p.h \
    menubarwidgetcontainer_p.h \
    menuwidgetcontainer_p.h \
    objectadaptors_p.h \
    objectcontainerinterface_p.h \
    scrollareawidgetcontainer_p.h \
    stackedwidgetwidgetcontainer_p.h \
    staticdialogmethodattached_p.h \
    toolbarwidgetcontainer_p.h \
    widgetcontainerinterface_p.h \
    declarativesizepolicy_p.h \
    splitterwidgetcontainer_p.h

SOURCES = \
    abstractdeclarativeobject.cpp \
    declarativeaction.cpp \
    declarativeactionitem.cpp \
    declarativeboxlayout.cpp \
    declarativebuttongroupextension.cpp \
    declarativecolordialog.cpp \
    declarativecomboboxextension.cpp \
    declarativefiledialog.cpp \
    declarativefilesystemmodelextension.cpp \
    declarativefontdialog.cpp \
    declarativeformlayout.cpp \
    declarativegridlayout.cpp \
    declarativehboxlayout.cpp \
    declarativeicon.cpp \
    declarativeinputdialog.cpp \
    declarativeitemviewextension.cpp \
    declarativelabelextension.cpp \
    declarativelayoutextension.cpp \
    declarativeline.cpp \
    declarativeloaderwidget.cpp \
    declarativemessagebox.cpp \
    declarativeobjectextension.cpp \
    declarativepixmap.cpp \
    declarativeqmlcontext.cpp \
    declarativequickwidgetextension.cpp \
    declarativeseparator.cpp \
    declarativespaceritem.cpp \
    declarativestackedlayout.cpp \
    declarativestatusbar.cpp \
    declarativestringlistmodelextension.cpp \
    declarativetableviewextension.cpp \
    declarativetabstops.cpp \
    declarativetabwidget.cpp \
    declarativetexteditextension.cpp \
    declarativetreeviewextension.cpp \
    declarativevboxlayout.cpp \
    declarativewidgetextension.cpp \
    declarativewidgets_plugin.cpp \
    defaultobjectcontainer.cpp \
    defaultwidgetcontainer.cpp \
    mainwindowwidgetcontainer.cpp \
    menubarwidgetcontainer.cpp \
    menuwidgetcontainer.cpp \
    objectadaptors.cpp \
    scrollareawidgetcontainer.cpp \
    stackedwidgetwidgetcontainer.cpp \
    staticdialogmethodattached.cpp \
    toolbarwidgetcontainer.cpp \
    declarativesizepolicy.cpp \
    splitterwidgetcontainer.cpp
