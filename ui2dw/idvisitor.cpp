/*
  idvisitor.cpp

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

#include "idvisitor.h"

#include "uiobjectnode.h"
#include "uispacernode.h"

#include <QDebug>

IdVisitor::IdVisitor(const SharedVisitationContext &sharedContext)
  : UiNodeVisitor(sharedContext)
{
}

void IdVisitor::visit(UiObjectNode *objectNode)
{
  QString name = objectNode->name();
  if (!name.isEmpty()) {
    objectNode->setId(objectNameToUniqueId(name));
    objectNode->setName(name);
  }

  objectNode->acceptChildren(this);
}

void IdVisitor::visit(UiSpacerNode *spacerNode)
{
  QString name = spacerNode->name();
  if (!name.isEmpty()) {
    spacerNode->setId(objectNameToUniqueId(name));
    spacerNode->setName(name);
  }
}

QString IdVisitor::objectNameToUniqueId(QString &objectName)
{
  if (m_idsByObjectName.contains(objectName)) {
    qWarning() << Q_FUNC_INFO << "Object name" << objectName << "appears more than once. Generating new name";

    const QString nameTemplate = objectName + QLatin1String("_%1");
    int i = 2;
    do {
      objectName = nameTemplate.arg(i);
      ++i;
    } while (m_idsByObjectName.contains(objectName));
  }

  const QString id = objectNameStringToIdString(objectName);

  m_idsByObjectName.insert(objectName, id);
  m_sharedContext->insertIdForObjectName(objectName, id);

  return id;
}

QString IdVisitor::objectNameStringToIdString(const QString &objectName) const
{
  QString id = objectName;
  id[0] = objectName[0].toLower();

  return id;
}
