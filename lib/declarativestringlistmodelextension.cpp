/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativestringlistmodelextension.h"

#include <QStringListModel>

DeclarativeStringListModelExtension::DeclarativeStringListModelExtension(QObject *parent)
  : DeclarativeObjectExtension(parent)
{
}

QStringListModel *DeclarativeStringListModelExtension::extendedModel() const
{
  QStringListModel *model = qobject_cast<QStringListModel*>(extendedObject());
  Q_ASSERT(model);

  return model;
}

void DeclarativeStringListModelExtension::setStringList(const QStringList &list)
{
  QStringListModel *model = extendedModel();
  if (model->stringList() == list)
    return;

  model->setStringList(list);

  emit stringListChanged(list);
}

QStringList DeclarativeStringListModelExtension::stringList() const
{
  return extendedModel()->stringList();
}
