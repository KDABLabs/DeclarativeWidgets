/*
  Copyright (C) 2012-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com
  Author: Tobias Koenig, tobias.koenig@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "declarativewidgetsdocument.h"

// The declarative widget wrappers
#include "declarativeactionitem_p.h"
#include "declarativeaction_p.h"
#include "declarativebuttongroupextension_p.h"
#include "declarativecolordialog_p.h"
#include "declarativecomboboxextension_p.h"
#include "declarativecontainerwidgetextension_p.h"
#include "declarativedeclarativecontext_p.h"
#include "declarativedeclarativeviewextension_p.h"
#include "declarativefiledialog_p.h"
#include "declarativefilesystemmodelextension_p.h"
#include "declarativefontdialog_p.h"
#include "declarativeformlayout_p.h"
#include "declarativegridlayout_p.h"
#include "declarativehboxlayout_p.h"
#include "declarativeicon_p.h"
#include "declarativeinputdialog_p.h"
#include "declarativeitemviewextension_p.h"
#include "declarativeloaderwidget_p.h"
#include "declarativemessagebox_p.h"
#include "declarativepixmap_p.h"
#include "declarativeseparator_p.h"
#include "declarativespaceritem_p.h"
#include "declarativestackedlayout_p.h"
#include "declarativestatusbar_p.h"
#include "declarativestringlistmodelextension_p.h"
#include "declarativetableviewextension_p.h"
#include "declarativetabwidget_p.h"
#include "declarativetexteditextension_p.h"
#include "declarativetreeviewextension_p.h"
#include "declarativevboxlayout_p.h"
#include "declarativewidgetextension.h"
#include "mainwindowwidgetcontainer_p.h"
#include "menubarwidgetcontainer_p.h"
#include "menuwidgetcontainer_p.h"
#include "scrollareawidgetcontainer_p.h"
#include "stackedwidgetwidgetcontainer_p.h"
#include "toolbarwidgetcontainer_p.h"

#include <QButtonGroup>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QColumnView>
#include <QComboBox>
#include <QCommandLinkButton>
#include <QCoreApplication>
#include <QDateTimeEdit>
#include <QDebug>
#include <QDeclarativeView>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDial>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFileSystemModel>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLCDNumber>
#include <QListView>
#include <QMainWindow>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QRadioButton>
#include <QScrollBar>
#include <QStackedWidget>
#include <QStringListModel>
#include <QTableView>
#include <QTextBrowser>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QWebView>

class DeclarativeWidgetsDocument::Private
{
  public:
    Private(DeclarativeWidgetsDocument *qq, const QUrl &url)
      : q(qq)
      , m_url(url)
      , m_engine(new QDeclarativeEngine(q))
      , m_component(new QDeclarativeComponent(m_engine, q))
    {
    }

    DeclarativeWidgetsDocument* q;
    QUrl m_url;
    QDeclarativeEngine* m_engine;
    QDeclarativeComponent* m_component;
};

DeclarativeWidgetsDocument::DeclarativeWidgetsDocument(const QUrl &url, QObject *parent)
  : QObject(parent)
  , d(new Private(this, url))
{
  // objects
  qmlRegisterType<QAbstractItemModel>();
  qmlRegisterType<QAction>();
  qmlRegisterExtendedType<DeclarativeAction, DeclarativeObjectExtension>("QtWidgets", 1, 0, "Action");
  qmlRegisterExtendedType<DeclarativeActionItem, DeclarativeObjectExtension>("QtWidgets", 1, 0, "ActionItem");
  qmlRegisterExtendedType<QButtonGroup, DeclarativeButtonGroupExtension>("QtWidgets", 1, 0, "ButtonGroup");
  qmlRegisterType<DeclarativeContextProperty>("QtWidgets", 1, 0, "DeclarativeContextProperty");
  qmlRegisterType<DeclarativeDeclarativeContext>("QtWidgets", 1, 0, "DeclarativeContext");
  qmlRegisterExtendedType<QFileSystemModel, DeclarativeFileSystemModelExtension>("QtWidgets", 1, 0, "FileSystemModel");
  qmlRegisterType<DeclarativeIcon>("QtWidgets", 1, 0, "Icon");
  qmlRegisterType<QItemSelectionModel>();
  qmlRegisterType<DeclarativePixmap>("QtWidgets", 1, 0, "Pixmap");
  qmlRegisterExtendedType<DeclarativeSeparator, DeclarativeObjectExtension>("QtWidgets", 1, 0, "Separator");
  qmlRegisterExtendedType<QStringListModel, DeclarativeStringListModelExtension>("QtCore", 1, 0, "StringListModel");
  qmlRegisterType<QTextDocument>();
  qmlRegisterType<QTimer>("QtCore", 1, 0, "Timer");

  // layouts
  qmlRegisterExtendedType<DeclarativeFormLayout, DeclarativeFormLayoutExtension>("QtWidgets", 1, 0, "FormLayout");
  qmlRegisterExtendedType<DeclarativeHBoxLayout, DeclarativeHBoxLayoutExtension>("QtWidgets", 1, 0, "HBoxLayout");
  qmlRegisterExtendedType<DeclarativeGridLayout, DeclarativeGridLayoutExtension>("QtWidgets", 1, 0, "GridLayout");
  qmlRegisterExtendedType<DeclarativeStackedLayout, DeclarativeStackedLayoutExtension>("QtWidgets", 1, 0, "StackedLayout");
  qmlRegisterExtendedType<DeclarativeVBoxLayout, DeclarativeVBoxLayoutExtension>("QtWidgets", 1, 0, "VBoxLayout");

  // widgets
  qmlRegisterExtendedType<QCalendarWidget, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "CalendarWidget");
  qmlRegisterExtendedType<QCheckBox, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "CheckBox");
  qmlRegisterExtendedType<DeclarativeColorDialog, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "ColorDialog");
  qmlRegisterExtendedType<QColumnView, DeclarativeItemViewExtension>("QtWidgets", 1, 0, "ColumnView");
  qmlRegisterExtendedType<QCommandLinkButton, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "CommandLinkButton");
  qmlRegisterExtendedType<QComboBox, DeclarativeComboBoxExtension>("QtWidgets", 1, 0, "ComboBox");
  qmlRegisterExtendedType<QDateEdit, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "DateEdit");
  qmlRegisterExtendedType<QDateTimeEdit, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "DateTimeEdit");
  qmlRegisterExtendedType<QDeclarativeView, DeclarativeDeclarativeViewExtension>("QtWidgets", 1, 0, "DeclarativeView");
  qmlRegisterExtendedType<QDial, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "Dial");
  qmlRegisterExtendedType<Dialog, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "Dialog");
  qmlRegisterExtendedType<QDialogButtonBox, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "DialogButtonBox");
  qmlRegisterExtendedType<QDoubleSpinBox, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "DoubleSpinBox");
  qmlRegisterExtendedType<DeclarativeFileDialog, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "FileDialog");
  qmlRegisterExtendedType<QFrame, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "Frame");
  qmlRegisterExtendedType<DeclarativeFontDialog, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "FontDialog");
  qmlRegisterExtendedType<QGroupBox, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "GroupBox");
  qmlRegisterExtendedType<DeclarativeInputDialog, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "InputDialog");
  qmlRegisterUncreatableType<QHeaderView>("QtWidgets", 1, 0, "HeaderView", "");
  qmlRegisterExtendedType<QLabel, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "Label");
  qmlRegisterExtendedType<QLCDNumber, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "LCDNumber");
  qmlRegisterExtendedType<QLineEdit, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "LineEdit");
  qmlRegisterExtendedType<QListView, DeclarativeItemViewExtension>("QtWidgets", 1, 0, "ListView");
  qmlRegisterExtendedType<DeclarativeLoaderWidget, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "LoaderWidget");
  qmlRegisterExtendedType<QMainWindow, DeclarativeContainerWidgetExtension<MainWindowWidgetContainer> >("QtWidgets", 1, 0, "MainWindow");
  qmlRegisterExtendedType<Menu, DeclarativeContainerWidgetExtension<MenuWidgetContainer> >("QtWidgets", 1, 0, "Menu");
  qmlRegisterExtendedType<QMenuBar, DeclarativeContainerWidgetExtension<MenuBarWidgetContainer> >("QtWidgets", 1, 0, "MenuBar");
  qmlRegisterExtendedType<DeclarativeMessageBox, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "MessageBox");
  qmlRegisterExtendedType<QPlainTextEdit, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "PlainTextEdit");
  qmlRegisterExtendedType<QProgressBar, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "ProgressBar");
  qmlRegisterExtendedType<QPushButton, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "PushButton");
  qmlRegisterExtendedType<QRadioButton, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "RadioButton");
  qmlRegisterExtendedType<QScrollArea, DeclarativeContainerWidgetExtension<ScrollAreaWidgetContainer> >("QtWidgets", 1, 0, "ScrollArea");
  qmlRegisterExtendedType<QScrollBar, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "ScrollBar");
  qmlRegisterExtendedType<QSlider, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "Slider");
  qmlRegisterType<DeclarativeSpacerItem>("QtWidgets", 1, 0, "Spacer");
  qmlRegisterExtendedType<QStackedWidget, DeclarativeContainerWidgetExtension<StackedWidgetWidgetContainer> >("QtWidgets", 1, 0, "StackedWidget");
  qmlRegisterExtendedType<QSpinBox, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "SpinBox");
  qmlRegisterExtendedType<DeclarativeStatusBar, DeclarativeContainerWidgetExtension<StatusBarWidgetContainer> >("QtWidgets", 1, 0, "StatusBar");
  qmlRegisterExtendedType<QTableView, DeclarativeTableViewExtension>("QtWidgets", 1, 0, "TableView");
  qmlRegisterExtendedType<DeclarativeTabWidget, DeclarativeContainerWidgetExtension<TabWidgetWidgetContainer> >("QtWidgets", 1, 0, "TabWidget");
  qmlRegisterExtendedType<QTextBrowser, DeclarativeTextEditExtension>("QtWidgets", 1, 0, "TextBrowser");
  qmlRegisterExtendedType<QTextEdit, DeclarativeTextEditExtension>("QtWidgets", 1, 0, "TextEdit");
  qmlRegisterExtendedType<QTimeEdit, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "TimeEdit");
  qmlRegisterExtendedType<QToolBar, DeclarativeContainerWidgetExtension<ToolBarWidgetContainer> >("QtWidgets", 1, 0, "ToolBar");
  qmlRegisterExtendedType<QToolButton, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "ToolButton");
  qmlRegisterExtendedType<QTreeView, DeclarativeTreeViewExtension>("QtWidgets", 1, 0, "TreeView");
  qmlRegisterExtendedType<QWebView, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "WebView");
  qmlRegisterExtendedType<QWidget, DeclarativeWidgetExtension>("QtWidgets", 1, 0, "Widget");

  d->m_component->loadUrl(d->m_url);
  if (d->m_component->isError()) {
    foreach (const QDeclarativeError &error, d->m_component->errors())
      qDebug() << error.toString();
  }
}

DeclarativeWidgetsDocument::~DeclarativeWidgetsDocument()
{
  delete d;
}

void DeclarativeWidgetsDocument::setContextProperty(const QString &name, const QVariant &value)
{
  d->m_engine->rootContext()->setContextProperty(name, value);
}

void DeclarativeWidgetsDocument::setContextProperty(const QString &name, QObject *object)
{
  d->m_engine->rootContext()->setContextProperty(name, object);
}

QDeclarativeEngine* DeclarativeWidgetsDocument::engine() const
{
  return d->m_engine;
}

QWidget* DeclarativeWidgetsDocument::createWidget()
{
  QObject *object = d->m_component->create();
  if (!object) {
    qWarning("Unable to create component");
    return 0;
  }

  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);

  if (declarativeObject) {
    declarativeObject->setParent(this);
    return qobject_cast<QWidget*>(declarativeObject->object());
  }

  QWidget *widget = qobject_cast<QWidget*>(object);
  if (widget)
    return widget;

  qFatal("Root Element is neither an AbstractDeclarativeObject nor a widget");
  return 0;
}
