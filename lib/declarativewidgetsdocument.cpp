/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

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
#include "declarativecalendarwidget_p.h"
#include "declarativecolordialog_p.h"
#include "declarativedateedit_p.h"
#include "declarativedatetimeedit_p.h"
#include "declarativedeclarativecontext_p.h"
#include "declarativedeclarativeview_p.h"
#include "declarativedial_p.h"
#include "declarativedoublespinbox_p.h"
#include "declarativefiledialog_p.h"
#include "declarativefontdialog_p.h"
#include "declarativeformlayout_p.h"
#include "declarativeframe_p.h"
#include "declarativegridlayout_p.h"
#include "declarativegroupbox_p.h"
#include "declarativehboxlayout_p.h"
#include "declarativeinputdialog_p.h"
#include "declarativeitemviewextension_p.h"
#include "declarativelcdnumber_p.h"
#include "declarativemainwindowextension_p.h"
#include "declarativemenubarextension_p.h"
#include "declarativemenuextension_p.h"
#include "declarativemessagebox_p.h"
#include "declarativeplaintextedit_p.h"
#include "declarativeprogressbar_p.h"
#include "declarativescrollarea_p.h"
#include "declarativescrollbar_p.h"
#include "declarativeseparator_p.h"
#include "declarativespinbox_p.h"
#include "declarativestackedlayout_p.h"
#include "declarativestackedwidget_p.h"
#include "declarativestatusbar_p.h"
#include "declarativetabwidget_p.h"
#include "declarativetextbrowser_p.h"
#include "declarativetexteditextension_p.h"
#include "declarativetimeedit_p.h"
#include "declarativetoolbarextension_p.h"
#include "declarativevboxlayout_p.h"
#include "declarativewidgetextension.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QColumnView>
#include <QCommandLinkButton>
#include <QCoreApplication>
#include <QDebug>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDialogButtonBox>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QMenuBar>
#include <QRadioButton>
#include <QTableView>
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
  /*
  // widgets
  qmlRegisterType<DeclarativeCalendarWidget>("QtGui", 1, 0, "CalendarWidget");
  qmlRegisterType<DeclarativeCheckBox>("QtGui", 1, 0, "CheckBox");
  qmlRegisterType<DeclarativeDateEdit>("QtGui", 1, 0, "DateEdit");
  qmlRegisterType<DeclarativeDateTimeEdit>("QtGui", 1, 0, "DateTimeEdit");
  qmlRegisterType<DeclarativeDeclarativeContext>("QtGui", 1, 0, "DeclarativeContext");
  qmlRegisterType<DeclarativeContextProperty>("QtGui", 1, 0, "DeclarativeContextProperty");
  qmlRegisterType<DeclarativeDeclarativeView>("QtGui", 1, 0, "DeclarativeView");
  qmlRegisterType<DeclarativeDial>("QtGui", 1, 0, "Dial");
  qmlRegisterType<DeclarativeDoubleSpinBox>("QtGui", 1, 0, "DoubleSpinBox");
  qmlRegisterType<DeclarativeFrame>("QtGui", 1, 0, "Frame");
  qmlRegisterType<DeclarativeGroupBox>("QtGui", 1, 0, "GroupBox");
  qmlRegisterType<DeclarativeLabel>("QtGui", 1, 0, "Label");
  qmlRegisterType<DeclarativeLCDNumber>("QtGui", 1, 0, "LCDNumber");
  qmlRegisterType<DeclarativePlainTextEdit>("QtGui", 1, 0, "PlainTextEdit");
  qmlRegisterType<DeclarativeProgressBar>("QtGui", 1, 0, "ProgressBar");
  qmlRegisterType<DeclarativeScrollArea>("QtGui", 1, 0, "ScrollArea");
  qmlRegisterType<DeclarativeScrollBar>("QtGui", 1, 0, "ScrollBar");
  qmlRegisterType<DeclarativeSpinBox>("QtGui", 1, 0, "SpinBox");
  qmlRegisterType<DeclarativeStackedWidget>("QtGui", 1, 0, "StackedWidget");
  qmlRegisterType<DeclarativeStatusBarAttached>();
  qmlRegisterType<DeclarativeTabWidgetAttached>();
  qmlRegisterType<DeclarativeTextBrowser>("QtGui", 1, 0, "TextBrowser");
  qmlRegisterType<DeclarativeTimeEdit>("QtGui", 1, 0, "TimeEdit");
  */

  // objects
  qmlRegisterType<QAbstractItemModel>();
  qmlRegisterType<QAction>();
  qmlRegisterExtendedType<DeclarativeAction, DeclarativeObjectExtension>("QtGui", 1, 0, "Action");
  qmlRegisterExtendedType<DeclarativeActionItem, DeclarativeObjectExtension>("QtGui", 1, 0, "ActionItem");
  qmlRegisterExtendedType<QButtonGroup, DeclarativeButtonGroupExtension>("QtGui", 1, 0, "ButtonGroup");
  qmlRegisterType<DeclarativeContext>();
  qmlRegisterType<QItemSelectionModel>();
  qmlRegisterExtendedType<DeclarativeSeparator, DeclarativeObjectExtension>("QtGui", 1, 0, "Separator");
  qmlRegisterType<QTextDocument>();

  // layouts
  qmlRegisterExtendedType<DeclarativeFormLayout, DeclarativeFormLayoutExtension>("QtGui", 1, 0, "FormLayout");
  qmlRegisterExtendedType<DeclarativeHBoxLayout, DeclarativeHBoxLayoutExtension>("QtGui", 1, 0, "HBoxLayout");
  qmlRegisterExtendedType<DeclarativeGridLayout, DeclarativeGridLayoutExtension>("QtGui", 1, 0, "GridLayout");
  qmlRegisterExtendedType<DeclarativeStackedLayout, DeclarativeStackedLayoutExtension>("QtGui", 1, 0, "StackedLayout");
  qmlRegisterExtendedType<DeclarativeVBoxLayout, DeclarativeVBoxLayoutExtension>("QtGui", 1, 0, "VBoxLayout");

  // widgets
  qmlRegisterExtendedType<QCheckBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "CheckBox");
  qmlRegisterExtendedType<DeclarativeColorDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "ColorDialog");
  qmlRegisterExtendedType<QColumnView, DeclarativeItemViewExtension>("QtGui", 1, 0, "ColumnView");
  qmlRegisterExtendedType<QCommandLinkButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "CommandLinkButton");
  qmlRegisterExtendedType<Dialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "Dialog");
  qmlRegisterExtendedType<QDialogButtonBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "DialogButtonBox");
  qmlRegisterExtendedType<DeclarativeFileDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "FileDialog");
  qmlRegisterExtendedType<DeclarativeFontDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "FontDialog");
  qmlRegisterExtendedType<DeclarativeInputDialog, DeclarativeWidgetExtension>("QtGui", 1, 0, "InputDialog");
  qmlRegisterExtendedType<QLabel, DeclarativeWidgetExtension>("QtGui", 1, 0, "Label");
  qmlRegisterExtendedType<QLineEdit, DeclarativeWidgetExtension>("QtGui", 1, 0, "LineEdit");
  qmlRegisterExtendedType<QListView, DeclarativeItemViewExtension>("QtGui", 1, 0, "ListView");
  qmlRegisterExtendedType<QMainWindow, DeclarativeMainWindowExtension>("QtGui", 1, 0, "MainWindow");
  qmlRegisterExtendedType<Menu, DeclarativeMenuExtension>("QtGui", 1, 0, "Menu");
  qmlRegisterExtendedType<QMenuBar, DeclarativeMenuBarExtension>("QtGui", 1, 0, "MenuBar");
  qmlRegisterExtendedType<DeclarativeMessageBox, DeclarativeWidgetExtension>("QtGui", 1, 0, "MessageBox");
  qmlRegisterExtendedType<QPushButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "PushButton");
  qmlRegisterExtendedType<QRadioButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "RadioButton");
  qmlRegisterExtendedType<QSlider, DeclarativeWidgetExtension>("QtGui", 1, 0, "Slider");
  qmlRegisterExtendedType<DeclarativeStatusBar, DeclarativeStatusBarExtension>("QtGui", 1, 0, "StatusBar");
  qmlRegisterExtendedType<QTableView, DeclarativeItemViewExtension>("QtGui", 1, 0, "TableView");
  qmlRegisterExtendedType<DeclarativeTabWidget, DeclarativeTabWidgetExtension>("QtGui", 1, 0, "TabWidget");
  qmlRegisterExtendedType<QTextEdit, DeclarativeTextEditExtension>("QtGui", 1, 0, "TextEdit");
  qmlRegisterExtendedType<QToolBar, DeclarativeToolBarExtension>("QtGui", 1, 0, "ToolBar");
  qmlRegisterExtendedType<QToolButton, DeclarativeWidgetExtension>("QtGui", 1, 0, "ToolButton");
  qmlRegisterExtendedType<QTreeView, DeclarativeItemViewExtension>("QtGui", 1, 0, "TreeView");
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

  qWarning("Root element is no AbstractDeclarativeObject subclass");

  QWidget *widget = qobject_cast<QWidget*>(object);
  if (widget)
    return widget;

  qFatal("Root Element is neither ab AbstractDeclarativeObject nor a widget");
  return 0;
}
