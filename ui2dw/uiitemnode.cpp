/*
  Copyright (C) 2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "uiitemnode.h"

#include "parser.h"
#include "uilayoutnode.h"
#include "uinodevisitor.h"
#include "uispacernode.h"
#include "uiwidgetnode.h"

#include <QDebug>
#include <QXmlStreamAttributes>
#include <QXmlStreamReader>

UiItemNode::UiItemNode()
  : UiNode()
  , m_row(-1)
  , m_column(-1)
  , m_rowSpan(-1)
  , m_colSpan(-1)
{
}

UiNode *UiItemNode::parse(Parser *parser)
{
  UiItemNode *target = new UiItemNode;

  const QXmlStreamAttributes attributes = parser->reader()->attributes();
  if (attributes.hasAttribute(QLatin1String("row"))) {
    bool ok = false;
    const int value = attributes.value(QLatin1String("row")).toString().toInt(&ok);
    if (ok) {
      target->m_row = value;
    }
  }
  if (attributes.hasAttribute(QLatin1String("column"))) {
    bool ok = false;
    const int value = attributes.value(QLatin1String("column")).toString().toInt(&ok);
    if (ok) {
      target->m_column = value;
    }
  }

  if (attributes.hasAttribute(QLatin1String("rowspan"))) {
    bool ok = false;
    const int value = attributes.value(QLatin1String("rowspan")).toString().toInt(&ok);
    if (ok) {
      target->m_rowSpan = value;
    }
  }

  if (attributes.hasAttribute(QLatin1String("colspan"))) {
    bool ok = false;
    const int value = attributes.value(QLatin1String("colspan")).toString().toInt(&ok);
    if (ok) {
      target->m_colSpan = value;
    }
  }

  while (!parser->reader()->atEnd()) {
    if (!parser->reader()->readNextStartElement()) {
      if (parser->reader()->isEndElement() && parser->reader()->name().compare(QLatin1String("item"), Qt::CaseInsensitive) == 0) {
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
    } else if (parser->reader()->name().compare(QLatin1String("spacer"), Qt::CaseInsensitive) == 0) {
      UiNode *childNode = UiSpacerNode::parse(parser);
      if (childNode != 0) {
        target->appendChild(childNode);
      }
    } else {
      qDebug() << "Skipping unsupported" << parser->reader()->name().toString()
               << "sub element of item element, line"
               << parser->reader()->lineNumber();
      parser->reader()->skipCurrentElement();
    }
  }
  return target;
}

void UiItemNode::accept(UiNodeVisitor *visitor)
{
  visitor->visit(this);
}

int UiItemNode::row() const
{
  return m_row;
}

void UiItemNode::setRow(int row)
{
  m_row = row;
}

int UiItemNode::column() const
{
  return m_column;
}

void UiItemNode::setColumn(int column)
{
  m_column = column;
}

int UiItemNode::rowSpan() const
{
  return m_rowSpan;
}

void UiItemNode::setRowSpan(int rowSpan)
{
  m_rowSpan = rowSpan;
}

int UiItemNode::colSpan() const
{
  return m_colSpan;
}

void UiItemNode::setColSpan(int colSpan)
{
  m_colSpan = colSpan;
}
