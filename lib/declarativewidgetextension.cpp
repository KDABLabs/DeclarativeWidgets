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

#include "declarativewidgetextension.h"

#include "declarativeactionitem_p.h"
#include "defaultobjectcontainer_p.h"
#include "defaultwidgetcontainer.h"
#include "objectadaptors_p.h"
#include "widgetcontainerinterface_p.h"

#include <QAction>
#include <QEvent>
#include <QLayout>
#include <QQmlInfo>
#include <QWidget>

class WidgetContainerDelegate : public DefaultObjectContainer
{
  public:
    explicit WidgetContainerDelegate(WidgetContainerInterface *widgetContainer)
      : m_widgetContainer(widgetContainer)
    {
    }

    ~WidgetContainerDelegate()
    {
      delete m_widgetContainer;
    }

    void dataAppend(QObject *object)
    {
      DefaultObjectContainer::dataAppend(object);

      QWidget *widget = qobject_cast<QWidget*>(object);
      if (widget) {

        // restore widget flags for dialogs, menus
        const QVariant originalWindowFlags = widget->property("originalWindowFlags");
        if (originalWindowFlags.isValid() && originalWindowFlags.canConvert<Qt::WindowFlags>()) {
          widget->setParent(widget->parentWidget(), originalWindowFlags.value<Qt::WindowFlags>());
        }

        m_widgetContainer->addWidget(widget);
        return;
      }

      QLayout *layout = qobject_cast<QLayout*>(object);
      if (layout) {
        m_widgetContainer->setLayout(layout);
        return;
      }

      QAction *action = qobject_cast<QAction*>(object);
      if (action) {
        m_widgetContainer->addAction(action);
        return;
      }

      DeclarativeActionItem *actionItem = qobject_cast<DeclarativeActionItem*>(object);
      if (actionItem) {
        m_widgetContainer->addAction(actionItem->action());
        return;
      }
    }

  private:
    WidgetContainerInterface *m_widgetContainer;
};

DeclarativeWidgetExtension::DeclarativeWidgetExtension(QObject *parent)
  : DeclarativeObjectExtension(new WidgetContainerDelegate(new DefaultWidgetContainer(qobject_cast<QWidget*>(parent))), parent)
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

bool DeclarativeWidgetExtension::isVisible() const
{
  return extendedWidget()->isVisible();
}

void DeclarativeWidgetExtension::setVisible(bool visible)
{
  extendedWidget()->setVisible(visible);
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

  case QEvent::Show:
  case QEvent::Hide:
    emit visibleChanged(isVisible());
    break;

  default:
    break;
  }

  return false;
}

DeclarativeWidgetExtension::DeclarativeWidgetExtension(WidgetContainerInterface *widgetContainer, QObject *parent)
  : DeclarativeObjectExtension(new WidgetContainerDelegate(widgetContainer), parent)
{
  parent->installEventFilter(this);
}
