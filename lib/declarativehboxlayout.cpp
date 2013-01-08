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

#include "declarativehboxlayout_p.h"

#include <QDeclarativeInfo>
#include <QWidget>

DeclarativeHBoxLayout::DeclarativeHBoxLayout(QObject *parent)
  : QHBoxLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeBoxLayoutAttached *DeclarativeHBoxLayout::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeBoxLayoutAttached(widget, parent);

  QLayout *layout = qobject_cast<QLayout*>(parent);
  if (layout)
    return new DeclarativeBoxLayoutAttached(layout, parent);

  qmlInfo(parent) << "Can only attach HBoxLayout to widgets and layouts";
  return 0;
}

DeclarativeHBoxLayoutExtension::DeclarativeHBoxLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(parent)
{
}

void DeclarativeHBoxLayoutExtension::addWidget(QWidget *widget)
{
  QHBoxLayout *hboxLayout = qobject_cast<QHBoxLayout*>(extendedLayout());
  Q_ASSERT(hboxLayout);

  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(widget, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(hboxLayout);
  }

  hboxLayout->addWidget(widget, stretch, alignment);
}

void DeclarativeHBoxLayoutExtension::addLayout(QLayout *layout)
{
  QHBoxLayout *hboxLayout = qobject_cast<QHBoxLayout*>(extendedLayout());
  Q_ASSERT(hboxLayout);

  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(layout, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(hboxLayout);
  }

  hboxLayout->addLayout(layout, stretch);
  hboxLayout->setAlignment(layout, alignment);
}
