/*
  declarativeobjectextension.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativeobjectextension.h"
#include "defaultobjectcontainer_p.h"

DeclarativeObjectExtension::DeclarativeObjectExtension(QObject *parent)
  : QObject(parent)
  , m_objectContainer(new DefaultObjectContainer)
{
}

DeclarativeObjectExtension::~DeclarativeObjectExtension()
{
    delete m_objectContainer;
}

DeclarativeObjectExtension::DeclarativeObjectExtension(ObjectContainerInterface *objectContainer, QObject *parent)
  : QObject(parent)
  , m_objectContainer(objectContainer)
{
}

QQmlListProperty<QObject> DeclarativeObjectExtension::data()
{
  return QQmlListProperty<QObject>(this, 0, DeclarativeObjectExtension::data_append,
                                            DeclarativeObjectExtension::data_count,
                                            DeclarativeObjectExtension::data_at,
                                            DeclarativeObjectExtension::data_clear);
}

void DeclarativeObjectExtension::data_append(QQmlListProperty<QObject> *property, QObject *object)
{
  if (!object)
    return;

  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that && that->m_objectContainer)
    that->m_objectContainer->dataAppend(object);
  else
    qWarning("cast went wrong in data_append");
}

int DeclarativeObjectExtension::data_count(QQmlListProperty<QObject> *property)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that && that->m_objectContainer)
    return that->m_objectContainer->dataCount();
  else {
    qWarning("cast went wrong in data_count");
    return 0;
  }
}

QObject* DeclarativeObjectExtension::data_at(QQmlListProperty<QObject> *property, int index)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that && that->m_objectContainer)
    return that->m_objectContainer->dataAt(index);
  else {
    qWarning("cast went wrong in data_at");
    return 0;
  }
}

void DeclarativeObjectExtension::data_clear(QQmlListProperty<QObject> *property)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that && that->m_objectContainer)
    that->m_objectContainer->dataClear();
  else
    qWarning("cast went wrong in data_clear");
}
