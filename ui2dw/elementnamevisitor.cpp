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

#include "elementnamevisitor.h"

#include "uiobjectnode.h"
#include "uipropertynode.h"

#include <QDebug>

static EnumValue fixEnumValue(const EnumValue &enumValue)
{
  const QStringList nameParts = enumValue.nameParts;

  // if we have two components and the first one is a Qt class, strip away the Q
  if (nameParts.count() == 2 && nameParts[0].length() > 1 && nameParts[0][1].isUpper()) {
    EnumValue value;
    value.nameParts = nameParts;
    value.nameParts[0] = nameParts[0].mid(1);

    return value;
  }

  return enumValue;
}

static SetValue fixSetValue(const SetValue &setValue)
{
  SetValue value;

  Q_FOREACH (const EnumValue &enumValue, setValue.flags) {
    value.flags << fixEnumValue(enumValue);
  }

  return value;
}

ElementNameVisitor::ElementNameVisitor()
{
}

void ElementNameVisitor::visit(UiObjectNode *objectNode)
{
  QStringList className = objectNode->className();

  // consider all classes that are not namespaced and start with a leading Q
  // followed by another upper case character to be Qt classes we support
  // and strip away the leading Q
  if (className.count() == 1 && className[0][0] == QLatin1Char('Q')) {
    if (className[0].length() > 1 && className[0][1].isUpper()) {
      className[0] = className[0].mid(1); // strip away the leading Q
    }
  }
  objectNode->setClassName(className);

  objectNode->acceptChildren(this);
}

void ElementNameVisitor::visit(UiPropertyNode *propertyNode)
{
  if (propertyNode->value().canConvert<EnumValue>()) {
    propertyNode->setValue(QVariant::fromValue(fixEnumValue(propertyNode->value().value<EnumValue>())));
  } else if (propertyNode->value().canConvert<SetValue>()) {
    propertyNode->setValue(QVariant::fromValue(fixSetValue(propertyNode->value().value<SetValue>())));
  }
}
