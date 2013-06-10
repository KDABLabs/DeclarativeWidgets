/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include "declarativemessagebox_p.h"
#include "declarativeseparator_p.h"
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
  qmlRegisterExtendedType<DeclarativeAction, DeclarativeObjectExtension>("QtGui", 1, 0, "Action");
  qmlRegisterExtendedType<DeclarativeActionItem, DeclarativeObjectExtension>("QtGui", 1, 0, "ActionItem");
  qmlRegisterExtendedType<QButtonGroup, DeclarativeButtonGroupExtension>("QtGui", 1, 0, "ButtonGroup");
  qmlRegisterType<DeclarativeContextProperty>("QtGui", 1, 0, "DeclarativeContextProperty");
  qmlRegisterType<DeclarativeDeclarativeContext>("QtGui", 1, 0, "DeclarativeContext");
  qmlRegisterExtendedType<QFileSystemModel, DeclarativeFileSystemModelExtension>("QtGui", 1, 0, "FileSystemModel");
  qmlRegisterType<DeclarativeIcon>("QtGui", 1, 0, "Icon");
  qmlRegisterType<QItemSelectionModel>();
  qmlRegisterExtendedType<DeclarativeSeparator, DeclarativeObjectExtension>("QtGui", 1, 0, "Separator");
  qmlRegisterExtendedType<QStringListModel, DeclarativeStringListModelExtension>("QtCore", 1, 0, "StringListModel");
  qmlRegisterType<QTextDocument>();
  qmlRegisterType<QTimer>("QtCore", 1, 0, "Timer");

  // layouts
  qmlRegisterExtendedType<DeclarativeFormLayout, DeclarativeFormLayoutExtension>("QtGui", 1, 0, "FormLayout");
  qmlRegisterExtendedType<DeclarativeHBoxLayout, DeclarativeHBoxLayoutExtension>("QtGui", 1, 0, "HBoxLayout");
  qmlRegisterExtendedType<DeclarativeGridLayout, DeclarativeGridLayoutExtension>("QtGui", 1, 0, "GridLayout");
  qmlRegisterExtendedType<DeclarativeStackedLayout, DeclarativeStackedLayoutExtension>("QtGui", 1, 0, "StackedLayout");
  qmlRegisterExtendedType<DeclarativeVBoxLayout, DeclarativeVBoxLayoutExtension>("QtGui", 1, 0, "VBoxLayout");

  // widgets
  qmlRegisterExtendedType<QCalendarWidget, DeclarativeWidgetExtension>("QtGui", 1, 0, "CalendarWidget");
  qmlRegisterExtendedType<QCheckBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "CheckBox");
  qmlRegisterExtendedType<DeclarativeColorDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "ColorDialog");
  qmlRegisterExtendedType<QColumnView, DeclarativeItemViewExtension>("QtGui", 1, 0, "ColumnView");
  qmlRegisterExtendedType<QCommandLinkButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "CommandLinkButton");
  qmlRegisterExtendedType<QComboBox, DeclarativeComboBoxExtension>("QtGui", 1, 0, "ComboBox");
  qmlRegisterExtendedType<QDateEdit, DeclarativeWidgetExtension>("QtGui", 1, 0, "DateEdit");
  qmlRegisterExtendedType<QDateTimeEdit, DeclarativeWidgetExtension>("QtGui", 1, 0, "DateTimeEdit");
  qmlRegisterExtendedType<QDeclarativeView, DeclarativeDeclarativeViewExtension>("QtGui", 1, 0, "DeclarativeView");
  qmlRegisterExtendedType<QDial, DeclarativeWidgetExtension>("QtGui", 1, 0, "Dial");
  qmlRegisterExtendedType<Dialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "Dialog");
  qmlRegisterExtendedType<QDialogButtonBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "DialogButtonBox");
  qmlRegisterExtendedType<QDoubleSpinBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "DoubleSpinBox");
  qmlRegisterExtendedType<DeclarativeFileDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "FileDialog");
  qmlRegisterExtendedType<QFrame, DeclarativeWidgetExtension>("QtGui", 1, 0, "Frame");
  qmlRegisterExtendedType<DeclarativeFontDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "FontDialog");
  qmlRegisterExtendedType<QGroupBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "GroupBox");
  qmlRegisterExtendedType<DeclarativeInputDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "InputDialog");
  qmlRegisterUncreatableType<QHeaderView>("QtGui", 1, 0, "HeaderView", "");
  qmlRegisterExtendedType<QLabel, DeclarativeWidgetExtension>("QtGui", 1, 0, "Label");
  qmlRegisterExtendedType<QLineEdit, DeclarativeWidgetExtension>("QtGui", 1, 0, "LineEdit");
  qmlRegisterExtendedType<QLCDNumber, DeclarativeWidgetExtension>("QtGui", 1, 0, "LCDNumber");
  qmlRegisterExtendedType<QListView, DeclarativeItemViewExtension>("QtGui", 1, 0, "ListView");
  qmlRegisterExtendedType<QMainWindow, DeclarativeContainerWidgetExtension<MainWindowWidgetContainer> >("QtGui", 1, 0, "MainWindow");
  qmlRegisterExtendedType<Menu, DeclarativeContainerWidgetExtension<MenuWidgetContainer> >("QtGui", 1, 0, "Menu");
  qmlRegisterExtendedType<QMenuBar, DeclarativeContainerWidgetExtension<MenuBarWidgetContainer> >("QtGui", 1, 0, "MenuBar");
  qmlRegisterExtendedType<DeclarativeMessageBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "MessageBox");
  qmlRegisterExtendedType<QPlainTextEdit, DeclarativeWidgetExtension>("QtGui", 1, 0, "PlainTextEdit");
  qmlRegisterExtendedType<QProgressBar, DeclarativeWidgetExtension>("QtGui", 1, 0, "ProgressBar");
  qmlRegisterExtendedType<QPushButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "PushButton");
  qmlRegisterExtendedType<QRadioButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "RadioButton");
  qmlRegisterExtendedType<QScrollArea, DeclarativeContainerWidgetExtension<ScrollAreaWidgetContainer> >("QtGui", 1, 0, "ScrollArea");
  qmlRegisterExtendedType<QScrollBar, DeclarativeWidgetExtension>("QtGui", 1, 0, "ScrollBar");
  qmlRegisterExtendedType<QSlider, DeclarativeWidgetExtension>("QtGui", 1, 0, "Slider");
  qmlRegisterExtendedType<QStackedWidget, DeclarativeContainerWidgetExtension<StackedWidgetWidgetContainer> >("QtGui", 1, 0, "StackedWidget");
  qmlRegisterExtendedType<QSpinBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "SpinBox");
  qmlRegisterExtendedType<DeclarativeStatusBar, DeclarativeContainerWidgetExtension<StatusBarWidgetContainer> >("QtGui", 1, 0, "StatusBar");
  qmlRegisterExtendedType<QTableView, DeclarativeTableViewExtension>("QtGui", 1, 0, "TableView");
  qmlRegisterExtendedType<DeclarativeTabWidget, DeclarativeContainerWidgetExtension<TabWidgetWidgetContainer> >("QtGui", 1, 0, "TabWidget");
  qmlRegisterExtendedType<QTextBrowser, DeclarativeTextEditExtension>("QtGui", 1, 0, "TextBrowser");
  qmlRegisterExtendedType<QTextEdit, DeclarativeTextEditExtension>("QtGui", 1, 0, "TextEdit");
  qmlRegisterExtendedType<QTimeEdit, DeclarativeWidgetExtension>("QtGui", 1, 0, "TimeEdit");
  qmlRegisterExtendedType<QToolBar, DeclarativeContainerWidgetExtension<ToolBarWidgetContainer> >("QtGui", 1, 0, "ToolBar");
  qmlRegisterExtendedType<QToolButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "ToolButton");
  qmlRegisterExtendedType<QTreeView, DeclarativeTreeViewExtension>("QtGui", 1, 0, "TreeView");
  qmlRegisterExtendedType<QWebView, DeclarativeWidgetExtension>("QtGui", 1, 0, "WebView");
  qmlRegisterExtendedType<QWidget, DeclarativeWidgetExtension>("QtGui", 1, 0, "Widget");

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
