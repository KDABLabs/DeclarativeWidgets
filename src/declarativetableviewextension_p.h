/*
  declarativetableviewextension_p.h

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

#ifndef DECLARATIVETABLEVIEWEXTENSION_P_H
#define DECLARATIVETABLEVIEWEXTENSION_P_H

#include <QtGlobal>
#include "declarativeitemviewextension_p.h"

QT_BEGIN_NAMESPACE
class QHeaderView;
class QTableView;
QT_END_NAMESPACE

class DeclarativeTableViewExtension : public DeclarativeItemViewExtension
{
  Q_OBJECT

  Q_PROPERTY(QHeaderView* horizontalHeader READ horizontalHeader WRITE setHorizontalHeader NOTIFY horizontalHeaderChanged)
  Q_PROPERTY(QHeaderView* verticalHeader READ verticalHeader WRITE setVerticalHeader NOTIFY verticalHeaderChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false CONSTANT)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeTableViewExtension(QObject *parent = 0);

    QTableView *extendedTableView() const;

    void setHorizontalHeader(QHeaderView *header);
    QHeaderView *horizontalHeader() const;

    void setVerticalHeader(QHeaderView *header);
    QHeaderView *verticalHeader() const;

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel *model);
    void selectionModelChanged(QItemSelectionModel *selectionModel);

    void horizontalHeaderChanged(QHeaderView *header);
    void verticalHeaderChanged(QHeaderView *header);
};

#endif // DECLARATIVETABLEVIEWEXTENSION_P_H
