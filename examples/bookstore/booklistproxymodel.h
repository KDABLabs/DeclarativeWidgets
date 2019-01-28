/*
  booklistproxymodel.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef BOOKLISTPROXYMODEL_H
#define BOOKLISTPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QHash>

class BookListProxyModel : public QAbstractProxyModel
{
  Q_OBJECT

  public:
    enum Roles {
      BookIdRole = Qt::UserRole + 1,
      BookTitleRole,
      BookPriceRole,
      BookNotesRole,
      AuthorIdRole,
      AuthorFirstNameRole,
      AuthorLastNameRole
    };

    explicit BookListProxyModel(QObject *parent = 0);

    void addColumnToRoleMapping(int column, int role);
    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    QVariant data(const QModelIndex &proxyIndex, int role) const;

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

  private:
    const QHash<int, QByteArray> m_rolesToNames;

    QHash<int, int> m_rolesToSourceColumns;
    QHash<int, int> m_sourceColumnsToRoles;
};

#endif // BOOKLISTPROXYMODEL_H
