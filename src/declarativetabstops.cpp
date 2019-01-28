/*
  declarativetabstops.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2014-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer <kevin.krammer@kdab.com>

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

#include "declarativetabstops_p.h"

#include <QQmlInfo>
#include <QWidget>

DeclarativeTabStops::DeclarativeTabStops(QObject *parent)
  : QObject(parent)
{
}

void DeclarativeTabStops::setTabStops(const QVariantList &tabStops)
{
  if (tabStops == m_tabStops)
    return;

  m_tabStops = tabStops;

  QList<QWidget*> widgets;
  widgets.reserve(m_tabStops.count());

  for (int i = 0; i < m_tabStops.count(); ++i) {
    QWidget *widget = qobject_cast<QWidget*>(m_tabStops[i].value<QObject*>());
    if (widget != 0) {
      widgets << widget;
    } else {
      qmlInfo(this) << "TabStop at " << i << " is not a widget";
    }
  }

  for (int i = 1; i < widgets.count(); ++i) {
    QWidget::setTabOrder(widgets[i - 1], widgets[i]);
  }

  emit tabStopsChanged();
}

QVariantList DeclarativeTabStops::tabStops() const
{
  return m_tabStops;
}
