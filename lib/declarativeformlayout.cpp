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

#include "declarativeformlayout_p.h"

class DeclarativeFormLayoutAttached::Private
{
  public:
    QString label;
};

DeclarativeFormLayoutAttached::DeclarativeFormLayoutAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

DeclarativeFormLayoutAttached::~DeclarativeFormLayoutAttached()
{
  delete d;
}

void DeclarativeFormLayoutAttached::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;
  emit labelChanged(label);
}

QString DeclarativeFormLayoutAttached::label() const
{
  return d->label;
}

// DeclarativeFormLayout
DeclarativeFormLayout::DeclarativeFormLayout(QObject *parent) : DeclarativeLayoutProxy<QFormLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeFormLayoutAttached *DeclarativeFormLayout::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeFormLayoutAttached(parent);
}

void DeclarativeFormLayout::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(declarativeObject, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    if (!properties->label().isEmpty()) {
      m_proxiedObject->addRow(properties->label(), widget);
      m_children.append(declarativeObject);
      return;
    }
  }

  m_proxiedObject->addRow(widget);
  m_children.append(declarativeObject);
}

void DeclarativeFormLayout::addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(declarativeObject, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    if (!properties->label().isEmpty()) {
      m_proxiedObject->addRow(properties->label(), layout);
      m_children.append(declarativeObject);
      return;
    }
  }
  m_proxiedObject->addRow(layout);
  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeFormLayout, QFormLayout)
