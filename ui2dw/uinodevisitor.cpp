/*
  Copyright (C) 2013-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "uinodevisitor.h"

#include "uiactionnode.h"
#include "uiaddactionnode.h"
#include "uiitemnode.h"
#include "uilayoutnode.h"
#include "uipropertynode.h"
#include "uispacernode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

#include <QDebug>

UiNodeVisitor::UiNodeVisitor()
{
}

UiNodeVisitor::~UiNodeVisitor()
{
}

void UiNodeVisitor::visit(UiActionNode *actionNode)
{
  visit(static_cast<UiObjectNode*>(actionNode));
}

void UiNodeVisitor::visit(UiAddActionNode *addActionNode)
{
  visit(static_cast<UiNode*>(addActionNode));
}

void UiNodeVisitor::visit(UiItemNode *itemNode)
{
  visit(static_cast<UiNode*>(itemNode));
}

void UiNodeVisitor::visit(UiNode *node)
{
  node->acceptChildren(this);
}

void UiNodeVisitor::visit(UiLayoutNode *layoutNode)
{
  visit(static_cast<UiObjectNode*>(layoutNode));
}

void UiNodeVisitor::visit(UiPropertyNode *propertyNode)
{
  visit(static_cast<UiNode*>(propertyNode));
}

void UiNodeVisitor::visit(UiObjectNode *objectNode)
{
  visit(static_cast<UiNode*>(objectNode));
}

void UiNodeVisitor::visit(UiSpacerNode *spacerNode)
{
  visit(static_cast<UiNode*>(spacerNode));
}

void UiNodeVisitor::visit(UiTopNode *topNode)
{
  visit(static_cast<UiNode*>(topNode));
}

void UiNodeVisitor::visit(UiWidgetNode *widgetNode)
{
  visit(static_cast<UiObjectNode*>(widgetNode));
}
