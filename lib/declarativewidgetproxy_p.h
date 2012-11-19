/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

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

#ifndef DECLARATIVEWIDGETPROXY_P_H
#define DECLARATIVEWIDGETPROXY_P_H

#include "declarativeobjectproxy_p.h"

#include "declarativeactionitem_p.h"

#include <QAction>
#include <QLayout>

template <class T>
class DeclarativeWidgetProxy : public DeclarativeObjectProxy<T>
{
  public:
    explicit DeclarativeWidgetProxy(QObject *parent = 0) : DeclarativeObjectProxy<T>(parent) {}

  protected:
    void dataAppend(QObject *object)
    {
        AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
        if (declarativeObject) {
          QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
          if (widget) {
            addWidget(widget, declarativeObject);
            return;
          }

          QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
          if (layout) {
            // TODO: error when widget is set

            if (DeclarativeObjectProxy<T>::m_proxiedObject->layout()) {
              qmlInfo(this) << "Can not add a second Layout";
              return;
            }

            setLayout(layout, declarativeObject);
            return;
          }

          DeclarativeActionItem *declarativeActionItem = dynamic_cast<DeclarativeActionItem*>(object);
          if (declarativeActionItem) {
            addAction(qobject_cast<ActionItem*>(declarativeActionItem->object())->action(), declarativeObject);
            return;
          }

          QAction *action = qobject_cast<QAction*>(declarativeObject->object());
          if (action) {
            addAction(action, declarativeObject);
            return;
          }

          addQObject(declarativeObject->object(), declarativeObject);
          return;
        }

        DeclarativeObjectProxy<T>::dataAppend(object);
    }

    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
    {
      Q_UNUSED(declarativeObject);
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      widget->setParent(DeclarativeObjectProxy<T>::m_proxiedObject, widget->windowFlags());
    }

    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->setLayout(layout);
    }

    virtual void addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->addAction(action);
    }

    virtual void addQObject(QObject *object, AbstractDeclarativeObject *declarativeObject)
    {
      object->setParent(DeclarativeObjectProxy<T>::m_proxiedObject);
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
    }
};

#endif
