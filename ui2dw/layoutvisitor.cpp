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

#include "layoutvisitor.h"

#include "uilayoutnode.h"
#include "uipropertynode.h"

LayoutVisitor::LayoutVisitor(const SharedVisitationContext &sharedContext)
  : UiNodeVisitor(sharedContext)
{
}

void LayoutVisitor::visit(UiLayoutNode *layoutNode)
{
  QMargins contentsMargins;

  int i = 0;
  while (i < layoutNode->childCount()) {
    bool takeAndDeleteChild = false;

    UiPropertyNode *propertyNode = dynamic_cast<UiPropertyNode*>(layoutNode->childAt(i));
    if (propertyNode) {
      takeAndDeleteChild = true;

      if (propertyNode->name() == QLatin1String("leftMargin")) {
        contentsMargins.setLeft(propertyNode->value().toInt());
      } else if (propertyNode->name() == QLatin1String("topMargin")) {
        contentsMargins.setTop(propertyNode->value().toInt());
      } else if (propertyNode->name() == QLatin1String("rightMargin")) {
        contentsMargins.setRight(propertyNode->value().toInt());
      } else if (propertyNode->name() == QLatin1String("bottomMargin")) {
        contentsMargins.setBottom(propertyNode->value().toInt());
      } else if (propertyNode->name() == QLatin1String("margin")) {
        contentsMargins.setLeft(propertyNode->value().toInt());
        contentsMargins.setTop(propertyNode->value().toInt());
        contentsMargins.setRight(propertyNode->value().toInt());
        contentsMargins.setBottom(propertyNode->value().toInt());
      } else {
        takeAndDeleteChild = false;
      }
    }

    if (takeAndDeleteChild) {
      delete layoutNode->takeChildAt(i);
    } else {
      ++i;
    }
  }

  if (!contentsMargins.isNull()) {
    UiPropertyNode *marginsNode = new UiPropertyNode;
    marginsNode->setName(QLatin1String("contentsMargins"));
    marginsNode->setValue(QVariant::fromValue(contentsMargins));
    layoutNode->prependChild(marginsNode);
  }
  layoutNode->acceptChildren(this);
}
