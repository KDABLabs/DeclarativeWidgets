/*
  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com

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
