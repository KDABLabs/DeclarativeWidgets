/*
  uinode.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "uinode.h"

#include "uinodevisitor.h"

UiNode::UiNode()
{
}

UiNode::~UiNode()
{
  qDeleteAll(m_children);
}

void UiNode::acceptChildren(UiNodeVisitor *visitor)
{
  Q_FOREACH (UiNode *child, m_children) {
    child->accept(visitor);
  }
}

void UiNode::appendChild(UiNode *node)
{
  m_children.append(node);
}

void UiNode::prependChild(UiNode *node)
{
  m_children.prepend(node);
}

UiNode *UiNode::childAt(int index)
{
  return m_children.at(index);
}

UiNode *UiNode::takeChildAt(int index)
{
  return m_children.takeAt(index);
}

int UiNode::childCount() const
{
  return m_children.count();
}

QString UiNode::name() const
{
  return m_name;
}

void UiNode::setName(const QString &name)
{
  m_name = name;
}
