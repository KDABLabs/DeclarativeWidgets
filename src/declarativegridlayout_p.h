/*
  declarativegridlayout_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Tobias Koenig <tobias.koenig@kdab.com>
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

#ifndef DECLARATIVEGRIDLAYOUT_P_H
#define DECLARATIVEGRIDLAYOUT_P_H

#include <QtGlobal>
#include "declarativelayoutextension.h"

#include <QGridLayout>
#include <qqml.h>

class DeclarativeSpacerItem;

class DeclarativeGridLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
  Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
  Q_PROPERTY(int rowSpan READ rowSpan WRITE setRowSpan NOTIFY rowSpanChanged)
  Q_PROPERTY(int columnSpan READ columnSpan WRITE setColumnSpan NOTIFY columnSpanChanged)
  Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

  public:
    DeclarativeGridLayoutAttached(QWidget *widget, QObject *parent);
    DeclarativeGridLayoutAttached(QLayout *layout, QObject *parent);
    DeclarativeGridLayoutAttached(DeclarativeSpacerItem *spacerItem, QObject *parent);
    ~DeclarativeGridLayoutAttached();

    void setParentLayout(QGridLayout *parentLayout);

    void setRow(int row);
    int row() const;

    void setColumn(int column);
    int column() const;

    void setRowSpan(int rowSpan);
    int rowSpan() const;

    void setColumnSpan(int columnSpan);
    int columnSpan() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

  Q_SIGNALS:
    void rowChanged(int row);
    void columnChanged(int column);
    void rowSpanChanged(int rowSpan);
    void columnSpanChanged(int columnSpan);
    void alignmentChanged(Qt::Alignment alignment);

  private:
    class Private;
    Private *const d;
};

class DeclarativeGridLayout : public QGridLayout
{
  Q_OBJECT

  public:
    explicit DeclarativeGridLayout(QObject *parent = 0);

    static DeclarativeGridLayoutAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeGridLayout, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeGridLayoutExtension : public DeclarativeLayoutExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false CONSTANT)
  Q_PROPERTY(DeclarativeLayoutContentsMargins* contentsMargins READ contentsMargins CONSTANT)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeGridLayoutExtension(QObject *parent = 0);
};

#endif
