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

#include "idvisitor.h"

#include "uiobjectnode.h"
#include "uispacernode.h"

#include <QDebug>

IdVisitor::IdVisitor()
{
}

void IdVisitor::visit(UiObjectNode *objectNode)
{
  const QString id = objectNameToUniqueId(objectNode->name());

  objectNode->setId(id);

  objectNode->acceptChildren(this);
}

void IdVisitor::visit(UiSpacerNode *spacerNode)
{
  const QString id = objectNameToUniqueId(spacerNode->name());

  spacerNode->setId(id);
}

QString IdVisitor::objectNameToUniqueId(const QString &objectName)
{
  QString name = objectName;
  if (m_idsByObjectName.contains(name)) {
    qWarning() << Q_FUNC_INFO << "Object name" << name << "appears more than once. Generating new name";

    const QString nameTemplate = name + QLatin1String("_%1");
    int i = 2;
    do {
      name = nameTemplate.arg(i);
      ++i;
    } while (m_idsByObjectName.contains(name));
  }

  const QString id = objectNameStringToIdString(name);

  m_idsByObjectName.insert(name, id);

  return id;
}

QString IdVisitor::objectNameStringToIdString(const QString &objectName) const
{
  QString id = objectName;
  id[0] = objectName[0].toLower();

  return id;
}
