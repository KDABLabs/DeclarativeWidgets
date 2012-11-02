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

#include "abstractdeclarativeobject_p.h"

#include <QMetaMethod>

AbstractDeclarativeObject::AbstractDeclarativeObject(QObject *parent)
  : QObject(parent)
{
}

AbstractDeclarativeObject::~AbstractDeclarativeObject()
{
}

QDeclarativeListProperty<QObject> AbstractDeclarativeObject::data()
{
  return QDeclarativeListProperty<QObject>(this, 0, AbstractDeclarativeObject::data_append,
                                                    AbstractDeclarativeObject::data_count,
                                                    AbstractDeclarativeObject::data_at,
                                                    AbstractDeclarativeObject::data_clear);
}

void AbstractDeclarativeObject::dataAppend(QObject *)
{
}

int AbstractDeclarativeObject::dataCount() const
{
  return 0;
}

QObject* AbstractDeclarativeObject::dataAt(int) const
{
  return 0;
}

void AbstractDeclarativeObject::dataClear()
{
}

void AbstractDeclarativeObject::connectAllSignals(QObject *sender, QObject *receiver, const QSet<QByteArray> &blacklist) const
{
  for (int i = 0; i < sender->metaObject()->methodCount(); ++i) {
    const QMetaMethod method = sender->metaObject()->method(i);
    if (method.methodType() == QMetaMethod::Signal) {
      if (blacklist.contains(method.signature()))
        continue;

      const QByteArray signature = "2" + QByteArray(method.signature());
      QObject::connect(sender, signature.data(), receiver, signature.data());
    }
  }
}

void AbstractDeclarativeObject::data_append(QDeclarativeListProperty<QObject> *property, QObject *object)
{
  if (!object)
    return;

  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    that->dataAppend(object);
  else
    qWarning("cast went wrong in data_append");
}

int AbstractDeclarativeObject::data_count(QDeclarativeListProperty<QObject> *property)
{
  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    return that->dataCount();
  else {
    qWarning("cast went wrong in data_count");
    return 0;
  }
}

QObject* AbstractDeclarativeObject::data_at(QDeclarativeListProperty<QObject> *property, int index)
{
  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    return that->dataAt(index);
  else {
    qWarning("cast went wrong in data_at");
    return 0;
  }
}

void AbstractDeclarativeObject::data_clear(QDeclarativeListProperty<QObject> *property)
{
  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    that->dataClear();
  else
    qWarning("cast went wrong in data_clear");
}

