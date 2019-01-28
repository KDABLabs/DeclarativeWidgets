/*
  itemvisitor.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "itemvisitor.h"

#include "uilayoutitemnode.h"
#include "uipropertynode.h"
#include "uiwidgetnode.h"

#include <QDebug>

class LabelTextVisitor : public UiNodeVisitor
{
  public:
    explicit LabelTextVisitor(const SharedVisitationContext &sharedContext)
      : UiNodeVisitor(sharedContext)
    {
    }

    static QString getText(UiNode *node, const SharedVisitationContext &sharedContext);

    void visit(UiPropertyNode *propertyNode);
    void visit(UiWidgetNode *widgetNode);

  private:
    QString m_labelText;
};

QString LabelTextVisitor::getText(UiNode *node, const SharedVisitationContext &sharedContext)
{
  LabelTextVisitor visitor(sharedContext);

  node->accept(&visitor);

  return visitor.m_labelText;
}

void LabelTextVisitor::visit(UiPropertyNode *propertyNode)
{
  if (propertyNode->name() == QLatin1String("text")) {
    const QString value = propertyNode->value().toString();
    if (m_labelText.isEmpty()) {
      m_labelText = value;
    } else {
      qWarning() << Q_FUNC_INFO << "Found text properyt with value" << value
                 << "but labelText is already set to" << m_labelText;
    }
  }
}

void LabelTextVisitor::visit(UiWidgetNode *widgetNode)
{
  const QStringList className = widgetNode->className();
  if (!className.isEmpty() && className.last() == QLatin1String("QLabel")) {
    widgetNode->acceptChildren(this);
  } else {
    qWarning() << Q_FUNC_INFO << "Widget node is not a QLabel but of class" << className;
  }
}


ItemVisitor::ItemVisitor(const SharedVisitationContext &sharedContext)
  : UiNodeVisitor(sharedContext)
{
}

void ItemVisitor::visit(UiLayoutItemNode *itemNode)
{
  if (itemNode->name() == QLatin1String("QGridLayout")) {
    visitGridLayoutItem(itemNode);
  } else if (itemNode->name() == QLatin1String("QFormLayout")) {
    visitFormLayoutItem(itemNode);
  }

  itemNode->acceptChildren(this);
}

void ItemVisitor::visitGridLayoutItem(UiLayoutItemNode *itemNode)
{
  const int row = itemNode->row();
  const int column = itemNode->column();

  if (row < 0 || column < 0) {
    qCritical() << Q_FUNC_INFO << "GridLayout item missing either row or column";
    return;
  }

  if (itemNode->childCount() != 1) {
    qCritical() << Q_FUNC_INFO << "GridLayout item with unexpected child count=" << itemNode->childCount();
    return;
  }

  UiNode *childNode = itemNode->childAt(0);

  UiPropertyNode *property = 0;
  if (itemNode->colSpan() > 1) {
    property = new UiPropertyNode;
    property->setName(QLatin1String("GridLayout.columnSpan"));
    property->setValue(itemNode->colSpan());
    childNode->prependChild(property);
  }

  if (itemNode->rowSpan() > 1) {
    property = new UiPropertyNode;
    property->setName(QLatin1String("GridLayout.rowSpan"));
    property->setValue(itemNode->rowSpan());
    childNode->prependChild(property);
  }

  property = new UiPropertyNode;
  property->setName(QLatin1String("GridLayout.column"));
  property->setValue(column);
  childNode->prependChild(property);

  property = new UiPropertyNode;
  property->setName(QLatin1String("GridLayout.row"));
  property->setValue(row);
  childNode->prependChild(property);
}

void ItemVisitor::visitFormLayoutItem(UiLayoutItemNode *itemNode)
{
  const int row = itemNode->row();
  const int column = itemNode->column();

  if (row < 0 || column < 0) {
    qCritical() << Q_FUNC_INFO << "FormLayout item missing either row or column";
    return;
  }

  if (column > 1) {
    qCritical() << Q_FUNC_INFO << "FormLayout item has more than two columns";
    return;
  }

  if (itemNode->childCount() != 1) {
    qCritical() << Q_FUNC_INFO << "FormLayout item with unexpected child count=" << itemNode->childCount();
    return;
  }

  UiNode *childNode = itemNode->childAt(0);
  if (column == 0) {
    // TODO can we add support for non-QLabels in label role?
    m_labels.insert(row, LabelTextVisitor::getText(childNode, m_sharedContext));
    delete itemNode->takeChildAt(0);
  } else {
    UiPropertyNode *property = new UiPropertyNode;
    property->setName(QLatin1String("FormLayout.label"));
    property->setValue(m_labels.value(row));
    childNode->prependChild(property);
  }
}
