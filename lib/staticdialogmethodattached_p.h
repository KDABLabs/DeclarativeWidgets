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

#ifndef STATICDIALOGMETHODATTACHED_P_H
#define STATICDIALOGMETHODATTACHED_P_H

#include <QObject>

class StaticDialogMethodAttached : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QObject* parent READ dialogParent WRITE setDialogParent NOTIFY dialogParentChanged)

  protected:
    explicit StaticDialogMethodAttached(QObject *parent = 0);

  public:
    ~StaticDialogMethodAttached();

    void setDialogParent(QObject *parent);
    QObject *dialogParent() const;

  Q_SIGNALS:
    void dialogParentChanged(QObject *parent);

  protected:
    QWidget *bestParentWindow() const;

  private:
    class Private;
    Private *const d;
};

#endif // STATICDIALOGMETHODATTACHED_P_H
