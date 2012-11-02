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

#ifndef DECLARATIVEHBOXLAYOUT_P_H
#define DECLARATIVEHBOXLAYOUT_P_H

#include "declarativeboxlayout_p.h"
#include "declarativelayoutproxy_p.h"

#include <QHBoxLayout>

class DeclarativeHBoxLayout : public DeclarativeLayoutProxy<QHBoxLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeHBoxLayout(QObject *parent = 0);

    static DeclarativeBoxLayoutAttached *qmlAttachedProperties(QObject *parent);

  protected:
    void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeHBoxLayout, QML_HAS_ATTACHED_PROPERTIES)

#endif
