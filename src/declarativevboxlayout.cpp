/*
  declarativevboxlayout.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Tobias Koenig <tobias.koenig@kdab.com>
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

#include "declarativevboxlayout_p.h"

#include "declarativespaceritem_p.h"
#include "layoutcontainerinterface_p.h"

#include <QQmlInfo>
#include <QWidget>

DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent)
  : QVBoxLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeBoxLayoutAttached *DeclarativeVBoxLayout::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeBoxLayoutAttached(widget, parent);

  QLayout *layout = qobject_cast<QLayout*>(parent);
  if (layout)
    return new DeclarativeBoxLayoutAttached(layout, parent);

  DeclarativeSpacerItem *spacerItem = qobject_cast<DeclarativeSpacerItem*>(parent);
  if (spacerItem)
    return new DeclarativeBoxLayoutAttached(spacerItem, parent);

  qmlInfo(parent) << "Can only attach VBoxLayout to widgets, spacers and layouts";
  return 0;
}

class VBoxLayoutContainer : public LayoutContainerInterface
{
  public:
    explicit VBoxLayoutContainer(QVBoxLayout *layout)
      : m_layout(layout)
    {
      Q_ASSERT(m_layout);
    }

    void addLayout(QLayout *layout);
    void addSpacer(DeclarativeSpacerItem *spacerItem);
    void addWidget(QWidget *widget);
    void setContentsMargins(int left, int top, int right, int bottom);
    void getContentsMargins(int &left, int &top, int &right, int &bottom);

  private:
    QVBoxLayout *m_layout;
};


DeclarativeVBoxLayoutExtension::DeclarativeVBoxLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(new VBoxLayoutContainer(qobject_cast<QVBoxLayout*>(parent)), parent)
{
}

void VBoxLayoutContainer::addLayout(QLayout *layout)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeVBoxLayout>(layout, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_layout);
  }

  m_layout->addLayout(layout, stretch);
  m_layout->setAlignment(layout, alignment);
}

void VBoxLayoutContainer::addSpacer(DeclarativeSpacerItem *spacerItem)
{
    m_layout->addSpacerItem(spacerItem->spacer());
}

void VBoxLayoutContainer::addWidget(QWidget *widget)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeVBoxLayout>(widget, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_layout);
  }

  m_layout->addWidget(widget, stretch, alignment);
}

void VBoxLayoutContainer::setContentsMargins(int left, int top, int right, int bottom)
{
  m_layout->setContentsMargins(left, top, right, bottom);
}

void VBoxLayoutContainer::getContentsMargins(int &left, int &top, int &right, int &bottom)
{
  m_layout->getContentsMargins(&left, &top, &right, &bottom);
}
