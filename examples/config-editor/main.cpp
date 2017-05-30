#include "configeditor.h"

#include "declarativewidgetsdocument.h"

#include <QApplication>
#include <QQmlEngine>
#include <QWidget>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  DeclarativeWidgetsDocument document(QUrl("qrc:///main.qml"));
  QObject::connect(document.engine(), SIGNAL(quit()), &app, SLOT(quit()));

  ConfigEditor editor;
  document.setContextProperty("_editor", &editor);

  QWidget *widget = document.create<QWidget>();
  if (!widget)
    qFatal("Failed to create widget from document");

  widget->show();

  return app.exec();
}
