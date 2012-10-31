#include "declarativewidgetdocument.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QTimer>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtGui/QApplication>
#include <QtGui/QFileSystemModel>
#include <QtGui/QWidget>
#include <QDebug>

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

  DeclarativeWidgetDocument document(documentUrl);
  QObject::connect(document.engine(), SIGNAL(quit()), &app, SLOT(quit()));

  document.setContextProperty("_timer", &timer);
  document.setContextProperty("_fileSystemModel", &model);

  QWidget *widget = document.create<QWidget>();
  if (widget)
    widget->show();

  return app.exec();
}
