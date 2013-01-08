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

#include "declarativestackedlayout_p.h"

#include <QDeclarativeInfo>
#include <QWidget>

DeclarativeStackedLayout::DeclarativeStackedLayout(QObject *parent)
  : QStackedLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeStackedLayoutExtension::DeclarativeStackedLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(parent)
{
}

int DeclarativeStackedLayoutExtension::count() const
{
  QStackedLayout *stackedLayout = qobject_cast<QStackedLayout*>(extendedLayout());
  Q_ASSERT(stackedLayout);

  return stackedLayout->count();
}

void DeclarativeStackedLayoutExtension::addWidget(QWidget *widget)
{
  extendedLayout()->addWidget(widget);
}

void DeclarativeStackedLayoutExtension::addLayout(QLayout*)
{
  qmlInfo(extendedLayout()) << "StackedLayout does not support child layouts";
}
