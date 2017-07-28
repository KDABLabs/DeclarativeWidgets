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

#ifndef DECLARATIVETABLEVIEWEXTENSION_P_H
#define DECLARATIVETABLEVIEWEXTENSION_P_H

#include "declarativewidgets_export.h"
#include "declarativeitemviewextension_p.h"

class QHeaderView;
class QTableView;

class DECLARATIVEWIDGETS_EXPORT DeclarativeTableViewExtension : public DeclarativeItemViewExtension
{
  Q_OBJECT

  Q_PROPERTY(QHeaderView* horizontalHeader READ horizontalHeader WRITE setHorizontalHeader NOTIFY horizontalHeaderChanged)
  Q_PROPERTY(QHeaderView* verticalHeader READ verticalHeader WRITE setVerticalHeader NOTIFY verticalHeaderChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)

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
