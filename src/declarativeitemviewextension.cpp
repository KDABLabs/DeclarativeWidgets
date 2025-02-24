/*
  declarativeitemviewextension.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativeitemviewextension_p.h"

DeclarativeItemViewExtension::DeclarativeItemViewExtension(QObject *parent)
  : DeclarativeWidgetExtension(parent)
{
}

QAbstractItemView *DeclarativeItemViewExtension::extendedItemView() const
{
  QAbstractItemView *itemView = qobject_cast<QAbstractItemView*>(extendedWidget());
  Q_ASSERT(itemView);

  return itemView;
}

void DeclarativeItemViewExtension::setModel(QAbstractItemModel *model)
{
  if (extendedItemView()->model() == model)
    return;

  extendedItemView()->setModel(model);

  emit modelChanged(model);
  emit selectionModelChanged(extendedItemView()->selectionModel());
}

QAbstractItemModel *DeclarativeItemViewExtension::model() const
{
  return extendedItemView()->model();
}

void DeclarativeItemViewExtension::setSelectionModel(QItemSelectionModel *selectionModel)
{
  if (extendedItemView()->selectionModel() == selectionModel)
    return;

  extendedItemView()->setSelectionModel(selectionModel);

  emit selectionModelChanged(selectionModel);
}

QItemSelectionModel *DeclarativeItemViewExtension::selectionModel() const
{
  return extendedItemView()->selectionModel();
}

QAbstractItemDelegate *DeclarativeItemViewExtension::itemDelegate() const
{
  return extendedItemView()->itemDelegate();
}

void DeclarativeItemViewExtension::setItemDelegate(QAbstractItemDelegate *itemDelegate)
{
  if (extendedItemView()->itemDelegate() == itemDelegate)
    return;

  extendedItemView()->setItemDelegate(itemDelegate);

  emit itemDelegateChanged(itemDelegate);
}
