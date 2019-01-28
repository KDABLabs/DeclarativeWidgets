/*
  fontproperyvisitor.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2014-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "fontproperyvisitor.h"

#include "uipropertynode.h"

namespace {

enum QmlFontWeightValue {
  Light = 25,
  Normal = 50,
  DemiBold = 63,
  Bold = 75,
  Black = 87
};

EnumValue weightIntToEnumValue(int weight)
{
  EnumValue enumValue;
  enumValue.nameParts << QLatin1String("Font");

  int minDistance = abs(weight - Light);
  QString qmlWeight = QLatin1String("Light");

  int distance = abs(weight - Normal);
  if (distance < minDistance) {
    minDistance = distance;
    qmlWeight = QLatin1String("Normal");
  }

  distance = abs(weight - DemiBold);
  if (distance < minDistance) {
    minDistance = distance;
    qmlWeight = QLatin1String("DemiBold");
  }

  distance = abs(weight - Bold);
  if (distance < minDistance) {
    minDistance = distance;
    qmlWeight = QLatin1String("Bold");
  }

  distance = abs(weight - Black);
  if (distance < minDistance) {
    minDistance = distance;
    qmlWeight = QLatin1String("Black");
  }

  enumValue.nameParts << qmlWeight;

  return enumValue;
}

}

FontProperyVisitor::FontProperyVisitor(const SharedVisitationContext &sharedContext)
  : UiNodeVisitor(sharedContext)
  , m_unhandledSubProperties(QSet<QString>() << "stylestrategy" << "kerning")
{
}

void FontProperyVisitor::visit(UiPropertyNode *propertyNode)
{
  if (propertyNode->value().userType() != qMetaTypeId<FontValue>()) {
    return;
  }

  FontValue fontValue = propertyNode->value().value<FontValue>();

  const QVariantHash fontProperties = fontValue.fontProperties;
  fontValue.fontProperties.clear();

  QVariantHash::const_iterator it = fontProperties.constBegin();
  QVariantHash::const_iterator endIt = fontProperties.constEnd();
  for (; it != endIt; ++it) {

    // skip font properties that are not available in QML
    if (m_unhandledSubProperties.contains(it.key())) {
      continue;
    }

    if (it.key() == QLatin1String("pointsize")) {
      fontValue.fontProperties.insert(QLatin1String("pointSize"), it.value());
    } else if (it.key() == QLatin1String("weight")) {
      EnumValue weightValue = weightIntToEnumValue(it.value().toInt());
      weightValue.nameParts.prepend(m_sharedContext->registerImport("QtQuick", "1.0"));
      fontValue.fontProperties.insert(it.key(), QVariant::fromValue(weightValue));
    } else {
      fontValue.fontProperties.insert(it.key(), it.value());
    }
  }

  propertyNode->setValue(QVariant::fromValue(fontValue));
}
