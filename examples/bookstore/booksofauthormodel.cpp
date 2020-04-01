/*
  booksofauthormodel.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "booksofauthormodel.h"

#include "bookstore.h"

#include <QSqlError>

BooksOfAuthorModel::BooksOfAuthorModel(BookStore *store) :
  QSqlQueryModel(store),
  m_store(store),
  m_authorId(-1)
{
  setHeaderData(1, Qt::Horizontal, tr("Title"));
  setHeaderData(2, Qt::Horizontal, tr("Price"));
  setHeaderData(3, Qt::Horizontal, tr("Notes"));

  refresh();
}

void BooksOfAuthorModel::setAuthor(int authorId)
{
  m_authorId = authorId;
  refresh();
}

void BooksOfAuthorModel::refresh()
{
  QString query = QString::fromUtf8("SELECT title, price, notes FROM book");
  if (m_authorId != -1)
    query += QString::fromUtf8(" WHERE authorid = %1").arg(m_authorId);

  setQuery(query);
  if (lastError().type() != QSqlError::NoError)
    m_store->reportDbError(tr("Error running showAuthor query"), lastError());
}
