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

#include "staticdialogmethodattached_p.h"

#include "abstractdeclarativeobject_p.h"

#include <QPointer>
#include <QWidget>

class StaticDialogMethodAttached::Private
{
  public:
    QPointer<QObject> dialogParent;
};

StaticDialogMethodAttached::StaticDialogMethodAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

StaticDialogMethodAttached::~StaticDialogMethodAttached()
{
  delete d;
}

void StaticDialogMethodAttached::setDialogParent(QObject *parent)
{
  if (parent == d->dialogParent)
    return;

  d->dialogParent = parent;
  emit dialogParentChanged(parent);
}

QObject *StaticDialogMethodAttached::dialogParent() const
{
  return d->dialogParent;
}

QWidget *StaticDialogMethodAttached::bestParentWindow() const
{
  QObject *parent = d->dialogParent;

  if (!parent)
    parent = this->parent();

  // if parent is a Declarative Object, search the proxied hierarchy
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject)
    parent = declarativeObject->object();

  while (parent) {
    QWidget *widget = qobject_cast<QWidget*>(parent);
    if (widget)
      return widget->topLevelWidget();

    parent = parent->parent();
  }

  return 0;
}
