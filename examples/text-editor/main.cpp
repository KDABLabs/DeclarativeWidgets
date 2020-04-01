/*
  main.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer <kevin.krammer@kdab.com>

  Licensees holding valid commercial KDAB DeclarativeWidgets licenses may use this file in
  accordance with DeclarativeWidgets Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "editor.h"

#include <QApplication>
#include <QDebug>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QWidget>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  const QUrl documentUrl = QUrl("qrc:///main.qml");

  QQmlEngine engine;
#ifdef Q_OS_MACOS
  engine.addImportPath(QStringLiteral("%1/../PlugIns").arg(QCoreApplication::applicationDirPath()));
#else
  engine.addImportPath(PLUGIN_IMPORT_PATH);
#endif
  Editor editor;
  engine.rootContext()->setContextProperty("_editor", &editor);
  QObject::connect(&engine, &QQmlEngine::quit, QCoreApplication::instance(), &QCoreApplication::quit);

  QQmlComponent component(&engine, documentUrl);
  QWidget *widget = qobject_cast<QWidget*>(component.create());
  if (!widget)
    qFatal("Failed to create widget from QML");
    
  widget->show();

  return app.exec();
}
