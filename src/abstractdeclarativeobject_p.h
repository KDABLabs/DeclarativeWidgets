/*
  abstractdeclarativeobject_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef ABSTRACTDECLARATIVEOBJECT_P_H
#define ABSTRACTDECLARATIVEOBJECT_P_H

#include <QtGlobal>

#include <QObject>
#include <QQmlListProperty>
#include <QSet>

class AbstractDeclarativeObject : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false CONSTANT)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit AbstractDeclarativeObject(QObject *parent = 0);
    ~AbstractDeclarativeObject();

    virtual QObject* object() const = 0;

  protected:
    virtual void dataAppend(QObject *);
    virtual int dataCount() const;
    virtual QObject *dataAt(int) const;
    virtual void dataClear();

    void connectAllSignals(const QObject *sender, const QObject *receiver, const QSet<QByteArray> &blacklist = QSet<QByteArray>()) const;

  private:
    QQmlListProperty<QObject> data();

    static void data_append(QQmlListProperty<QObject> *, QObject *);
    static int data_count(QQmlListProperty<QObject> *);
    static QObject *data_at(QQmlListProperty<QObject> *, int);
    static void data_clear(QQmlListProperty<QObject> *);
};

#endif
