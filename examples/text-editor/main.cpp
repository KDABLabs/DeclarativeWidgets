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

#include "editor.h"

#include "declarativewidgetsdocument.h"

#include <QApplication>
#include <QDebug>
#include <QDeclarativeEngine>
#include <QWidget>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  const QUrl documentUrl = QUrl("qrc:///main.qml");

  DeclarativeWidgetsDocument document(documentUrl);
  QObject::connect(document.engine(), SIGNAL(quit()), &app, SLOT(quit()));

  Editor editor;
  document.setContextProperty("_editor", &editor);

  QWidget *widget = document.create<QWidget>();
  if (!widget)
    qFatal("Failed to create widget from document");
    
  widget->show();

  return app.exec();
}
