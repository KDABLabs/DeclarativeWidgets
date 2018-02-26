TEMPLATE = lib

TARGET = declarativewidgets

QT += core-private qml widgets quickwidgets

qtHaveModule(webenginewidgets) {
    QT += webenginewidgets
}

DESTDIR = $${LIB_DESTDIR}

mac {
    QMAKE_SONAME_PREFIX = @executable_path/../Frameworks
}

DEFINES += BUILDING_DECLARATIVEWIDGETS
CONFIG += c++11

HEADERS = \
  abstractdeclarativeobject_p.h \
  declarativeactionitem_p.h \
  declarativeaction_p.h \
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
  declarativelayoutextension.h \
  declarativemessagebox_p.h \
  declarativeobjectextension.h \
  declarativeobjectproxy_p.h \
  declarativepixmap_p.h \
  declarativeqmlcontext_p.h \
  declarativequickwidgetextension_p.h \
  declarativeseparator_p.h \
  declarativestackedlayout_p.h \
  declarativestatusbar_p.h \
  declarativestringlistmodelextension_p.h \
  declarativetableviewextension_p.h \
  declarativetabwidget_p.h \
  declarativetexteditextension_p.h \
  declarativetreeviewextension_p.h \
  declarativevboxlayout_p.h \
  declarativewidgetextension.h \
  declarativewidgetsdocument.h \
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
  declarativeloaderwidget_p.h \
  declarativespaceritem_p.h \
  declarativeline_p.h \
  declarativelabelextension_p.h \
  declarativetabstops_p.h \
  declarativelistitem_p.h

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
  declarativelayoutextension.cpp \
  declarativemessagebox.cpp \
  declarativeobjectextension.cpp \
  declarativepixmap.cpp \
  declarativeqmlcontext.cpp \
  declarativequickwidgetextension.cpp \
  declarativeseparator.cpp \
  declarativestackedlayout.cpp \
  declarativestatusbar.cpp \
  declarativestringlistmodelextension.cpp \
  declarativetableviewextension.cpp \
  declarativetabwidget.cpp \
  declarativetexteditextension.cpp \
  declarativetreeviewextension.cpp \
  declarativevboxlayout.cpp \
  declarativewidgetextension.cpp \
  declarativewidgetsdocument.cpp \
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
  declarativeloaderwidget.cpp \
  declarativespaceritem.cpp \
  declarativeline.cpp \
  declarativelabelextension.cpp \
  declarativetabstops.cpp \
  declarativelistitem.cpp
