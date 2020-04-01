/*
  booklistproxymodel.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer <kevin.krammer@kdab.com>
  Author: Nathan Collins <nathan.collins@kdab.com>

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

#include "booklistproxymodel.h"

#include <QDebug>

static QHash<int, QByteArray> createRolesToNameMapping()
{
  QHash<int, QByteArray> mapping;

  mapping[BookListProxyModel::BookIdRole] = "bookId";
  mapping[BookListProxyModel::BookTitleRole] = "bookTitle";
  mapping[BookListProxyModel::BookPriceRole] = "bookPrice";
  mapping[BookListProxyModel::BookNotesRole] = "bookNotes";
  mapping[BookListProxyModel::AuthorIdRole] = "authorId";
  mapping[BookListProxyModel::AuthorFirstNameRole] = "authorFirstName";
  mapping[BookListProxyModel::AuthorLastNameRole] = "authorLastName";

  return mapping;
}

BookListProxyModel::BookListProxyModel(QObject *parent)
  : QAbstractProxyModel(parent),
    m_rolesToNames(createRolesToNameMapping())
{
}

void BookListProxyModel::addColumnToRoleMapping(int column, int role)
{
  m_sourceColumnsToRoles[column] = role;
  m_rolesToSourceColumns[role] = column;
}

QHash<int, QByteArray> BookListProxyModel::roleNames() const
{
    return m_rolesToNames;
}

int BookListProxyModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);

  return 1;
}

int BookListProxyModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  return sourceModel()->rowCount();
}

QModelIndex BookListProxyModel::index(int row, int column, const QModelIndex &parent) const
{
  Q_ASSERT(column == 0);
  Q_UNUSED(column);

  if (parent.isValid())
    return QModelIndex();

  return createIndex(row, 0, (quintptr) 0);
}

QModelIndex BookListProxyModel::parent(const QModelIndex &child) const
{
  Q_UNUSED(child);
  return QModelIndex();
}

QVariant BookListProxyModel::data(const QModelIndex &proxyIndex, int role) const
{
  const int row = proxyIndex.row();
  const int column = m_rolesToSourceColumns.contains(role) ? m_rolesToSourceColumns[role] : 0;

  const QModelIndex sourceIndex = sourceModel()->index(row, column);
  return sourceIndex.data(Qt::DisplayRole);
}

QModelIndex BookListProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
  return createIndex(sourceIndex.row(), 0, sourceIndex.column());
}

QModelIndex BookListProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
  return sourceModel()->index(proxyIndex.row(), proxyIndex.internalId());
}
