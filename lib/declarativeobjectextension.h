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

#ifndef DECLARATIVEOBJECTEXTENSION_H
#define DECLARATIVEOBJECTEXTENSION_H

#include <QDeclarativeListProperty>
#include <QObject>

class DeclarativeObjectExtension : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeObjectExtension(QObject *parent = 0);
    ~DeclarativeObjectExtension();

    QObject *extendedObject() const { return parent(); }

  protected:
    QObjectList m_children;

    virtual void dataAppend(QObject *object);
    virtual int dataCount() const;
    virtual QObject *dataAt(int index) const;
    virtual void dataClear();

    QDeclarativeListProperty<QObject> data();

  private:
    static void data_append(QDeclarativeListProperty<QObject> *, QObject *);
    static int data_count(QDeclarativeListProperty<QObject> *);
    static QObject *data_at(QDeclarativeListProperty<QObject> *, int);
    static void data_clear(QDeclarativeListProperty<QObject> *);
};

#endif // DECLARATIVEOBJECTEXTENSION_H
