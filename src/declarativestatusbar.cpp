/*
  declarativestatusbar.cpp

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

#include "declarativestatusbar_p.h"

#include <QQmlInfo>

class DeclarativeStatusBarAttached::Private
{
  public:
    int stretch;
};

DeclarativeStatusBarAttached::DeclarativeStatusBarAttached(QObject *parent)
  : QObject(parent), d(new DeclarativeStatusBarAttached::Private)
{
  d->stretch = 0;
}

DeclarativeStatusBarAttached::~DeclarativeStatusBarAttached()
{
  delete d;
}

void DeclarativeStatusBarAttached::setStretch(int stretch)
{
  if (d->stretch == stretch)
    return;

  d->stretch = stretch;
  emit stretchChanged();
}

int DeclarativeStatusBarAttached::stretch() const
{
  return d->stretch;
}

DeclarativeStatusBar::DeclarativeStatusBar(QWidget *parent)
  : QStatusBar(parent)
{
}

DeclarativeStatusBarAttached *DeclarativeStatusBar::qmlAttachedProperties(QObject *object)
{
  return new DeclarativeStatusBarAttached(object);
}

StatusBarWidgetContainer::StatusBarWidgetContainer(QObject *parent)
  : DefaultWidgetContainer(qobject_cast<QStatusBar*>(parent))
{
  Q_ASSERT(m_widget);
}

void StatusBarWidgetContainer::addWidget(QWidget *widget)
{
  // TODO: error when layout is set

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeStatusBar>(widget, false);
  DeclarativeStatusBarAttached *attached = qobject_cast<DeclarativeStatusBarAttached*>(attachedProperties);

  int stretch = 0;
  if (attached) {
    stretch = attached->stretch();
  }

  extendedStatusBar()->addPermanentWidget(widget, stretch);
}

void StatusBarWidgetContainer::setLayout(QLayout *layout)
{
  Q_UNUSED(layout);
  qmlInfo(m_widget) << "Can not add Layout to StatusBar";
}

QStatusBar *StatusBarWidgetContainer::extendedStatusBar() const
{
  return static_cast<QStatusBar*>(m_widget);
}
