/*
  declarativeitemviewextension_p.h

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

#ifndef DECLARATIVEITEMVIEWEXTENSION_P_H
#define DECLARATIVEITEMVIEWEXTENSION_P_H

#include <QtGlobal>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>

class QAbstractItemDelegate;

#include "declarativewidgetextension.h"

QT_BEGIN_NAMESPACE
class QAbstractItemDelegate;
QT_END_NAMESPACE

class DeclarativeItemViewPropertySignals
{
  protected:
    virtual ~DeclarativeItemViewPropertySignals() {}

    // signal signatures
    virtual void modelChanged(QAbstractItemModel *model) = 0;
    virtual void selectionModelChanged(QItemSelectionModel *selectionModel) = 0;
    virtual void itemDelegateChanged(QAbstractItemDelegate *itemDelegate) = 0;
};

class DeclarativeItemViewExtension : public DeclarativeWidgetExtension, protected DeclarativeItemViewPropertySignals
{
  Q_OBJECT

  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)
  Q_PROPERTY(QAbstractItemDelegate* itemDelegate READ itemDelegate WRITE setItemDelegate NOTIFY itemDelegateChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false CONSTANT)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeItemViewExtension(QObject *parent = 0);

    QAbstractItemView *extendedItemView() const;

    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

    void setSelectionModel(QItemSelectionModel *selectionModel);
    QItemSelectionModel *selectionModel() const;

    QAbstractItemDelegate *itemDelegate() const;
    void setItemDelegate(QAbstractItemDelegate *itemDelegate);

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel *model) Q_DECL_OVERRIDE;
    void selectionModelChanged(QItemSelectionModel *selectionModel) Q_DECL_OVERRIDE;
    void itemDelegateChanged(QAbstractItemDelegate *itemDelegate) Q_DECL_OVERRIDE;
};

#endif
