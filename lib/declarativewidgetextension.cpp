#include "declarativewidgetextension.h"

#include "declarativeactionitem_p.h"
#include "objectadaptors_p.h"

#include <QAction>
#include <QDeclarativeInfo>
#include <QEvent>
#include <QLayout>
#include <QWidget>

DeclarativeWidgetExtension::DeclarativeWidgetExtension(QObject *parent)
  : DeclarativeObjectExtension(parent)
{
  parent->installEventFilter(this);
}

QWidget *DeclarativeWidgetExtension::extendedWidget() const
{
  QWidget *parentWidget = qobject_cast<QWidget*>(parent());
  Q_ASSERT(parentWidget);
  Q_UNUSED(parentWidget);

  return parentWidget;
}

int DeclarativeWidgetExtension::x() const
{
  return extendedWidget()->x();
}

void DeclarativeWidgetExtension::setX(int value)
{
  QWidget *widget = extendedWidget();

  if (value == widget->x())
    return;

  QRect geometry = widget->geometry();
  geometry.moveLeft(value);
  widget->setGeometry(geometry);
}

int DeclarativeWidgetExtension::y() const
{
  return extendedWidget()->y();
}

void DeclarativeWidgetExtension::setY(int value)
{
  QWidget *widget = extendedWidget();

  if (value == widget->y())
    return;

  QRect geometry = widget->geometry();
  geometry.moveTop(value);
  widget->setGeometry(geometry);
}

int DeclarativeWidgetExtension::width() const
{
  return extendedWidget()->width();
}

void DeclarativeWidgetExtension::setWidth(int value)
{
  QWidget *widget = extendedWidget();

  if (value == widget->width())
    return;

  QRect geometry = widget->geometry();
  geometry.setWidth(value);
  widget->setGeometry(geometry);
}

int DeclarativeWidgetExtension::height() const
{
  return extendedWidget()->height();
}

void DeclarativeWidgetExtension::setHeight(int value)
{
  QWidget *widget = extendedWidget();

  if (value == widget->height())
    return;

  QRect geometry = widget->geometry();
  geometry.setHeight(value);
  widget->setGeometry(geometry);
}

QRect DeclarativeWidgetExtension::geometry() const
{
  return extendedWidget()->geometry();
}

void DeclarativeWidgetExtension::setGeometry(const QRect &rect)
{
  QWidget *widget = extendedWidget();

  if (rect == widget->geometry())
    return;

  widget->setGeometry(rect);
}

bool DeclarativeWidgetExtension::eventFilter(QObject *watched, QEvent *event)
{
  Q_ASSERT(watched == parent());
  Q_UNUSED(watched); // release builds

  switch (event->type())
  {
  case QEvent::Move:
    emit posChanged();
    emit geometryChanged();
    break;

  case QEvent::Resize:
    emit sizeChanged();
    emit geometryChanged();
    break;

  default:
    break;
  }

  return false;
}

void DeclarativeWidgetExtension::dataAppend(QObject *object)
{
  DeclarativeObjectExtension::dataAppend(object);

  QWidget *widget = qobject_cast<QWidget*>(object);
  if (widget) {

    // restore widget flags for dialogs, menus
    const QVariant originalWindowFlags = widget->property("originalWindowFlags");
    if (originalWindowFlags.isValid() && originalWindowFlags.canConvert<Qt::WindowFlags>()) {
      widget->setParent(widget->parentWidget(), originalWindowFlags.value<Qt::WindowFlags>());
    }

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
