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

#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QObject>

class BookListProxyModel;
class BooksOfAuthorModel;

class QModelIndex;
class QSqlError;
class QSqlTableModel;

class BookStore : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QObject* authorTable READ authorTable CONSTANT)
  Q_PROPERTY(QObject* bookTable READ bookTable CONSTANT)
  Q_PROPERTY(QObject* booksOfAuthorTable READ booksOfAuthorTable CONSTANT)
  Q_PROPERTY(QObject* bookList READ bookList CONSTANT)

  public:
    explicit BookStore(QObject *parent = 0);

    QObject *authorTable() const;
    QObject *bookTable() const;
    QObject *booksOfAuthorTable() const;
    QObject *bookList() const;

    void reportDbError(const QString &message, const QSqlError &error);

    Q_INVOKABLE int authorId(const QModelIndex &index) const;

  Q_SIGNALS:
    void information(const QString &message);
    void critical(const QString &message);

  private:
    QSqlTableModel *m_authorTable;
    QSqlTableModel *m_bookTable;
    BooksOfAuthorModel *m_booksOfAuthorTable;
    BookListProxyModel *m_bookList;

  private:
    void ensureDbPresence();
};

#endif // BOOKSTORE_H
