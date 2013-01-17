/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

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

#include "declarativeitemviewextension_p.h"

#include <QAbstractItemView>

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

