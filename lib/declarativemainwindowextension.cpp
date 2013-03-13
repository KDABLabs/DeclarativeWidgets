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

#include "declarativemainwindowextension_p.h"

#include <QDeclarativeInfo>
#include <QDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

DeclarativeMainWindowExtension::DeclarativeMainWindowExtension(QObject *parent)
  : DeclarativeWidgetExtension(parent)
{
}

QMainWindow *DeclarativeMainWindowExtension::extendedMainWindow() const
{
  QMainWindow *mainWindow = qobject_cast<QMainWindow*>(extendedWidget());
  Q_ASSERT(mainWindow);

  return mainWindow;
}

void DeclarativeMainWindowExtension::addWidget(QWidget *widget)
{
  QMenuBar *menuBar = qobject_cast<QMenuBar*>(widget);
  QToolBar *toolBar = qobject_cast<QToolBar*>(widget);
  QStatusBar *statusBar = qobject_cast<QStatusBar*>(widget);
  QDialog *dialog = qobject_cast<QDialog*>(widget);

  if (menuBar) {
    extendedMainWindow()->setMenuBar(menuBar);
  } else if (toolBar) {
    extendedMainWindow()->addToolBar(toolBar);
  } else if (statusBar) {
    extendedMainWindow()->setStatusBar(statusBar);
  } else if (dialog) {
    // We allow to place dialogs on the mainwindow
    dialog->setParent(extendedMainWindow(), dialog->windowFlags());
  } else if (widget) {
    if (extendedMainWindow()->centralWidget()) {
      qmlInfo(extendedMainWindow()) << "The MainWindow already contains a central widget";
      return;
    }

    extendedMainWindow()->setCentralWidget(widget);
  }
}

void DeclarativeMainWindowExtension::setLayout(QLayout *layout)
{
  Q_UNUSED(layout);
  qmlInfo(this) << "Can not set a Layout to a MainWindow";
}
