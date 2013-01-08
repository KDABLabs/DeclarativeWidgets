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

#include "declarativevboxlayout_p.h"

#include <QDeclarativeInfo>
#include <QWidget>

DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent)
  : QVBoxLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeBoxLayoutAttached *DeclarativeVBoxLayout::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeBoxLayoutAttached(widget, parent);

  QLayout *layout = qobject_cast<QLayout*>(parent);
  if (layout)
    return new DeclarativeBoxLayoutAttached(layout, parent);

  qmlInfo(parent) << "Can only attach VBoxLayout to widgets and layouts";
  return 0;
}

DeclarativeVBoxLayoutExtension::DeclarativeVBoxLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(parent)
{
}

void DeclarativeVBoxLayoutExtension::addWidget(QWidget *widget)
{
  QVBoxLayout *vboxLayout = qobject_cast<QVBoxLayout*>(extendedLayout());
  Q_ASSERT(vboxLayout);

  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeVBoxLayout>(widget, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(vboxLayout);
  }

  vboxLayout->addWidget(widget, stretch, alignment);
}

void DeclarativeVBoxLayoutExtension::addLayout(QLayout *layout)
{
  QVBoxLayout *vboxLayout = qobject_cast<QVBoxLayout*>(extendedLayout());
  Q_ASSERT(vboxLayout);

  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeVBoxLayout>(layout, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(vboxLayout);
  }

  vboxLayout->addLayout(layout, stretch);
  vboxLayout->setAlignment(layout, alignment);
}
