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

#include "declarativebuttongroupextension_p.h"

#include <QAbstractButton>
#include <QButtonGroup>

DeclarativeButtonGroupExtension::DeclarativeButtonGroupExtension(QObject *parent)
  : DeclarativeObjectExtension(parent)
{
}

void DeclarativeButtonGroupExtension::setButtons(const QVariantList &buttons)
{
  if (m_buttons == buttons)
    return;

  // First remove the old buttons ...
  foreach (const QVariant &variant, m_buttons) {
    QObject *object = variant.value<QObject*>();
    if (object) {
      QAbstractButton *button = qobject_cast<QAbstractButton*>(object);
      if (button)
        buttonGroup()->removeButton(button);
    }
  }

  m_buttons = buttons;

  // ... then add the new ones
  foreach (const QVariant &variant, m_buttons) {
    QObject *object = variant.value<QObject*>();
    if (object) {
      QAbstractButton *button = qobject_cast<QAbstractButton*>(object);
      if (button)
        buttonGroup()->addButton(button);
    }
  }

  emit buttonsChanged();
}

QVariantList DeclarativeButtonGroupExtension::buttons() const
{
  return m_buttons;
}

QButtonGroup *DeclarativeButtonGroupExtension::buttonGroup() const
{
  QButtonGroup *buttonGroup = qobject_cast<QButtonGroup*>(extendedObject());
  Q_ASSERT(buttonGroup);

  return buttonGroup;
}
