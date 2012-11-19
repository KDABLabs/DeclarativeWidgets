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

#ifndef DECLARATIVELAYOUTPROXY_P_H
#define DECLARATIVELAYOUTPROXY_P_H

#include "declarativeobjectproxy_p.h"

#include <QLayout>
#include <QWidget>

template <class T>
class DeclarativeLayoutProxy : public DeclarativeObjectProxy<T>
{
  public:
    explicit DeclarativeLayoutProxy(QObject *parent = 0) : DeclarativeObjectProxy<T>(parent) {}

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
          addLayout(layout, declarativeObject);
          return;
        }
      }

      DeclarativeObjectProxy<T>::dataAppend(object);
    }

    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->addWidget(widget);
    }

    virtual void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject) = 0;
};

#endif
