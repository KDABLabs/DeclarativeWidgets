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

#include "declarativeformlayout_p.h"

#include "layoutcontainerinterface_p.h"

#include <QDeclarativeInfo>
#include <QWidget>

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
DeclarativeFormLayout::DeclarativeFormLayout(QObject *parent) : QFormLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeFormLayoutAttached *DeclarativeFormLayout::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeFormLayoutAttached(parent);

  QLayout *layout = qobject_cast<QLayout*>(parent);
  if (layout)
    return new DeclarativeFormLayoutAttached(parent);

  qmlInfo(parent) << "Can only attach FormLayout to widgets and layouts";
  return 0;
}

class FormLayoutContainer : public LayoutContainerInterface
{
  public:
    explicit FormLayoutContainer(QFormLayout *layout)
      : m_layout(layout)
    {
      Q_ASSERT(m_layout);
    }

    void addLayout(QLayout *layout);
    void addWidget(QWidget *widget);

  private:
    QFormLayout *m_layout;
};

DeclarativeFormLayoutExtension::DeclarativeFormLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(new FormLayoutContainer(qobject_cast<QFormLayout*>(parent)), parent)
{
}

void FormLayoutContainer::addWidget(QWidget *widget)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(widget, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    if (!properties->label().isEmpty()) {
      m_layout->addRow(properties->label(), widget);
      return;
    }
  }

  m_layout->addRow(widget);
}

void FormLayoutContainer::addLayout(QLayout *layout)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(layout, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    if (!properties->label().isEmpty()) {
      m_layout->addRow(properties->label(), layout);
      return;
    }
  }
  m_layout->addRow(layout);
}
