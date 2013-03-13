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

#include <QApplication>
#include <QDebug>
#include <QDeclarativeEngine>
#include <QDir>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QTimer>
#include <QWidget>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  const QStringList arguments = app.arguments();
  if (arguments.count() < 2) {
      qWarning("Missing QML file argument. Usage: qmlwidgets <qmlfile>");
      return -1;
  }

  QTimer timer;
  timer.setInterval(1000);
  timer.start();

  const QFileInfo qmlFile(QDir::current(), arguments[1]);
  const QUrl documentUrl = QUrl::fromLocalFile(qmlFile.absoluteFilePath());

  QFileSystemModel model;
  model.setRootPath("/");

  DeclarativeWidgetsDocument document(documentUrl);
  QObject::connect(document.engine(), SIGNAL(quit()), &app, SLOT(quit()));

  document.setContextProperty("_timer", &timer);
  document.setContextProperty("_fileSystemModel", &model);

  QWidget *widget = document.create<QWidget>();
  if (widget)
    widget->show();

  return app.exec();
}
