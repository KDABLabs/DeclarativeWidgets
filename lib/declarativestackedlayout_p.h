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

#ifndef DECLARATIVESTACKEDLAYOUT_P_H
#define DECLARATIVESTACKEDLAYOUT_P_H

#include "declarativelayoutextension.h"

#include <qdeclarative.h>
#include <QStackedLayout>

class DeclarativeStackedLayout : public QStackedLayout
{
  Q_OBJECT

  public:
    explicit DeclarativeStackedLayout(QObject *parent = 0);
};

class DeclarativeStackedLayoutExtension : public DeclarativeLayoutExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)
  Q_PROPERTY(int count READ count)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeStackedLayoutExtension(QObject *parent = 0);

    int count() const;

  protected:
    void addWidget(QWidget *widget);
    void addLayout(QLayout *layout);
};

#endif
