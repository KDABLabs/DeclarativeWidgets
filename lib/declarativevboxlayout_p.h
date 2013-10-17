/*
  Copyright (C) 2012-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEVBOXLAYOUT_P_H
#define DECLARATIVEVBOXLAYOUT_P_H

#include "declarativeboxlayout_p.h"
#include "declarativelayoutextension.h"

#include <qdeclarative.h>
#include <QVBoxLayout>

class DeclarativeVBoxLayout : public QVBoxLayout
{
  Q_OBJECT

  public:
    explicit DeclarativeVBoxLayout(QObject *parent = 0);

    static DeclarativeBoxLayoutAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeVBoxLayout, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeVBoxLayoutExtension : public DeclarativeLayoutExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeVBoxLayoutExtension(QObject *parent = 0);
};

#endif
