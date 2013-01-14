#include "declarativewidgetextension.h"

#include "declarativeactionitem_p.h"
#include "objectadaptors_p.h"

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

    // restore widget flags for menus
    Menu *menu = qobject_cast<Menu*>(widget);
    if (menu)
      menu->setParent(menu->parentWidget(), menu->originalWindowFlags);

    addWidget(widget);
    return;
  }

  QLayout *layout = qobject_cast<QLayout*>(object);
  if (layout) {
    setLayout(layout);
    return;
  }

  QAction *action = qobject_cast<QAction*>(object);
  if (action) {
    addAction(action);
    return;
  }

  DeclarativeActionItem *actionItem = qobject_cast<DeclarativeActionItem*>(object);
  if (actionItem) {
    addAction(actionItem->action());
    return;
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
