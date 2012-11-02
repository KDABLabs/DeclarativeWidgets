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

#include "declarativemenubar_p.h"

#include "declarativeseparator_p.h"

DeclarativeMenuBar::DeclarativeMenuBar(QObject *parent)
  : DeclarativeWidgetProxy<QMenuBar>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeMenuBar::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  QMenu *menu = qobject_cast<QMenu*>(widget);
  if (!menu) {
    qmlInfo(declarativeObject) << "The QMenuBar can only contain QMenus";
    return;
  }

  m_proxiedObject->addMenu(menu);

  m_children.append(declarativeObject);
}

void DeclarativeMenuBar::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not set a QLayout to a QMenuBar";
}

void DeclarativeMenuBar::addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(action)

  DeclarativeSeparator *separator = dynamic_cast<DeclarativeSeparator*>(declarativeObject);

  if (separator) {
    m_proxiedObject->addSeparator();
  }

  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeMenuBar, QMenuBar)
