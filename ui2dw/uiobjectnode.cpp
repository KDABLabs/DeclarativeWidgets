/*
  uiobjectnode.cpp

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

#include "uiobjectnode.h"

#include "uiactionnode.h"
#include "uiaddactionnode.h"
#include "uilayoutitemnode.h"
#include "uilayoutnode.h"
#include "uinodevisitor.h"
#include "uipropertynode.h"
#include "uiwidgetnode.h"
#include "parser.h"

#include <QDebug>
#include <QXmlStreamAttributes>
#include <QXmlStreamReader>

UiObjectNode::UiObjectNode(const QLatin1String &elementName)
  : m_elementName(elementName)
{
}

void UiObjectNode::accept(UiNodeVisitor *visitor)
{
  visitor->visit(this);
}

QStringList UiObjectNode::className() const
{
  return m_className;
}

void UiObjectNode::setClassName(const QStringList &className)
{
  m_className = className;
}

QString UiObjectNode::id() const
{
  return m_id;
}

void UiObjectNode::setId(const QString &id)
{
  m_id = id;
}

UiObjectNode *UiObjectNode::parse(UiObjectNode *target, Parser *parser)
{
  const QString className = parser->reader()->attributes().value(QLatin1String("class")).toString();
  if (className.isEmpty()) {
    parser->reader()->raiseError(target->m_elementName + QLatin1String(" element is missing the class attribute"));
    delete target;
    return 0;
  }

  QString objectName;
  if (parser->reader()->attributes().hasAttribute(QLatin1String("name"))) {
    objectName = parser->reader()->attributes().value(QLatin1String("name")).toString();
    if (objectName.isEmpty()) {
      qWarning() << target->m_elementName << "element has an empty name attribute";
    } else {
      target->setName(objectName);
    }
  }

  target->setClassName(className.split(QLatin1String("::")));

  while (!parser->reader()->atEnd()) {
    if (!parser->reader()->readNextStartElement()) {
      if (parser->reader()->isEndElement() && parser->reader()->name().compare(target->m_elementName, Qt::CaseInsensitive) == 0) {
        break;
      } else {
        continue;
      }
    }

    if (parser->reader()->name().compare(QLatin1String("widget"), Qt::CaseInsensitive) == 0) {
      UiNode *childNode = UiWidgetNode::parse(parser);
      if (childNode != 0) {
        target->appendChild(childNode);
      }
    } else if (parser->reader()->name().compare(QLatin1String("layout"), Qt::CaseInsensitive) == 0) {
      UiNode *childNode = UiLayoutNode::parse(parser);
      if (childNode != 0) {
        target->appendChild(childNode);
      }
    } else if (parser->reader()->name().compare(QLatin1String("property"), Qt::CaseInsensitive) == 0) {
      UiNode *childNode = UiPropertyNode::parse(parser);
      if (childNode != 0) {
        target->appendChild(childNode);
      }
    } else if (parser->reader()->name().compare(QLatin1String("action"), Qt::CaseInsensitive) == 0) {
      UiNode *childNode = UiActionNode::parse(parser);
      if (childNode != 0) {
        target->appendChild(childNode);
      }
    } else if (parser->reader()->name().compare(QLatin1String("addaction"), Qt::CaseInsensitive) == 0) {
      const QString actionName = parser->reader()->attributes().value(QLatin1String("name")).toString();
      if (actionName.isEmpty()) {
        parser->reader()->raiseError(QLatin1String("addaction element is missing the name attribute"));
        parser->reader()->skipCurrentElement();
        continue;
      }

      UiNode *childNode = new UiAddActionNode;
      childNode->setName(actionName);
      target->appendChild(childNode);
    } else if (parser->reader()->name().compare(QLatin1String("item"), Qt::CaseInsensitive) == 0) {
      UiNode *childNode = UiLayoutItemNode::parse(parser);
      if (childNode != 0) {
        childNode->setName(className);
        target->appendChild(childNode);
      }
    } else {
      qDebug() << "Skipping unsupported" << parser->reader()->name().toString()
               << "sub element of" << target->m_elementName << "element" << objectName << ", line"
               << parser->reader()->lineNumber();
      parser->reader()->skipCurrentElement();
    }
  }

  return target;
}
