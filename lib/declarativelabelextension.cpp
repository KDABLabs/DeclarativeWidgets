/*
  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativelabelextension_p.h"

#include <QWidget>

DeclarativeLabelExtension::DeclarativeLabelExtension(QObject *parent)
  : DeclarativeWidgetExtension(parent)
  , m_buddy(0)
{
}

void DeclarativeLabelExtension::setBuddy(QWidget *buddy)
{
  if (buddy == m_buddy) {
    return;
  }

  if (m_buddy) {
    disconnect(m_buddy, SIGNAL(destroyed()), this, SLOT(buddyDestroyed()));
  }

  m_buddy = buddy;

  if (m_buddy) {
    connect(m_buddy, SIGNAL(destroyed()), this, SLOT(buddyDestroyed()));
  }

  emit buddyChanged();
}

QWidget *DeclarativeLabelExtension::buddy() const
{
  return m_buddy;
}

void DeclarativeLabelExtension::buddyDestroyed()
{
  if (m_buddy != 0) {
    m_buddy = 0;
    emit buddyChanged();
  }
}
