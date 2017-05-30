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

#include "bookstore.h"

#include "declarativewidgetsdocument.h"

#include <QApplication>
#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QWidget>

static QWidget *createDeclarativeWidgetsUi(BookStore *bookStore, const QString &fileName)
{
  const QUrl documentUrl = QUrl(QString("qrc:///widgets/%1").arg(fileName));

  DeclarativeWidgetsDocument *document = new DeclarativeWidgetsDocument(documentUrl, bookStore);
  QObject::connect(document->engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

  document->setContextProperty("_store", bookStore);

  QWidget *widget = document->create<QWidget>();
  if (!widget)
    qFatal("Failed to create widget from document");

  return widget;
}

static QWidget *createQtQuickUi(BookStore *bookStore, const QString &fileName)
{
  QQuickView *view = new QQuickView();

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
