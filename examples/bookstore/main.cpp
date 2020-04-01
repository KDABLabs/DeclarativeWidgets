/*
  main.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer <kevin.krammer@kdab.com>
  Author: Nathan Collins <nathan.collins@kdab.com>

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

#include "bookstore.h"

#include <QApplication>
#include <QDebug>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickWidget>
#include <QWidget>

static QWidget *createDeclarativeWidgetsUi(BookStore *bookStore, const QString &fileName)
{
  const QUrl documentUrl = QUrl(QString("qrc:///widgets/%1").arg(fileName));

  QQmlEngine engine;
#ifdef Q_OS_MACOS
  engine.addImportPath(QStringLiteral("%1/../PlugIns").arg(QCoreApplication::applicationDirPath()));
#else
  engine.addImportPath(PLUGIN_IMPORT_PATH);
#endif
  engine.rootContext()->setContextProperty("_store", bookStore);
  QObject::connect(&engine, &QQmlEngine::quit, QCoreApplication::instance(), &QCoreApplication::quit);

  QQmlComponent component(&engine, documentUrl, bookStore);
  QWidget *widget = qobject_cast<QWidget*>(component.create());
  if (!widget)
    qFatal("Failed to create widget from QML");

  return widget;
}

static QWidget *createQtQuickUi(BookStore *bookStore, const QString &fileName)
{
  QQuickWidget *view = new QQuickWidget();

  QObject::connect(view->engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

  view->engine()->rootContext()->setContextProperty("_store", bookStore);

  view->setSource(QUrl(QString("qrc:///qtquick/%1").arg(fileName)));

  return view;
}

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QString fileName = "developer.qml";
  bool useDeclarativeWidgets = true;

  const QStringList args = app.arguments();
  if (args.count() >= 2) {
    Q_FOREACH (const QString &arg, args) {
      if (arg == "-h" || arg == "-help" || arg == "--help") {
        qDebug() << "Usage: bookstore --mode admin|staff|shop";
        return 0;
      }
    }

    if (args.count() != 3 || args[1] != "--mode")
      qFatal("Usage: bookstore --mode admin|staff|shop");

    const QString mode = args[2].toLower();
    if (mode != "admin" && mode != "staff" && mode != "shop")
      qFatal("Unknown mode option %s\nUsage: bookstore --mode admin|staff|shop", qPrintable(mode));

    useDeclarativeWidgets = (mode != "shop");
    fileName = mode + ".qml";
  }

  fileName = fileName.left(1).toUpper() + fileName.mid(1);

  BookStore bookStore;

  QWidget *widget = useDeclarativeWidgets ? createDeclarativeWidgetsUi(&bookStore, fileName) : createQtQuickUi(&bookStore, fileName);
    
  widget->show();

  return app.exec();
}
