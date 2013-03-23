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

#include "mainwindowwidgetcontainer_p.h"

#include <QDeclarativeInfo>
#include <QDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

MainWindowWidgetContainer::MainWindowWidgetContainer(QObject *parent)
  : DefaultWidgetContainer(qobject_cast<QMainWindow*>(parent))
{
  Q_ASSERT(m_widget);
}

void MainWindowWidgetContainer::addWidget(QWidget *widget)
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
      qmlInfo(m_widget) << "The MainWindow already contains a central widget";
      return;
    }

    extendedMainWindow()->setCentralWidget(widget);
  }
}

void MainWindowWidgetContainer::setLayout(QLayout *layout)
{
  Q_UNUSED(layout);
  qmlInfo(m_widget) << "Can not set a Layout to a MainWindow";
}

QMainWindow *MainWindowWidgetContainer::extendedMainWindow() const
{
  return static_cast<QMainWindow*>(m_widget);
}
