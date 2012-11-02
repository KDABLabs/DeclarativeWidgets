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

#include "declarativemainwindow_p.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

DeclarativeMainWindow::DeclarativeMainWindow(QObject *parent)
  : DeclarativeWidgetProxy<QMainWindow>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeMainWindow::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  QMenuBar *menuBar = qobject_cast<QMenuBar*>(widget);
  QToolBar *toolBar = qobject_cast<QToolBar*>(widget);
  QStatusBar *statusBar = qobject_cast<QStatusBar*>(widget);
  QDialog *dialog = qobject_cast<QDialog*>(widget);

  if (menuBar) {
    m_proxiedObject->setMenuBar(menuBar);
  } else if (toolBar) {
    m_proxiedObject->addToolBar(toolBar);
  } else if (statusBar) {
    m_proxiedObject->setStatusBar(statusBar);
  } else if (dialog) {
    // We allow to place dialogs on the mainwindow
    dialog->setParent(m_proxiedObject, dialog->windowFlags());
  } else if (widget) {
    if (m_proxiedObject->centralWidget()) {
      qmlInfo(declarativeObject) << "The QMainWindow contains a central widget already";
      return;
    }

    m_proxiedObject->setCentralWidget(widget);
  }

  m_children.append(declarativeObject);
}

void DeclarativeMainWindow::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not set a QLayout to a QMainWindow";
}

CUSTOM_METAOBJECT(DeclarativeMainWindow, QMainWindow)
