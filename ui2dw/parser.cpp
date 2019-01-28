/*
  parser.cpp

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

#include "parser.h"

#include "uiconnectionnode.h"
#include "uitabstopsnode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

#include <QDebug>
#include <QIODevice>
#include <QXmlStreamReader>

static QSet<QString> ignoredElementNames()
{
  QSet<QString> result;

  result << QLatin1String("connections");
  result << QLatin1String("ui");

  return result;
}

static QSet<QString> skippedElementNames()
{
  QSet<QString> result;

  result << QLatin1String("resources");

  return result;
}

Parser::Parser(QIODevice *inputDevice)
  : m_reader(new QXmlStreamReader(inputDevice))
  , m_ignoredElementNames(ignoredElementNames())
  , m_skippedElementNames(skippedElementNames())
{
}

Parser::~Parser()
{
}

QSharedPointer<UiTopNode> Parser::parse()
{
  QSharedPointer<UiTopNode> topNode(new UiTopNode);

  while (!m_reader->atEnd()) {
    m_reader->readNext();
    if (!m_reader->isStartElement()) {
      continue;
    }

    if (m_reader->name().compare(QLatin1String("widget"), Qt::CaseInsensitive) == 0) {
      UiNode *widgetNode = UiWidgetNode::parse(this);
      if (widgetNode != 0) {
        topNode->appendChild(widgetNode);
      }
    } else if (m_reader->name().compare(QLatin1String("class"), Qt::CaseInsensitive) == 0) {
      topNode->setClassName(m_reader->readElementText().split(QLatin1String("::")));
    } else if (m_reader->name().compare(QLatin1String("connection"), Qt::CaseInsensitive) == 0) {
      UiNode *connectionNode = UiConnectionNode::parse(this);
      if (connectionNode != 0) {
        topNode->appendChild(connectionNode);
      }
    } else if (m_reader->name().compare(QLatin1String("tabstops"), Qt::CaseInsensitive) == 0) {
      UiNode *tabStopsNode = UiTabStopsNode::parse(this);
      if (tabStopsNode != 0) {
        topNode->appendChild(tabStopsNode);
      }
    } else if (m_ignoredElementNames.contains(m_reader->name().toString())) {
      continue;
    } else if (m_skippedElementNames.contains(m_reader->name().toString())) {
      m_reader->skipCurrentElement();
    } else {
      qWarning() << "Skipping unsupported element" << m_reader->name();
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

bool Parser::readUntilElement(const QString &parent, const QString &element)
{
  while (!m_reader->atEnd()) {
    m_reader->readNext();
    if (m_reader->isEndElement() && m_reader->name().compare(parent) == 0) {
      return false;
    }

    if (m_reader->isStartElement() && m_reader->name().compare(element) == 0) {
      return true;
    }
  }

  return false;
}
