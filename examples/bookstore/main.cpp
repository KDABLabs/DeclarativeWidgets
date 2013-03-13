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
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QWidget>

static QWidget *createDeclarativeWidgetsUi(BookStore *bookStore)
{
  const QUrl documentUrl = QUrl("qrc:///widgets/main.qml");

  DeclarativeWidgetsDocument *document = new DeclarativeWidgetsDocument(documentUrl, bookStore);
  QObject::connect(document->engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

  document->setContextProperty("_store", bookStore);

  QWidget *widget = document->create<QWidget>();
  if (!widget)
    qFatal("Failed to create widget from document");

  return widget;
}

static QWidget *createQtQuickUi(BookStore *bookStore)
{
  QDeclarativeView *view = new QDeclarativeView();

  QObject::connect(view->engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

  view->engine()->rootContext()->setContextProperty("_store", bookStore);

  view->setSource(QUrl("qrc:///qtquick/main.qml"));

  return view;
}

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  bool useDeclarativeWidgets = false;

  const QStringList args = app.arguments();
  if (args.count() >= 2) {
    Q_FOREACH (const QString &arg, args) {
      if (arg == "-h" || arg == "-help" || arg == "--help") {
        qDebug() << "Usage: bookstore --mode staff|customer";
        return 0;
      }
    }

    if (args.count() != 3 || args[1] != "--mode")
      qFatal("Usage: bookstore --mode staff|customer");

    if (args[2] != "staff" && args[2] != "customer")
      qFatal("Unknown mode option %s\nUsage: bookstore --mode staff|customer", qPrintable(argv[2]));

    useDeclarativeWidgets = (args[2] == "staff");
  }

  BookStore bookStore;

  QWidget *widget = useDeclarativeWidgets ? createDeclarativeWidgetsUi(&bookStore) : createQtQuickUi(&bookStore);
    
  widget->show();

  return app.exec();
}
