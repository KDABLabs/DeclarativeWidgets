/*
  qmlwriter.cpp

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

#include "qmlwriter.h"

#include "uiaddactionnode.h"
#include "uiconnectionnode.h"
#include "uilayoutnode.h"
#include "uipropertynode.h"
#include "uispacernode.h"
#include "uitabstopsnode.h"
#include "uitopnode.h"
#include "uiwidgetnode.h"

#include <QDebug>
#include <QIODevice>
#include <QRect>
#include <QTextCodec>
#include <QTextStream>

class PropertyWriter
{
  public:
    PropertyWriter() {}
    virtual ~PropertyWriter() {}

    void write(QTextStream &writer, const QByteArray &indent, const QString &name, const QVariant &value)
    {
      writeBeginProperty(writer, indent, name);
      writeValue(writer, indent, value);
      writeEndProperty(writer, indent);
    }

protected:
    virtual void writeBeginProperty(QTextStream &writer, const QByteArray &indent, const QString &name)
    {
      writer << indent << name << QLatin1String(": ");
    }

    virtual void writeEndProperty(QTextStream &writer,const QByteArray &indent)
    {
      Q_UNUSED(indent);
      writer << endl;
    }

    virtual void writeValue(QTextStream &writer, const QByteArray &indent, const QVariant &value)
    {
      Q_UNUSED(indent);

      switch (value.type()) {
      case QVariant::Bool:
        writer << (value.toBool() ? "true" : "false");
        break;

      case QVariant::Double:
        writer << value.toDouble();
        break;

      case QVariant::Int:
        writer << value.toInt();
        break;

      case QVariant::Rect: {
        const QRect r = value.value<QRect>();
        writer << "Qt.rect(" << r.x() << ", " << r.y() << ", " << r.width() << ", " << r.height() << ")";
        break;
      }

      case QVariant::Size: {
        const QSize s = value.value<QSize>();
        writer << "Qt.size(" << s.width() << ", " << s.height() << ")";
        break;
      }

      case QVariant::UInt:
        writer << value.toUInt();
        break;

      case QVariant::UserType:
        if (value.canConvert<EnumValue>()) {
          writeEnumValue(writer, value.value<EnumValue>());
          break;
        }

        if (value.canConvert<IdValue>()) {
          writer << value.value<IdValue>().id;
          break;
        }

        if (value.canConvert<PixmapValue>()) {
          writer << "Pixmap.fromFileName(\"" << value.value<PixmapValue>().fileName << "\")";
          break;
        }

        if (value.canConvert<SetValue>()) {
          writeSetValue(writer, value.value<SetValue>());
          break;
        }

        // fall through

      default: {
        QString text = value.toString();
        text.replace('"', QLatin1String("\\\""));
        writer << "\"" << text << "\"";
        break;
      }
      }
    }

    void writeEnumValue(QTextStream &writer, const EnumValue &enumValue)
    {
      writer << enumValue.nameParts.join(QLatin1String("."));
    }

    void writeSetValue(QTextStream &writer, const SetValue &setValue)
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
};

class GroupedPropertyWriter : public PropertyWriter
{
  public:
    GroupedPropertyWriter()
      : PropertyWriter()
      , m_offsetIndent(2, ' ')
    {
    }

  protected:
    const QByteArray m_offsetIndent;

  protected:
    void writeBeginProperty(QTextStream &writer, const QByteArray &indent, const QString &name)
    {
      writer << indent << name << " {" << endl;
    }

    void writeEndProperty(QTextStream &writer, const QByteArray &indent)
    {
      writer << indent << "}" << endl;
    }
};

class FontPropertyWriter : public GroupedPropertyWriter
{
  public:
    FontPropertyWriter()
      : GroupedPropertyWriter()
      , m_subValueWriter(new PropertyWriter)
      , m_orderedNames(QStringList() << "family" << "pointSize" << "bold" << "italic" << "underline" << "strikeout")
    {
    }

  protected:
    QScopedPointer<PropertyWriter> m_subValueWriter;
    const QStringList m_orderedNames;

  protected:
    void writeValue(QTextStream &writer, const QByteArray &indent, const QVariant &value)
    {
      Q_ASSERT(value.canConvert<FontValue>());

      const QByteArray subIndent = indent + m_offsetIndent;

      QVariantHash fontProperties = value.value<FontValue>().fontProperties;

      // first write properties that we want in a preferential order
      Q_FOREACH (const QString &name, m_orderedNames) {
        QVariantHash::iterator it = fontProperties.find(name);
        if (it != fontProperties.end()) {
          m_subValueWriter->write(writer, subIndent, it.key(), it.value());
          fontProperties.erase(it);
        }
      }

      // then write all the remaining ones
      QVariantHash::const_iterator it = fontProperties.constBegin();
      QVariantHash::const_iterator endIt = fontProperties.constEnd();
      for (; it != endIt; ++it) {
        m_subValueWriter->write(writer, subIndent, it.key(), it.value());
      }
    }
};

class MarginsPropertyWriter : public GroupedPropertyWriter
{
  public:
    MarginsPropertyWriter()
      : GroupedPropertyWriter()
      , m_subValueWriter(new PropertyWriter)
    {
    }

  protected:
    QScopedPointer<PropertyWriter> m_subValueWriter;

  protected:
    void writeValue(QTextStream &writer, const QByteArray &indent, const QVariant &value)
    {
      Q_ASSERT(value.canConvert<QMargins>());

      const QByteArray subIndent = indent + m_offsetIndent;

      const QMargins margins = value.value<QMargins>();

      m_subValueWriter->write(writer, subIndent, QLatin1String("left"), margins.left());
      m_subValueWriter->write(writer, subIndent, QLatin1String("top"), margins.top());
      m_subValueWriter->write(writer, subIndent, QLatin1String("right"), margins.right());
      m_subValueWriter->write(writer, subIndent, QLatin1String("bottom"), margins.bottom());
    }
};

QmlWriter::QmlWriter(QIODevice *outputDevice, const SharedVisitationContext &sharedContext)
  : UiNodeVisitor(sharedContext)
  , m_writer(new QTextStream(outputDevice))
  , m_currentIndent(0)
  , m_propertyWriter(new PropertyWriter)
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

void QmlWriter::visit(UiConnectionNode *connectionNode)
{
  const QByteArray indent(m_currentIndent, ' ');
  const QByteArray offsetIndent(2, ' ');

  *m_writer << endl;
  *m_writer << indent << m_sharedContext->registerImport("QtQuick", "1.0")
            << ".Connections {" << endl;

  *m_writer << indent << offsetIndent << "target: " << connectionNode->sender() << endl;
  *m_writer << indent << offsetIndent << connectionNode->signalHandler() << ": ";

  const QStringList argumentTypes = connectionNode->argumentTypes();
  if (argumentTypes.count() == 0) {
    *m_writer << connectionNode->receiver() << "." << connectionNode->slotName() << "()" << endl;
  } else {
    *m_writer << "{" << endl;

    // add comment since we can't easily determine the argument names
    *m_writer << indent << offsetIndent << offsetIndent
              << "// TODO: find names of signal arguments or respective properties to pass to the slot"
              << endl;

    QStringList args;
    for (int i = 0; i < argumentTypes.count(); ++i) {
      args << QString("arg%1").arg(i);
      *m_writer << indent << offsetIndent << offsetIndent
                << "// " << args[i] << " is of type \"" << argumentTypes[i] << "\"" << endl;
    }
    *m_writer << endl;

    *m_writer << indent << offsetIndent << offsetIndent
              << connectionNode->receiver() << "." << connectionNode->slotName() << "(";

    *m_writer << args.join(", ") << ")" << endl;

    *m_writer << indent << offsetIndent << "}" << endl;
  }

  *m_writer << indent << "}" << endl;
}

void QmlWriter::visit(UiPropertyNode *propertyNode)
{
  const QByteArray indent(m_currentIndent, ' ');

  initializeUserProperyWriters();

  UserPropertyWriterHash::const_iterator it = m_userPropertyWriters.constFind(propertyNode->value().userType());
  if (it != m_userPropertyWriters.constEnd()) {
    it.value()->write(*m_writer, indent, propertyNode->name(), propertyNode->value());
  } else {
    m_propertyWriter->write(*m_writer, indent, propertyNode->name(), propertyNode->value());
  }
}

void QmlWriter::visit(UiObjectNode *objectNode)
{
  const QByteArray indent(m_currentIndent, ' ');
  const QByteArray offsetIndent(2, ' ');

  *m_writer << endl;
  *m_writer << indent << objectNode->className().last() << " {" << endl;
  if (!objectNode->id().isEmpty()) {
    *m_writer << indent << offsetIndent << "id: " << objectNode->id() << endl;
  }
  if (!objectNode->name().isEmpty()) {
    *m_writer << indent << offsetIndent << "objectName: \"" << objectNode->id() << "\"" << endl;
  }

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

        policyEnum.nameParts = QStringList() << QLatin1String("Spacer") << QLatin1String("Expanding");
        policyNode = new UiPropertyNode;
        policyNode->setName(QLatin1String("horizontalSizePolicy"));
        policyNode->setValue(QVariant::fromValue(policyEnum));;
        spacerNode->appendChild(policyNode);

        policyEnum.nameParts = QStringList() << QLatin1String("Spacer") << QLatin1String("Minimum");
        policyNode = new UiPropertyNode;
        policyNode->setName(QLatin1String("verticalSizePolicy"));
        policyNode->setValue(QVariant::fromValue(policyEnum));;
        spacerNode->appendChild(policyNode);

      } else if (nameParts[1] == QLatin1String("Vertical")) {
        EnumValue policyEnum;
        UiPropertyNode *policyNode = 0;

        policyEnum.nameParts = QStringList() << QLatin1String("Spacer") << QLatin1String("Minimum");
        policyNode = new UiPropertyNode;
        policyNode->setName(QLatin1String("horizontalSizePolicy"));
        policyNode->setValue(QVariant::fromValue(policyEnum));;
        spacerNode->appendChild(policyNode);

        policyEnum.nameParts = QStringList() << QLatin1String("Spacer") << QLatin1String("Expanding");
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

void QmlWriter::visit(UiTabStopsNode *tabStopsNode)
{
  if (tabStopsNode->tabStops().isEmpty())
    return;

  const QByteArray indent(m_currentIndent, ' ');
  const QByteArray offsetIndent(2, ' ');

  *m_writer << endl;
  *m_writer << indent << "TabStops {" << endl;
  *m_writer << indent << offsetIndent << "tabStops: [ " << tabStopsNode->tabStops().join(", ") << " ]" << endl;
  *m_writer << indent << "}" << endl;
}

void QmlWriter::visit(UiTopNode *topNode)
{
  *m_writer << "import QtWidgets 1.0" << endl;
  *m_writer << endl;

  const QStringList additionalImportLines = m_sharedContext->generateImportLines();
  if (!additionalImportLines.isEmpty()) {
    Q_FOREACH (const QString &importLine, additionalImportLines) {
      *m_writer << importLine << endl;
    }
    *m_writer << endl;
  }

  topNode->acceptChildren(this);
}

void QmlWriter::initializeUserProperyWriters()
{
  if (!m_userPropertyWriters.isEmpty()) {
    return;
  }

  m_userPropertyWriters.insert(qMetaTypeId<FontValue>(), new FontPropertyWriter);
  m_userPropertyWriters.insert(qMetaTypeId<QMargins>(), new MarginsPropertyWriter);
}
