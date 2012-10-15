#include "declarativewidgetdocument.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QTimer>
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QDebug>
int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  const QStringList arguments = app.arguments();
  if (arguments.count() < 2) {
      qFatal("Missing QML file argument. Usage: qmlwidgets <qmlfile>");
      return -1;
  }

  QTimer timer;
  timer.setInterval(1000);
  timer.start();

  const QFileInfo qmlFile(QDir::current(), arguments[1]);
  const QUrl documentUrl = QUrl::fromLocalFile(qmlFile.absoluteFilePath());

  DeclarativeWidgetDocument document(documentUrl);
  document.setContextProperty("_timer", &timer);

  QWidget *widget = document.create<QWidget>();
  if (widget)
    widget->show();

  return app.exec();
}
