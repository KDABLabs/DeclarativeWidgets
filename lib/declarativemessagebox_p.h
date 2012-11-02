/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

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

#ifndef DECLARATIVEMESSAGEBOX_P_H
#define DECLARATIVEMESSAGEBOX_P_H

#include "declarativeobjectproxy_p.h"

#include <QMessageBox>

class DeclarativeMessageBoxAttached : public QObject
{
  Q_OBJECT

  public:
    DeclarativeMessageBoxAttached(QObject *parent = 0);

    Q_INVOKABLE void about(QObject *parent, const QString &title, const QString &text);
    Q_INVOKABLE void aboutQt(QObject *parent, const QString &title);
    Q_INVOKABLE int critical(QObject *parent, const QString &title, const QString &text,
                             int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);
    Q_INVOKABLE int information(QObject *parent, const QString &title, const QString &text,
                                int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);
    Q_INVOKABLE int question(QObject *parent, const QString &title, const QString &text,
                             int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);
    Q_INVOKABLE int warning(QObject *parent, const QString &title, const QString &text,
                            int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);

  private:
    QWidget *bestParentWindow(QObject *parent) const;
};

class DeclarativeMessageBox : public DeclarativeObjectProxy<QMessageBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMessageBox(QObject *parent = 0);

    static DeclarativeMessageBoxAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeMessageBox, QML_HAS_ATTACHED_PROPERTIES)

#endif
