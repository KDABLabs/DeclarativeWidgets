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

#include "qmlwriter.h"

#include "uiaddactionnode.h"
#include "uilayoutnode.h"
#include "uipropertynode.h"
#include "uispacernode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

#include <QDebug>
#include <QIODevice>
#include <QRect>
#include <QTextCodec>
#include <QTextStream>

static void writeEnumValue(QTextStream &writer, const EnumValue &enumValue)
{
  QStringList nameParts = enumValue.nameParts;
  while (nameParts.count() > 2) {
    nameParts.pop_front();
  }

  writer << nameParts.join(QLatin1String("."));
}

static void writeSetValue(QTextStream &writer, const SetValue &setValue)
{
  int count = setValue.flags.count();

  Q_FOREACH (const EnumValue &enumValue, setValue.flags) {
    writeEnumValue(writer, enumValue);

    --count;
    if (count > 0) {
      writer << " | ";
    }
  }
}

QmlWriter::QmlWriter(QIODevice *outputDevice)
  : m_writer(new QTextStream(outputDevice))
  , m_currentIndent(0)
{
  m_writer->setCodec(QTextCodec::codecForName("UTF-8"));
}

QmlWriter::~QmlWriter()
{
}

void QmlWriter::write(const QSharedPointer<UiTopNode> &topNode)
{
  topNode->accept(this);
}

void QmlWriter::visit(UiAddActionNode *addActionNode)
{
  const QByteArray indent(m_currentIndent, ' ');
  const QByteArray offsetIndent(2, ' ');

  *m_writer << endl;
  *m_writer << indent << "ActionItem {" << endl;
  *m_writer << indent << offsetIndent << "action: " << addActionNode->name() << endl;
  *m_writer << indent << "}" << endl;
}

void QmlWriter::visit(UiPropertyNode *propertyNode)
{
  const QByteArray indent(m_currentIndent, ' ');

  *m_writer << indent << propertyNode->name() << ": ";

  switch (propertyNode->value().type()) {
  case QVariant::Bool:
    *m_writer << (propertyNode->value().toBool() ? "true" : "false");
    break;

  case QVariant::Double:
    *m_writer << propertyNode->value().toDouble();
    break;

  case QVariant::Int:
    *m_writer << propertyNode->value().toInt();
    break;

  case QVariant::Rect: {
    const QRect r = propertyNode->value().value<QRect>();
    *m_writer << "Qt.rect(" << r.x() << ", " << r.y() << ", " << r.width() << ", " << r.height() << ")";
    break;
  }

  case QVariant::Size: {
    const QSize s = propertyNode->value().value<QSize>();
    *m_writer << "Qt.size(" << s.width() << ", " << s.height() << ")";
    break;
  }

  case QVariant::UInt:
    *m_writer << propertyNode->value().toUInt();
    break;

  case QVariant::UserType:
    if (propertyNode->value().canConvert<EnumValue>()) {
      writeEnumValue(*m_writer, propertyNode->value().value<EnumValue>());
      break;
    }

    if (propertyNode->value().canConvert<SetValue>()) {
      writeSetValue(*m_writer, propertyNode->value().value<SetValue>());
      break;
    }

    // fall through

  default:
    *m_writer << "\"" << propertyNode->value().toString() << "\"";
    break;
  }

  *m_writer << endl;
}

void QmlWriter::visit(UiObjectNode *objectNode)
{
  const QByteArray indent(m_currentIndent, ' ');
  const QByteArray offsetIndent(2, ' ');

  *m_writer << endl;
  *m_writer << indent << objectNode->className().last() << " {" << endl;
  *m_writer << indent << offsetIndent << "id: " << objectNode->id() << endl;
  *m_writer << indent << offsetIndent << "objectName: \"" << objectNode->id() << "\"" << endl;

  m_currentIndent += 2;
  objectNode->acceptChildren(this);
  m_currentIndent -= 2;

  *m_writer << indent << "}" << endl;
}

void QmlWriter::visit(UiSpacerNode *spacerNode)
{
  const QByteArray indent(m_currentIndent, ' ');
  const QByteArray offsetIndent(2, ' ');

  *m_writer << endl;
  *m_writer << indent << "Spacer {" << endl;
  *m_writer << indent << offsetIndent << "id: " << spacerNode->id() << endl;
  *m_writer << indent << offsetIndent << "objectName: \"" << spacerNode->id() << "\"" << endl;

  // map the orientation property to spacer size policy enums
  // TODO should probably be in a specialized "property transform" visitor
  for (int i = 0; i < spacerNode->childCount(); ++i) {
    UiNode *child = spacerNode->childAt(i);
    if (child->name() == QLatin1String("orientation")) {
      UiPropertyNode *orientationProperty = dynamic_cast<UiPropertyNode*>(child);
      if (orientationProperty == 0) {
        qWarning() << Q_FUNC_INFO << "Spacer orientation child node is not a propery node";
        continue;
      }

      const QStringList nameParts = orientationProperty->value().value<EnumValue>().nameParts;
      if (nameParts.count() != 2 || nameParts[0] != QLatin1String("Qt")) {
        qWarning() << Q_FUNC_INFO << "Spacer orientation is neither Qt::Vertical nor Qt::Horizontal: "
                   << nameParts.join(QLatin1String("::"));
        continue;
      }

      if (nameParts[1] == QLatin1String("Horizontal")) {
        EnumValue policyEnum;
        UiPropertyNode *policyNode = 0;

        policyEnum.nameParts << QLatin1String("Spacer") << QLatin1String("Expanding");
        policyNode = new UiPropertyNode;
        policyNode->setName(QLatin1String("horizontalSizePolicy"));
        policyNode->setValue(QVariant::fromValue(policyEnum));;
        spacerNode->appendChild(policyNode);

        policyEnum.nameParts << QLatin1String("Spacer") << QLatin1String("Minimum");
        policyNode = new UiPropertyNode;
        policyNode->setName(QLatin1String("verticalSizePolicy"));
        policyNode->setValue(QVariant::fromValue(policyEnum));;
        spacerNode->appendChild(policyNode);

      } else if (nameParts[1] == QLatin1String("Vertical")) {
        EnumValue policyEnum;
        UiPropertyNode *policyNode = 0;

        policyEnum.nameParts << QLatin1String("Spacer") << QLatin1String("Minimum");
        policyNode = new UiPropertyNode;
        policyNode->setName(QLatin1String("horizontalSizePolicy"));
        policyNode->setValue(QVariant::fromValue(policyEnum));;
        spacerNode->appendChild(policyNode);

        policyEnum.nameParts << QLatin1String("Spacer") << QLatin1String("Expanding");
        policyNode = new UiPropertyNode;
        policyNode->setName(QLatin1String("verticalSizePolicy"));
        policyNode->setValue(QVariant::fromValue(policyEnum));;
        spacerNode->appendChild(policyNode);

      } else {
        qWarning() << Q_FUNC_INFO << "Spacer orientation is neither Qt::Vertical nor Qt::Horizontal: "
                   << nameParts.join(QLatin1String("::"));
        continue;
      }

      delete spacerNode->takeChildAt(i);
      break;
    }
  }

  m_currentIndent += 2;
  spacerNode->acceptChildren(this);
  m_currentIndent -= 2;

  *m_writer << indent << "}" << endl;
}

void QmlWriter::visit(UiTopNode *topNode)
{
  Q_UNUSED(topNode);

  *m_writer << "import QtWidgets 1.0" << endl;
  *m_writer << endl;

  topNode->acceptChildren(this);
}
