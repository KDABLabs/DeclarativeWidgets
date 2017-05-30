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

#include "extensionplugin_plugin.h"

#include "declarativeactionitem_p.h"
#include "declarativeaction_p.h"
#include "declarativebuttongroupextension_p.h"
#include "declarativecolordialog_p.h"
#include "declarativecomboboxextension_p.h"
#include "declarativecontainerwidgetextension_p.h"
#include "declarativedeclarativecontext_p.h"
#if defined(QT5_PORT)
#include "declarativedeclarativeviewextension_p.h"
#else
#warning NOT PORTED YET
#endif
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
#include "declarativetabstops_p.h"
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
#include <QDateTimeEdit>
#include <QQuickView>
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
#include <QScrollArea>
#include <QScrollBar>
#include <QStackedWidget>
#include <QStringListModel>
#include <QTableView>
#include <QTextBrowser>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QWebEngineView>

#include <qqml.h>

// @uri QtWidgets
void ExtensionpluginPlugin::registerTypes(const char *uri)
{
  Q_ASSERT(uri == QLatin1String("QtWidgets"));

  // objects
  qmlRegisterType<QAbstractItemModel>();
  qmlRegisterType<QAction>();
  qmlRegisterExtendedType<DeclarativeAction, DeclarativeObjectExtension>(uri, 1, 0, "Action");
  qmlRegisterExtendedType<DeclarativeActionItem, DeclarativeObjectExtension>(uri, 1, 0, "ActionItem");
  qmlRegisterExtendedType<QButtonGroup, DeclarativeButtonGroupExtension>(uri, 1, 0, "ButtonGroup");
  qmlRegisterType<DeclarativeContextProperty>(uri, 1, 0, "DeclarativeContextProperty");
  qmlRegisterType<DeclarativeDeclarativeContext>(uri, 1, 0, "DeclarativeContext");
  qmlRegisterExtendedType<QFileSystemModel, DeclarativeFileSystemModelExtension>(uri, 1, 0, "FileSystemModel");
  qmlRegisterType<DeclarativeIcon>(uri, 1, 0, "Icon");
  qmlRegisterType<QItemSelectionModel>();
  qmlRegisterExtendedType<DeclarativeSeparator, DeclarativeObjectExtension>(uri, 1, 0, "Separator");
  qmlRegisterExtendedType<QStringListModel, DeclarativeStringListModelExtension>("QtCore", 1, 0, "StringListModel");
  qmlRegisterType<DeclarativeTabStops>("QtWidgets", 1, 0, "TabStops");
  qmlRegisterType<QTextDocument>();
  qmlRegisterType<QTimer>("QtCore", 1, 0, "Timer");

  // layouts
  qmlRegisterExtendedType<DeclarativeFormLayout, DeclarativeFormLayoutExtension>(uri, 1, 0, "FormLayout");
  qmlRegisterExtendedType<DeclarativeHBoxLayout, DeclarativeHBoxLayoutExtension>(uri, 1, 0, "HBoxLayout");
  qmlRegisterExtendedType<DeclarativeGridLayout, DeclarativeGridLayoutExtension>(uri, 1, 0, "GridLayout");
  qmlRegisterExtendedType<DeclarativeStackedLayout, DeclarativeStackedLayoutExtension>(uri, 1, 0, "StackedLayout");
  qmlRegisterExtendedType<DeclarativeVBoxLayout, DeclarativeVBoxLayoutExtension>(uri, 1, 0, "VBoxLayout");

  // widgets
  qmlRegisterExtendedType<QCalendarWidget, DeclarativeWidgetExtension>(uri, 1, 0, "CalendarWidget");
  qmlRegisterExtendedType<QCheckBox, DeclarativeWidgetExtension>(uri, 1, 0, "CheckBox");
  qmlRegisterExtendedType<DeclarativeColorDialog, DeclarativeWidgetExtension>(uri, 1, 0, "ColorDialog");
  qmlRegisterExtendedType<QColumnView, DeclarativeItemViewExtension>(uri, 1, 0, "ColumnView");
  qmlRegisterExtendedType<QCommandLinkButton, DeclarativeWidgetExtension>(uri, 1, 0, "CommandLinkButton");
  qmlRegisterExtendedType<QComboBox, DeclarativeComboBoxExtension>(uri, 1, 0, "ComboBox");
  qmlRegisterExtendedType<QDateEdit, DeclarativeWidgetExtension>(uri, 1, 0, "DateEdit");
  qmlRegisterExtendedType<QDateTimeEdit, DeclarativeWidgetExtension>(uri, 1, 0, "DateTimeEdit");
  qmlRegisterExtendedType<QQuickView, DeclarativeDeclarativeViewExtension>(uri, 1, 0, "DeclarativeView");
  qmlRegisterExtendedType<QDial, DeclarativeWidgetExtension>(uri, 1, 0, "Dial");
  qmlRegisterExtendedType<Dialog, DeclarativeWidgetExtension>(uri, 1, 0, "Dialog");
  qmlRegisterExtendedType<QDialogButtonBox, DeclarativeWidgetExtension>(uri, 1, 0, "DialogButtonBox");
  qmlRegisterExtendedType<QDoubleSpinBox, DeclarativeWidgetExtension>(uri, 1, 0, "DoubleSpinBox");
  qmlRegisterExtendedType<DeclarativeFileDialog, DeclarativeWidgetExtension>(uri, 1, 0, "FileDialog");
  qmlRegisterExtendedType<QFrame, DeclarativeWidgetExtension>(uri, 1, 0, "Frame");
  qmlRegisterExtendedType<DeclarativeFontDialog, DeclarativeWidgetExtension>(uri, 1, 0, "FontDialog");
  qmlRegisterExtendedType<QGroupBox, DeclarativeWidgetExtension>(uri, 1, 0, "GroupBox");
  qmlRegisterExtendedType<DeclarativeInputDialog, DeclarativeWidgetExtension>(uri, 1, 0, "InputDialog");
  qmlRegisterUncreatableType<QHeaderView>(uri, 1, 0, "HeaderView", "");
  qmlRegisterExtendedType<QLabel, DeclarativeWidgetExtension>(uri, 1, 0, "Label");
  qmlRegisterExtendedType<QLineEdit, DeclarativeWidgetExtension>(uri, 1, 0, "LineEdit");
  qmlRegisterExtendedType<QLCDNumber, DeclarativeWidgetExtension>(uri, 1, 0, "LCDNumber");
  qmlRegisterExtendedType<QListView, DeclarativeItemViewExtension>(uri, 1, 0, "ListView");
  qmlRegisterExtendedType<QMainWindow, DeclarativeContainerWidgetExtension<MainWindowWidgetContainer> >(uri, 1, 0, "MainWindow");
  qmlRegisterExtendedType<Menu, DeclarativeContainerWidgetExtension<MenuWidgetContainer> >(uri, 1, 0, "Menu");
  qmlRegisterExtendedType<QMenuBar, DeclarativeContainerWidgetExtension<MenuBarWidgetContainer> >(uri, 1, 0, "MenuBar");
  qmlRegisterExtendedType<DeclarativeMessageBox, DeclarativeWidgetExtension>(uri, 1, 0, "MessageBox");
  qmlRegisterExtendedType<QPlainTextEdit, DeclarativeWidgetExtension>(uri, 1, 0, "PlainTextEdit");
  qmlRegisterExtendedType<QProgressBar, DeclarativeWidgetExtension>(uri, 1, 0, "ProgressBar");
  qmlRegisterExtendedType<QPushButton, DeclarativeWidgetExtension>(uri, 1, 0, "PushButton");
  qmlRegisterExtendedType<QRadioButton, DeclarativeWidgetExtension>(uri, 1, 0, "RadioButton");
  qmlRegisterExtendedType<QScrollArea, DeclarativeContainerWidgetExtension<ScrollAreaWidgetContainer> >(uri, 1, 0, "ScrollArea");
  qmlRegisterExtendedType<QScrollBar, DeclarativeWidgetExtension>(uri, 1, 0, "ScrollBar");
  qmlRegisterExtendedType<QSlider, DeclarativeWidgetExtension>(uri, 1, 0, "Slider");
  qmlRegisterExtendedType<QStackedWidget, DeclarativeContainerWidgetExtension<StackedWidgetWidgetContainer> >(uri, 1, 0, "StackedWidget");
  qmlRegisterExtendedType<QSpinBox, DeclarativeWidgetExtension>(uri, 1, 0, "SpinBox");
  qmlRegisterExtendedType<DeclarativeStatusBar, DeclarativeContainerWidgetExtension<StatusBarWidgetContainer> >(uri, 1, 0, "StatusBar");
  qmlRegisterExtendedType<QTableView, DeclarativeTableViewExtension>(uri, 1, 0, "TableView");
  qmlRegisterExtendedType<DeclarativeTabWidget, DeclarativeContainerWidgetExtension<TabWidgetWidgetContainer> >(uri, 1, 0, "TabWidget");
  qmlRegisterExtendedType<QTextBrowser, DeclarativeTextEditExtension>(uri, 1, 0, "TextBrowser");
  qmlRegisterExtendedType<QTextEdit, DeclarativeTextEditExtension>(uri, 1, 0, "TextEdit");
  qmlRegisterExtendedType<QTimeEdit, DeclarativeWidgetExtension>(uri, 1, 0, "TimeEdit");
  qmlRegisterExtendedType<QToolBar, DeclarativeContainerWidgetExtension<ToolBarWidgetContainer> >(uri, 1, 0, "ToolBar");
  qmlRegisterExtendedType<QToolButton, DeclarativeWidgetExtension>(uri, 1, 0, "ToolButton");
  qmlRegisterExtendedType<QTreeView, DeclarativeTreeViewExtension>(uri, 1, 0, "TreeView");
  qmlRegisterExtendedType<QWebEngineView, DeclarativeWidgetExtension>(uri, 1, 0, "WebEngineView");
  qmlRegisterExtendedType<QWidget, DeclarativeWidgetExtension>(uri, 1, 0, "Widget");
}
