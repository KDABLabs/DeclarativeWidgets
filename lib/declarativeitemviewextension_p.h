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

#ifndef DECLARATIVEITEMVIEWEXTENSION_P_H
#define DECLARATIVEITEMVIEWEXTENSION_P_H

#include "declarativewidgetextension.h"

class QAbstractItemModel;
class QAbstractItemView;
class QItemSelectionModel;

class DeclarativeItemViewPropertySignals
{
  protected:
    virtual ~DeclarativeItemViewPropertySignals() {}

    // signal signatures
    virtual void modelChanged(QAbstractItemModel *model) = 0;
    virtual void selectionModelChanged(QItemSelectionModel *selectionModel) = 0;
};

class DeclarativeItemViewExtension : public DeclarativeWidgetExtension, protected DeclarativeItemViewPropertySignals
{
  Q_OBJECT

  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeItemViewExtension(QObject *parent = 0);

    QAbstractItemView *extendedItemView() const;

    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

    void setSelectionModel(QItemSelectionModel *selectionModel);
    QItemSelectionModel *selectionModel() const;

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel *model);
    void selectionModelChanged(QItemSelectionModel *selectionModel);
};

#endif
