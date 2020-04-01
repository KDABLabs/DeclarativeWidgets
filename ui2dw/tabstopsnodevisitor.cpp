/*
  tabstopsnodevisitor.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2014-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "tabstopsnodevisitor.h"

#include "uitabstopsnode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

TabStopsNodeVisitor::TabStopsNodeVisitor(const SharedVisitationContext &sharedContext)
  : UiNodeVisitor(sharedContext)
  , m_widgetNode(0)
{
}

void TabStopsNodeVisitor::visit(UiTabStopsNode *tabStopsNode)
{
  QStringList ids = tabStopsNode->tabStops();
  for (int i = 0; i < ids.count(); ++i) {
    ids[i] = m_sharedContext->idForObjectName(ids[i]);
  }
  tabStopsNode->setTabStops(ids);

  m_tabStopsNodes << tabStopsNode;
}

void TabStopsNodeVisitor::visit(UiTopNode *topNode)
{
  UiNodeVisitor::visit(topNode);

  if (m_widgetNode != 0) {
    int i = 0;
    while (i < topNode->childCount()) {
      UiNode *child = topNode->childAt(i);
      if (m_tabStopsNodes.contains(child)) {
        topNode->takeChildAt(i);
        m_widgetNode->appendChild(child);
      } else {
        ++i;
      }
    }
  }
}

void TabStopsNodeVisitor::visit(UiWidgetNode *widgetNode)
{
  if (m_widgetNode == 0) {
    m_widgetNode = widgetNode;
  }

  UiNodeVisitor::visit(widgetNode);
}
