#include "declarativewidgetdocument.h"

#include <QtCore/QTimer>
#include <QtGui/QApplication>
#include <QtGui/QWidget>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QTimer timer;
  timer.setInterval(1000);
  timer.start();

  DeclarativeWidgetDocument document(QUrl("test.qml"));
  //DeclarativeWidgetDocument document(QUrl("animation.qml"));
  document.setContextProperty("_timer", &timer);

  QWidget *widget = document.create<QWidget>();
  if (widget)
    widget->show();

  return app.exec();
}
