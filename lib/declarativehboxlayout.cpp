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

DeclarativeHBoxLayout::DeclarativeHBoxLayout(QObject *parent)
  : DeclarativeLayoutProxy<QHBoxLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeBoxLayoutAttached *DeclarativeHBoxLayout::qmlAttachedProperties(QObject *parent)
{
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject) {
    QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
    if (widget)
      return new DeclarativeBoxLayoutAttached(widget, parent);

    QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
    if (layout)
      return new DeclarativeBoxLayoutAttached(layout, parent);
  }

  qmlInfo(parent) << "Can only attach HBoxLayout to widgets and layouts";
  return 0;
}

void DeclarativeHBoxLayout::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(declarativeObject, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addWidget(widget, stretch, alignment);
  m_children.append(declarativeObject);
}

void DeclarativeHBoxLayout::addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(declarativeObject, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addLayout(layout, stretch);
  m_proxiedObject->setAlignment(layout, alignment);
  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeHBoxLayout, QHBoxLayout)
