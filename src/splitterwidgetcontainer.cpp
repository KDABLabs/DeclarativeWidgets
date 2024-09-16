/*
  splitterwidgetcontainer.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2018 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Lova Widmark <znurree@gmail.com>

  Licensees holding valid commercial KDAB DeclarativeWidgets licenses may use this file in
  accordance with DeclarativeWidgets Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "splitterwidgetcontainer_p.h"

#include <QQmlInfo>
#include <QSplitter>

SplitterWidgetContainer::SplitterWidgetContainer(QObject *parent)
  : DefaultWidgetContainer(qobject_cast<QSplitter*>(parent))
{
  Q_ASSERT(m_widget);
}

void SplitterWidgetContainer::setLayout(QLayout *layout)
{
  Q_UNUSED(layout);
  qmlInfo(m_widget) << "Can not set a Layout to a Splitter";
}

void SplitterWidgetContainer::addWidget(QWidget *widget)
{
  extendedSplitter()->addWidget(widget);
}

QSplitter *SplitterWidgetContainer::extendedSplitter() const
{
  return static_cast<QSplitter*>(m_widget);
}
