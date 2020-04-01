/*
  uipropertynode.cpp

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

#include "uipropertynode.h"

#include "parser.h"
#include "uinodevisitor.h"

#include <QDebug>
#include <QRect>
#include <QXmlStreamReader>

class PropertyValueParser
{
  public:
    virtual ~PropertyValueParser() {}
    virtual QVariant parse(Parser *parser) = 0;
};

class BoolValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      const QString text = parser->reader()->readElementText().toLower();
      if (text == QLatin1String("true")) {
        return QVariant(true);
      } else if (text == QLatin1String("false")) {
        return QVariant(false);
      }
      return QVariant();
    }
};

class DoubleValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      bool ok = false;
      const double value = parser->reader()->readElementText().toDouble(&ok);
      if (ok) {
        return QVariant(value);
      }
      return QVariant();
    }
};

class EnumValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      return QVariant::fromValue(parseEnumString(parser->reader()->readElementText()));
    }

    static EnumValue parseEnumString(const QString &enumString)
    {
      EnumValue value;
      value.nameParts = enumString.split(QLatin1String("::"));
      return value;
    }
};

class NumberValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      bool ok = false;
      const int value = parser->reader()->readElementText().toInt(&ok);
      if (ok) {
        return QVariant(value);
      }
      return QVariant();
    }
};

class PixmapValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      PixmapValue value;

      value.resource = parser->reader()->attributes().value(QLatin1String("resource")).toString();
      value.fileName = parser->reader()->readElementText();

      return QVariant::fromValue(value);
    }
};

class RectValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      QRect r;

      if (!parser->readUntilElement(QLatin1String("rect"), QLatin1String("x"))) {
        parser->reader()->raiseError(QLatin1String("rect property element does not have an x element"));
        return QVariant();
      }
      r.setX(parser->reader()->readElementText().toInt());

      if (!parser->readUntilElement(QLatin1String("rect"), QLatin1String("y"))) {
        parser->reader()->raiseError(QLatin1String("rect property element does not have a y element"));
        return QVariant();
      }
      r.setY(parser->reader()->readElementText().toInt());

      if (!parser->readUntilElement(QLatin1String("rect"), QLatin1String("width"))) {
        parser->reader()->raiseError(QLatin1String("rect property element does not have a width element"));
        return QVariant();
      }
      r.setWidth(parser->reader()->readElementText().toInt());

      if (!parser->readUntilElement(QLatin1String("rect"), QLatin1String("height"))) {
        parser->reader()->raiseError(QLatin1String("rect property element does not have a height element"));
        return QVariant();
      }
      r.setHeight(parser->reader()->readElementText().toInt());

      return QVariant(r);
    }
};

class SetValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      const QStringList flagList = parser->reader()->readElementText().split(QLatin1String("|"));

      SetValue value;

      Q_FOREACH (const QString &flagString, flagList) {
        value.flags << EnumValueParser::parseEnumString(flagString);
      }

      return QVariant::fromValue(value);
    }
};

class SizeValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      QSize s;

      if (!parser->readUntilElement(QLatin1String("size"), QLatin1String("width"))) {
        parser->reader()->raiseError(QLatin1String("size property element does not have a width element"));
        return QVariant();
      }
      s.setWidth(parser->reader()->readElementText().toInt());

      if (!parser->readUntilElement(QLatin1String("size"), QLatin1String("height"))) {
        parser->reader()->raiseError(QLatin1String("size property element does not have a height element"));
        return QVariant();
      }
      s.setHeight(parser->reader()->readElementText().toInt());

      return QVariant(s);
    }
};

class StringValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      return QVariant(parser->reader()->readElementText());
    }
};


class FontValueParser : public PropertyValueParser
{
  public:
    QVariant parse(Parser *parser)
    {
      initializeValueParsers();

      FontValue fontValue;

      while (!parser->reader()->atEnd()) {
        parser->reader()->readNext();
        if (parser->reader()->isEndElement() && parser->reader()->name().compare(QLatin1String("font")) == 0) {
          break;
        }

        if (parser->reader()->isStartElement()) {
          const QString valueName = parser->reader()->name().toString();
          PropertyValueParser *const valueParser = s_valueParsers.value(valueName);
          if (valueParser == 0) {
            qWarning() << "skipping unsupported font property type" << valueName
                       << "in line" << parser->reader()->lineNumber();
            parser->reader()->skipCurrentElement();
            continue;
          }

          const QVariant value = valueParser->parse(parser);
          if (!value.isValid()) {
            qWarning() << "skipping unsupported font property type" << valueName
                       << "in line" << parser->reader()->lineNumber();
            parser->reader()->skipCurrentElement();
            continue;
          }

          fontValue.fontProperties.insert(valueName, value);
        }
      }

      if (!fontValue.fontProperties.isEmpty()) {
        return QVariant::fromValue(fontValue);
      }

      qWarning() << "font property without any supported sub properties";
      return QVariant();
    }

  private:
    typedef QHash<QString, PropertyValueParser*> ValueParserHash;
    static ValueParserHash s_valueParsers;

  private:
    static void initializeValueParsers()
    {
      if (!s_valueParsers.isEmpty()) {
        return;
      }

      s_valueParsers.insert(QLatin1String("bold"), new BoolValueParser);
      s_valueParsers.insert(QLatin1String("family"), new StringValueParser);
      s_valueParsers.insert(QLatin1String("italic"), new BoolValueParser);
      s_valueParsers.insert(QLatin1String("kerning"), new BoolValueParser);
      s_valueParsers.insert(QLatin1String("pointsize"), new NumberValueParser);
      s_valueParsers.insert(QLatin1String("strikeout"), new BoolValueParser);
      s_valueParsers.insert(QLatin1String("underline"), new BoolValueParser);
      s_valueParsers.insert(QLatin1String("weight"), new NumberValueParser);
      s_valueParsers.insert(QLatin1String("stylestrategy"), new EnumValueParser);
    }
};

FontValueParser::ValueParserHash FontValueParser::s_valueParsers;

UiPropertyNode::ValueParserHash UiPropertyNode::s_valueParsers;

UiPropertyNode::UiPropertyNode()
{
}

UiNode *UiPropertyNode::parse(Parser *parser)
{
  const QString objectName = parser->reader()->attributes().value(QLatin1String("name")).toString();
  if (objectName.isEmpty()) {
    parser->reader()->raiseError(QLatin1String("property element is missing the name attribute"));
    return 0;
  }

  if (!parser->reader()->readNextStartElement()) {
    parser->reader()->raiseError(QLatin1String("propery element does not contain child value element"));
    return 0;
  }

  initializeValueParsers();

  PropertyValueParser *const valueParser = s_valueParsers.value(parser->reader()->name().toString());
  if (valueParser == 0) {
    qWarning() << "skipping unsupported property type" << parser->reader()->name().toString()
               << "in line" << parser->reader()->lineNumber();
    parser->reader()->skipCurrentElement();
    return 0;
  }

  const QVariant value = valueParser->parse(parser);
  if (!value.isValid()) {
    qWarning() << "skipping unsupported property type" << parser->reader()->name().toString()
               << "in line" << parser->reader()->lineNumber();
    parser->reader()->skipCurrentElement();
    return 0;
  }

  UiPropertyNode *target = new UiPropertyNode;
  target->setName(objectName);
  target->setValue(value);

  return target;
}

void UiPropertyNode::accept(UiNodeVisitor *visitor)
{
  visitor->visit(this);
}

QVariant UiPropertyNode::value() const
{
  return m_value;
}

void UiPropertyNode::setValue(const QVariant &value)
{
  m_value = value;
}

void UiPropertyNode::initializeValueParsers()
{
  if (!s_valueParsers.isEmpty()) {
    return;
  }

  s_valueParsers.insert(QLatin1String("bool"), new BoolValueParser);
  s_valueParsers.insert(QLatin1String("cstring"), new StringValueParser);
  s_valueParsers.insert(QLatin1String("double"), new DoubleValueParser);
  s_valueParsers.insert(QLatin1String("enum"), new EnumValueParser);
  s_valueParsers.insert(QLatin1String("font"), new FontValueParser);
  s_valueParsers.insert(QLatin1String("number"), new NumberValueParser);
  s_valueParsers.insert(QLatin1String("pixmap"), new PixmapValueParser);
  s_valueParsers.insert(QLatin1String("rect"), new RectValueParser);
  s_valueParsers.insert(QLatin1String("set"), new SetValueParser);
  s_valueParsers.insert(QLatin1String("size"), new SizeValueParser);
  s_valueParsers.insert(QLatin1String("string"), new StringValueParser);
}
