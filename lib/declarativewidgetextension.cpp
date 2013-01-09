#include "declarativewidgetextension.h"

#include "abstractdeclarativeobject_p.h"

#include <QAction>
#include <QDeclarativeInfo>
#include <QLayout>
#include <QWidget>

DeclarativeWidgetExtension::DeclarativeWidgetExtension(QObject *parent)
  : DeclarativeObjectExtension(parent)
{
}

QWidget *DeclarativeWidgetExtension::extendedWidget() const
{
  QWidget *parentWidget = qobject_cast<QWidget*>(parent());
  Q_ASSERT(parentWidget);
  Q_UNUSED(parentWidget);

  return parentWidget;
}

void DeclarativeWidgetExtension::dataAppend(QObject *object)
{
  DeclarativeObjectExtension::dataAppend(object);

  QWidget *widget = qobject_cast<QWidget*>(object);
  if (widget) {
    addWidget(widget);
    return;
  }

  QLayout *layout = qobject_cast<QLayout*>(object);
  if (layout) {
    setLayout(layout);
    return;
  }

  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
  if (declarativeObject) {
    QAction *action = qobject_cast<QAction*>(declarativeObject->object());
    if (action) {
      addAction(action);
      return;
    }
  }
}

void DeclarativeWidgetExtension::addAction(QAction *action)
{
  extendedWidget()->addAction(action);
}

void DeclarativeWidgetExtension::setLayout(QLayout *layout)
{
  if (extendedWidget()->layout()){
    qmlInfo(this) << "Cannot add a second layout";
    return;
  }

  extendedWidget()->setLayout(layout);
}

void DeclarativeWidgetExtension::addWidget(QWidget *widget)
{
  widget->setParent(extendedWidget());
}
