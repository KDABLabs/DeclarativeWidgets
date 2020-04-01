/*
  uinodevisitor.cpp

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

#include "uinodevisitor.h"

#include "uiactionnode.h"
#include "uiaddactionnode.h"
#include "uiconnectionnode.h"
#include "uilayoutitemnode.h"
#include "uilayoutnode.h"
#include "uipropertynode.h"
#include "uispacernode.h"
#include "uitabstopsnode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

#include <QDebug>

static QString cleanVersion(const QString &version)
{
  return version.split('.').join("_");
}

static QString cleanModule(const QString &module)
{
  QString result;
  Q_FOREACH (const QString &part, module.split('.')) {
    result.append(part[0].toUpper()).append(part.mid(1));
  }

  return result;
}

VisitationContext::VisitationContext()
{
}

QString VisitationContext::registerImport(const QString &module, const QString &version)
{
  VersionMap &versionHash = m_imports[module];
  QString &alias = versionHash[version];
  if (alias.isEmpty()) {
    const QString modulePart = cleanModule(module);
    const QString versionPart = cleanVersion(version);

    alias = modulePart + versionPart;

    int count = 1;
    while (m_aliases.contains(alias)) {
      alias = modulePart + versionPart + QString("_%1").arg(++count);
    }

    m_aliases.insert(alias);
  }

  return alias;
}

QStringList VisitationContext::generateImportLines() const
{
  static QString linePattern = QLatin1String("import %1 %2 as %3");

  QStringList result;

  ModuleMap::const_iterator moduleIt = m_imports.constBegin();
  ModuleMap::const_iterator moduleEndIt = m_imports.constEnd();
  for (; moduleIt != moduleEndIt; ++moduleIt) {
    const VersionMap &versions = moduleIt.value();

    VersionMap::const_iterator versionIt = versions.constBegin();
    VersionMap::const_iterator versionEndIt = versions.constEnd();
    for (; versionIt != versionEndIt; ++versionIt) {
      result << linePattern.arg(moduleIt.key(), versionIt.key(), versionIt.value());
    }
  }

  return result;
}

void VisitationContext::insertIdForObjectName(const QString &objectName, const QString &id)
{
  m_idsByObjectName.insert(objectName, id);
}

QString VisitationContext::idForObjectName(const QString &objectName) const
{
  return m_idsByObjectName.value(objectName);
}


UiNodeVisitor::UiNodeVisitor(const SharedVisitationContext &sharedContext)
  : m_sharedContext(sharedContext)
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

void UiNodeVisitor::visit(UiConnectionNode *connectionNode)
{
  visit(static_cast<UiNode*>(connectionNode));
}

void UiNodeVisitor::visit(UiLayoutItemNode *itemNode)
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

void UiNodeVisitor::visit(UiTabStopsNode *tabStopsNode)
{
  visit(static_cast<UiNode*>(tabStopsNode));
}

void UiNodeVisitor::visit(UiTopNode *topNode)
{
  visit(static_cast<UiNode*>(topNode));
}

void UiNodeVisitor::visit(UiWidgetNode *widgetNode)
{
  visit(static_cast<UiObjectNode*>(widgetNode));
}
