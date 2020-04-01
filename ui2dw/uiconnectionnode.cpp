/*
  uiconnectionnode.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2014-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "uiconnectionnode.h"

#include "uinodevisitor.h"
#include "parser.h"

#include <QXmlStreamReader>

static QString readStringElement(Parser *parser, const QLatin1String &element)
{
  if (!parser->readUntilElement(QLatin1String("connection"), element)) {
    parser->reader()->raiseError(QString::fromUtf8("connection element does not have a %1 element").arg(element));
    return QString();
  }

  const QString text = parser->reader()->readElementText();
  if (text.isEmpty()) {
    parser->reader()->raiseError(QString::fromUtf8("connection element does have an empty %1 element").arg(element));
    return QString();
  }

  return text;
}

UiConnectionNode::UiConnectionNode()
{
}

UiNode *UiConnectionNode::parse(Parser *parser)
{
  const QString sender = readStringElement(parser, QLatin1String("sender"));
  if (sender.isEmpty()) {
    return 0;
  }

  const QString signalSignature = readStringElement(parser, QLatin1String("signal"));
  if (signalSignature.isEmpty()) {
    return 0;
  }

  const QString receicer = readStringElement(parser, QLatin1String("receiver"));
  if (receicer.isEmpty()) {
    return 0;
  }

  const QString slotSignature = readStringElement(parser, QLatin1String("slot"));
  if (slotSignature.isEmpty()) {
    return 0;
  }

  while (!parser->reader()->atEnd()) {
    if (parser->reader()->isEndElement() && parser->reader()->name() == QLatin1String("connection")) {
      break;
    }
    parser->reader()->readNext();
  }

  UiConnectionNode *target = new UiConnectionNode;
  target->m_sender = sender;
  target->m_signalSignature = signalSignature;
  target->m_receiver = receicer;
  target->m_slotSignature = slotSignature;

  return target;
}

void UiConnectionNode::accept(UiNodeVisitor *visitor)
{
  visitor->visit(this);
}

void UiConnectionNode::setSender(const QString &id)
{
  m_sender = id;
}

QString UiConnectionNode::sender() const
{
  return m_sender;
}

void UiConnectionNode::setReceiver(const QString &id)

{
  m_receiver = id;
}

QString UiConnectionNode::receiver() const
{
  return m_receiver;
}

QString UiConnectionNode::signalSignature() const
{
  return m_signalSignature;
}

QString UiConnectionNode::slotSignature() const
{
  return m_slotSignature;
}

void UiConnectionNode::setSignalHandler(const QString &signalHandler)
{
  m_signalHandler = signalHandler;
}

QString UiConnectionNode::signalHandler() const
{
  return m_signalHandler;
}

void UiConnectionNode::setSlotName(const QString &slotName)
{
  m_slotName = slotName;
}

QString UiConnectionNode::slotName() const
{
  return m_slotName;
}

void UiConnectionNode::setArgumentTypes(const QStringList& argumentTypes)
{
  m_argumentTypes = argumentTypes;
}

QStringList UiConnectionNode::argumentTypes() const
{
  return m_argumentTypes;
}
