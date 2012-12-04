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
#include "declarativebuttongroup_p.h"
#include "declarativecalendarwidget_p.h"
#include "declarativecheckbox_p.h"
#include "declarativecolordialog_p.h"
#include "declarativecolumnview_p.h"
#include "declarativecommandlinkbutton_p.h"
#include "declarativedateedit_p.h"
#include "declarativedatetimeedit_p.h"
#include "declarativedeclarativeview_p.h"
#include "declarativedialogbuttonbox_p.h"
#include "declarativedialog_p.h"
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
#include "declarativelabel_p.h"
#include "declarativelcdnumber_p.h"
#include "declarativelineedit_p.h"
#include "declarativelistview_p.h"
#include "declarativemainwindow_p.h"
#include "declarativemenubar_p.h"
#include "declarativemenu_p.h"
#include "declarativemessagebox_p.h"
#include "declarativeplaintextedit_p.h"
#include "declarativeprogressbar_p.h"
#include "declarativepushbutton_p.h"
#include "declarativeradiobutton_p.h"
#include "declarativescrollarea_p.h"
#include "declarativescrollbar_p.h"
#include "declarativeseparator_p.h"
#include "declarativeslider_p.h"
#include "declarativespinbox_p.h"
#include "declarativestackedlayout_p.h"
#include "declarativestackedwidget_p.h"
#include "declarativestatusbar_p.h"
#include "declarativetableview_p.h"
#include "declarativetabwidget_p.h"
#include "declarativetextbrowser_p.h"
#include "declarativetextedit_p.h"
#include "declarativetimeedit_p.h"
#include "declarativetoolbar_p.h"
#include "declarativetoolbutton_p.h"
#include "declarativetreeview_p.h"
#include "declarativevboxlayout_p.h"
#include "declarativewebview_p.h"
#include "declarativewidget_p.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>

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
  qmlRegisterType<QAbstractItemModel>();
  qmlRegisterType<QItemSelectionModel>();

  // objects
  qmlRegisterType<QAction>();
  qmlRegisterType<DeclarativeAction>("QtGui", 1, 0, "Action");
  qmlRegisterType<DeclarativeActionItem>("QtGui", 1, 0, "ActionItem");
  qmlRegisterType<DeclarativeButtonGroup>("QtGui", 1, 0, "ButtonGroup");
  qmlRegisterType<DeclarativeSeparator>("QtGui", 1, 0, "Separator");

  // layouts
  qmlRegisterType<DeclarativeBoxLayoutAttached>();
  qmlRegisterType<DeclarativeFormLayoutAttached>();
  qmlRegisterType<DeclarativeGridLayoutAttached>();
  qmlRegisterType<DeclarativeFormLayout>("QtGui", 1, 0, "FormLayout");
  qmlRegisterType<DeclarativeGridLayout>("QtGui", 1, 0, "GridLayout");
  qmlRegisterType<DeclarativeHBoxLayout>("QtGui", 1, 0, "HBoxLayout");
  qmlRegisterType<DeclarativeStackedLayout>("QtGui", 1, 0, "StackedLayout");
  qmlRegisterType<DeclarativeVBoxLayout>("QtGui", 1, 0, "VBoxLayout");

  // widgets
  qmlRegisterType<DeclarativeCalendarWidget>("QtGui", 1, 0, "CalendarWidget");
  qmlRegisterType<DeclarativeCheckBox>("QtGui", 1, 0, "CheckBox");
  qmlRegisterType<DeclarativeColorDialogAttached>();
  qmlRegisterType<DeclarativeColorDialog>("QtGui", 1, 0, "ColorDialog");
  qmlRegisterType<DeclarativeColumnView>("QtGui", 1, 0, "ColumnView");
  qmlRegisterType<DeclarativeCommandLinkButton>("QtGui", 1, 0, "CommandLinkButton");
  qmlRegisterType<DeclarativeDateEdit>("QtGui", 1, 0, "DateEdit");
  qmlRegisterType<DeclarativeDateTimeEdit>("QtGui", 1, 0, "DateTimeEdit");
  qmlRegisterType<DeclarativeDeclarativeView>("QtGui", 1, 0, "DeclarativeView");
  qmlRegisterType<DeclarativeDial>("QtGui", 1, 0, "Dial");
  qmlRegisterType<DeclarativeDialog>("QtGui", 1, 0, "Dialog");
  qmlRegisterType<DeclarativeDialogButtonBox>("QtGui", 1, 0, "DialogButtonBox");
  qmlRegisterType<DeclarativeDoubleSpinBox>("QtGui", 1, 0, "DoubleSpinBox");
  qmlRegisterType<DeclarativeFileDialogAttached>();
  qmlRegisterType<DeclarativeFileDialog>("QtGui", 1, 0, "FileDialog");
  qmlRegisterType<DeclarativeFontDialogAttached>();
  qmlRegisterType<DeclarativeFontDialog>("QtGui", 1, 0, "FontDialog");
  qmlRegisterType<DeclarativeFrame>("QtGui", 1, 0, "Frame");
  qmlRegisterType<DeclarativeGroupBox>("QtGui", 1, 0, "GroupBox");
  qmlRegisterType<DeclarativeInputDialogAttached>();
  qmlRegisterType<DeclarativeInputDialog>("QtGui", 1, 0, "InputDialog");
  qmlRegisterType<DeclarativeLabel>("QtGui", 1, 0, "Label");
  qmlRegisterType<DeclarativeLCDNumber>("QtGui", 1, 0, "LCDNumber");
  qmlRegisterType<DeclarativeLineEdit>("QtGui", 1, 0, "LineEdit");
  qmlRegisterType<DeclarativeListView>("QtGui", 1, 0, "ListView");
  qmlRegisterType<DeclarativeMainWindow>("QtGui", 1, 0, "MainWindow");
  qmlRegisterType<DeclarativeMenu>("QtGui", 1, 0, "Menu");
  qmlRegisterType<DeclarativeMenuBar>("QtGui", 1, 0, "MenuBar");
  qmlRegisterType<DeclarativeMessageBoxAttached>();
  qmlRegisterType<DeclarativeMessageBox>("QtGui", 1, 0, "MessageBox");
  qmlRegisterType<QTextDocument>();
  qmlRegisterType<DeclarativePlainTextEdit>("QtGui", 1, 0, "PlainTextEdit");
  qmlRegisterType<DeclarativeProgressBar>("QtGui", 1, 0, "ProgressBar");
  qmlRegisterType<DeclarativePushButton>("QtGui", 1, 0, "PushButton");
  qmlRegisterType<DeclarativeRadioButton>("QtGui", 1, 0, "RadioButton");
  qmlRegisterType<DeclarativeScrollArea>("QtGui", 1, 0, "ScrollArea");
  qmlRegisterType<DeclarativeScrollBar>("QtGui", 1, 0, "ScrollBar");
  qmlRegisterType<DeclarativeSlider>("QtGui", 1, 0, "Slider");
  qmlRegisterType<DeclarativeSpinBox>("QtGui", 1, 0, "SpinBox");
  qmlRegisterType<DeclarativeStackedWidget>("QtGui", 1, 0, "StackedWidget");
  qmlRegisterType<DeclarativeStatusBarAttached>();
  qmlRegisterType<DeclarativeStatusBar>("QtGui", 1, 0, "StatusBar");
  qmlRegisterType<DeclarativeTableView>("QtGui", 1, 0, "TableView");
  qmlRegisterType<DeclarativeTabWidgetAttached>();
  qmlRegisterType<DeclarativeTabWidget>("QtGui", 1, 0, "TabWidget");
  qmlRegisterType<DeclarativeTextBrowser>("QtGui", 1, 0, "TextBrowser");
  qmlRegisterType<DeclarativeTextEdit>("QtGui", 1, 0, "TextEdit");
  qmlRegisterType<DeclarativeTimeEdit>("QtGui", 1, 0, "TimeEdit");
  qmlRegisterType<DeclarativeToolBar>("QtGui", 1, 0, "ToolBar");
  qmlRegisterType<DeclarativeToolButton>("QtGui", 1, 0, "ToolButton");
  qmlRegisterType<DeclarativeTreeView>("QtGui", 1, 0, "TreeView");
  qmlRegisterType<DeclarativeWebView>("QtGui", 1, 0, "WebView");
  qmlRegisterType<DeclarativeWidget>("QtGui", 1, 0, "Widget");

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

  if (!declarativeObject) {
    qWarning("Root element is no AbstractDeclarativeObject subclass");
    return 0;
  }

  declarativeObject->setParent(this);

  return qobject_cast<QWidget*>(declarativeObject->object());
}
