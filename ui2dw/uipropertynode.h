/*
  uipropertynode.h

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

#ifndef UIPROPERTYNODE_H
#define UIPROPERTYNODE_H

#include "uinode.h"

#include <QHash>
#include <QMargins>
#include <QStringList>
#include <QVariant>

class Parser;
class PropertyValueParser;

Q_DECLARE_METATYPE(QMargins)

struct EnumValue
{
    QStringList nameParts;
};

Q_DECLARE_METATYPE(EnumValue)

struct FontValue
{
    QVariantHash fontProperties;
};

Q_DECLARE_METATYPE(FontValue)

struct IdValue
{
    QString id;
};

Q_DECLARE_METATYPE(IdValue)

struct PixmapValue
{
    QString fileName;
    QString resource;
};

Q_DECLARE_METATYPE(PixmapValue)

struct SetValue
{
    QList<EnumValue> flags;
};

Q_DECLARE_METATYPE(SetValue)

class UiPropertyNode : public UiNode
{
  public:
    UiPropertyNode();

    static UiNode *parse(Parser *parser);

    void accept(UiNodeVisitor *visitor);

    QVariant value() const;
    void setValue(const QVariant &value);

  protected:
    QVariant m_value;

    typedef QHash<QString, PropertyValueParser*> ValueParserHash;
    static ValueParserHash s_valueParsers;

  protected:
    static void initializeValueParsers();
};

#endif // UIPROPERTYNODE_H
