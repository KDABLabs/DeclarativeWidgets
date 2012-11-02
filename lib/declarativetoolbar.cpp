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

#include "declarativetoolbar_p.h"

#include "declarativeseparator_p.h"

DeclarativeToolBar::DeclarativeToolBar(QObject *parent)
  : DeclarativeWidgetProxy<QToolBar>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeToolBar::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  m_proxiedObject->addWidget(widget);

  m_children.append(declarativeObject);
}

void DeclarativeToolBar::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not set a QLayout to a QToolBar";
}

void DeclarativeToolBar::addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
{
  DeclarativeSeparator *separator = dynamic_cast<DeclarativeSeparator*>(declarativeObject);

  if (separator) {
    m_proxiedObject->addSeparator();
  } else {
    m_proxiedObject->addAction(action);
  }

  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeToolBar, QToolBar)
