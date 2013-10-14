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

#include "parser.h"

#include "uilayoutnode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

#include <QDebug>
#include <QIODevice>
#include <QXmlStreamReader>

Parser::Parser(QIODevice *inputDevice)
  : m_reader(new QXmlStreamReader(inputDevice))
{
}

Parser::~Parser()
{
}

QSharedPointer<UiTopNode> Parser::parse()
{
  QSharedPointer<UiTopNode> topNode(new UiTopNode);

  while (!m_reader->atEnd()) {
    if (!m_reader->readNextStartElement()) {
      break;
    }

    if (m_reader->name().compare(QLatin1String("widget"), Qt::CaseInsensitive) == 0) {
      UiNode *widgetNode = UiWidgetNode::parse(this);
      if (widgetNode != 0) {
        topNode->appendChild(widgetNode);
      }
    } else if (m_reader->name().compare(QLatin1String("class"), Qt::CaseInsensitive) == 0) {
      topNode->setClassName(m_reader->readElementText().split(QLatin1String("::")));
    }
  }

  return topNode;
}

QString Parser::errorString() const
{
  return m_reader->errorString();
}

QXmlStreamReader *Parser::reader() const
{
  return m_reader.data();
}
