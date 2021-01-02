/*
  declarativeobjectproxy_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Tobias Koenig <tobias.koenig@kdab.com>
  Author: Kevin Krammer <kevin.krammer@kdab.com>

  Licensees holding valid commercial KDAB DeclarativeWidgets licenses may use this file in
  accordance with DeclarativeWidgets Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DECLARATIVEOBJECTPROXY_P_H
#define DECLARATIVEOBJECTPROXY_P_H

#include <QtGlobal>
#include "abstractdeclarativeobject_p.h"

#include <QPointer>
#include <qqml.h>
#include <QQmlInfo>
#include <QVector>

template <class T>
class DeclarativeObjectProxy : public AbstractDeclarativeObject
{
  public:
    explicit DeclarativeObjectProxy(QObject *parent = 0) : AbstractDeclarativeObject(parent), m_proxiedObject(0) {}
    ~DeclarativeObjectProxy() { delete m_proxiedObject; }

    QObject *object() const {
      if (!m_proxiedObject)
        createProxiedObject();

      return m_proxiedObject.data();
    }

  protected:
    virtual void createProxiedObject() const = 0;

    void dataAppend(QObject *object)
    {
      m_children.append(object);
    }

    int dataCount() const { return m_children.count(); }
    QObject *dataAt(int index) const { return m_children.at(index); }
    void dataClear()
    {
      qDeleteAll(m_children);
      m_children.clear();
    }

  protected:
    mutable QPointer<T> m_proxiedObject;
    QVector<QObject*> m_children;
};

#endif
