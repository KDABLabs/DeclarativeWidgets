#include "declarativewidgetdocument.h"

#include <QtGui/QApplication>
#include <QtGui/QLabel>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  DeclarativeWidgetDocument document(QUrl("test.qml"));

  QWidget *widget = document.create<QWidget>();
  if (widget)
    widget->show();

  return app.exec();
}
