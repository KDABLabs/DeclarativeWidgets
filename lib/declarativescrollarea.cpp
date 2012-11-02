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

#include "declarativescrollarea_p.h"

DeclarativeScrollArea::DeclarativeScrollArea(QObject *parent)
  : DeclarativeWidgetProxy<QScrollArea>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeScrollArea::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  if (m_proxiedObject->widget()) {
    qmlInfo(declarativeObject) << "Can not add multiple Widgets to ScrollArea";
  } else {
    m_proxiedObject->setWidget(widget);
  }

  m_children.append(declarativeObject);
}

void DeclarativeScrollArea::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not add Layout to ScrollArea";
}

CUSTOM_METAOBJECT(DeclarativeScrollArea, QScrollArea)
