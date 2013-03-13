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

#include "declarativeobjectextension.h"

DeclarativeObjectExtension::DeclarativeObjectExtension(QObject *parent)
  : QObject(parent)
{
}

DeclarativeObjectExtension::~DeclarativeObjectExtension()
{
}

QDeclarativeListProperty<QObject> DeclarativeObjectExtension::data()
{
  return QDeclarativeListProperty<QObject>(this, 0, DeclarativeObjectExtension::data_append,
                                                    DeclarativeObjectExtension::data_count,
                                                    DeclarativeObjectExtension::data_at,
                                                    DeclarativeObjectExtension::data_clear);
}

void DeclarativeObjectExtension::dataAppend(QObject *object)
{
  m_children.append(object);
}

int DeclarativeObjectExtension::dataCount() const
{
  return m_children.count();
}

QObject* DeclarativeObjectExtension::dataAt(int index) const
{
  return m_children.at(index);
}

void DeclarativeObjectExtension::dataClear()
{
  m_children.clear();
}

void DeclarativeObjectExtension::data_append(QDeclarativeListProperty<QObject> *property, QObject *object)
{
  if (!object)
    return;

  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    that->dataAppend(object);
  else
    qWarning("cast went wrong in data_append");
}

int DeclarativeObjectExtension::data_count(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    return that->dataCount();
  else {
    qWarning("cast went wrong in data_count");
    return 0;
  }
}

QObject* DeclarativeObjectExtension::data_at(QDeclarativeListProperty<QObject> *property, int index)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    return that->dataAt(index);
  else {
    qWarning("cast went wrong in data_at");
    return 0;
  }
}

void DeclarativeObjectExtension::data_clear(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    that->dataClear();
  else
    qWarning("cast went wrong in data_clear");
}
