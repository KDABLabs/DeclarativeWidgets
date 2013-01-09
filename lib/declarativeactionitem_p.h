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

#ifndef DECLARATIVEDeclarativeActionItem_P_H
#define DECLARATIVEDeclarativeActionItem_P_H

#include <QObject>
#include <QVariant>

class QAction;

class DeclarativeActionItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QVariant action READ qmlAction WRITE setAction NOTIFY actionChanged)

  public:
    explicit DeclarativeActionItem(QObject *parent = 0);

    QAction* action();

  Q_SIGNALS:
    void actionChanged();

  private:
    void setAction(const QVariant &action);
    QVariant qmlAction() const;

    QVariant m_action;
    QAction* m_placeholderAction;
    QAction* m_qAction;
};

#endif
