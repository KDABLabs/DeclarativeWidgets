/*
  connectionnodevisitor.cpp

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

#include "connectionnodevisitor.h"

#include "uiconnectionnode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

ConnectionNodeVisitor::ConnectionNodeVisitor(const SharedVisitationContext &sharedContext)
  : UiNodeVisitor(sharedContext)
  , m_widgetNode(0)
{
}

void ConnectionNodeVisitor::visit(UiConnectionNode *connectionNode)
{
  // Need QtQuick 1.0 for Connections in Qt4
  m_sharedContext->registerImport("QtQuick", "1.0");

  connectionNode->setSender(m_sharedContext->idForObjectName(connectionNode->sender()));
  connectionNode->setReceiver(m_sharedContext->idForObjectName(connectionNode->receiver()));

  QString signalHandler;
  int signalArgCount = 0;
  parseSignalSignature(connectionNode->signalSignature(), signalHandler, signalArgCount);
  connectionNode->setSignalHandler(signalHandler);

  QString slotName;
  QStringList argumentTypes;
  parseSlotSignature(connectionNode->slotSignature(), slotName, argumentTypes);
  connectionNode->setSlotName(slotName);

  // in case the connection works because the slot has default values
  // for arguments beyond the number of arguments provided by the signal
  while (argumentTypes.count() > signalArgCount) {
    argumentTypes.removeLast();
  }
  connectionNode->setArgumentTypes(argumentTypes);

  m_connectionNodes << connectionNode;
}

void ConnectionNodeVisitor::visit(UiTopNode *topNode)
{
  UiNodeVisitor::visit(topNode);

  if (m_widgetNode != 0) {
    int i = 0;
    while (i < topNode->childCount()) {
      UiNode *child = topNode->childAt(i);
      if (m_connectionNodes.contains(child)) {
        topNode->takeChildAt(i);
        m_widgetNode->appendChild(child);
      } else {
        ++i;
      }
    }
  }
}

void ConnectionNodeVisitor::visit(UiWidgetNode *widgetNode)
{
  if (m_widgetNode == 0) {
    m_widgetNode = widgetNode;
  }

  UiNodeVisitor::visit(widgetNode);
}

void ConnectionNodeVisitor::parseSignalSignature(const QString &signalSignature, QString &signalHandler, int &argCount)
{
  const int parenthesesOpenIndex = signalSignature.indexOf('(');

  signalHandler = QLatin1String("on") + signalSignature.left(parenthesesOpenIndex);
  signalHandler[2] = signalHandler[2].toUpper();

  argCount = 0;

  const int parenthesesCloseIndex = signalSignature.lastIndexOf(')');
  if (parenthesesCloseIndex == (parenthesesOpenIndex + 1)) {
    return;
  }

  argCount = signalSignature.mid(parenthesesOpenIndex + 1).split(',').count();
}

void ConnectionNodeVisitor::parseSlotSignature(const QString &slotSignature, QString &slotName, QStringList &argumentTypes)
{
  const int parenthesesOpenIndex = slotSignature.indexOf('(');

  slotName = slotSignature.left(parenthesesOpenIndex);

  const int parenthesesCloseIndex = slotSignature.lastIndexOf(')');
  if (parenthesesCloseIndex == (parenthesesOpenIndex + 1)) {
    return;
  }

  argumentTypes = slotSignature.mid(parenthesesOpenIndex + 1, (parenthesesCloseIndex - parenthesesOpenIndex - 1)).split(',');
}
