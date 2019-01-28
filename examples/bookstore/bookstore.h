/*
  bookstore.h

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

#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QObject>

class BookListProxyModel;
class BooksOfAuthorModel;

QT_BEGIN_NAMESPACE
class QModelIndex;
class QSqlError;
class QSqlTableModel;
QT_END_NAMESPACE

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
