/*
  declarativegridlayout.cpp

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

#include "declarativegridlayout_p.h"

#include "declarativespaceritem_p.h"
#include "layoutcontainerinterface_p.h"

#include <QPointer>
#include <QQmlInfo>
#include <QWidget>

class DeclarativeGridLayoutAttached::Private
{
  public:
    Private(QWidget *w, QLayout *l, DeclarativeSpacerItem *s)
      : row(0), column(0), rowSpan(1), columnSpan(1), alignment(0),
        widget(w), layout(l), spacerItem(s)
    {}

    int row;
    int column;
    int rowSpan;
    int columnSpan;
    Qt::Alignment alignment;

    QPointer<QWidget> widget;
    QPointer<QLayout> layout;
    QPointer<DeclarativeSpacerItem> spacerItem;
    QPointer<QGridLayout> parentLayout;
};

DeclarativeGridLayoutAttached::DeclarativeGridLayoutAttached(QWidget *widget, QObject *parent)
  : QObject(parent), d(new Private(widget, 0, 0))
{
}

DeclarativeGridLayoutAttached::DeclarativeGridLayoutAttached(QLayout *layout, QObject *parent)
  : QObject(parent), d(new Private(0, layout, 0))
{
}

DeclarativeGridLayoutAttached::DeclarativeGridLayoutAttached(DeclarativeSpacerItem *spacerItem, QObject *parent)
  : QObject(parent), d(new Private(0, 0, spacerItem))
{
}

DeclarativeGridLayoutAttached::~DeclarativeGridLayoutAttached()
{
  delete d;
}

void DeclarativeGridLayoutAttached::setParentLayout(QGridLayout *parentLayout)
{
  d->parentLayout = parentLayout;
}

void DeclarativeGridLayoutAttached::setRow(int row)
{
  if (row == d->row)
    return;

  d->row = row;
  emit rowChanged(row);
}

int DeclarativeGridLayoutAttached::row() const
{
  return d->row;
}

void DeclarativeGridLayoutAttached::setColumn(int column)
{
  if (column == d->column)
    return;

  d->column = column;
  emit columnChanged(column);
}

int DeclarativeGridLayoutAttached::column() const
{
  return d->column;
}

void DeclarativeGridLayoutAttached::setRowSpan(int rowSpan)
{
  if (rowSpan == d->rowSpan)
    return;

  d->rowSpan = rowSpan;
  emit rowSpanChanged(rowSpan);
}

int DeclarativeGridLayoutAttached::rowSpan() const
{
  return d->rowSpan;
}

void DeclarativeGridLayoutAttached::setColumnSpan(int columnSpan)
{
  if (columnSpan == d->columnSpan)
    return;

  d->columnSpan = columnSpan;
  emit columnSpanChanged(columnSpan);
}

int DeclarativeGridLayoutAttached::columnSpan() const
{
  return d->columnSpan;
}

void DeclarativeGridLayoutAttached::setAlignment(Qt::Alignment alignment)
{
  if (alignment == d->alignment)
    return;

  d->alignment = alignment;
  emit alignmentChanged(alignment);

  if (d->parentLayout) {
    if (d->widget)
      d->parentLayout->setAlignment(d->widget, d->alignment);

    if (d->layout)
      d->parentLayout->setAlignment(d->layout, d->alignment);
  }
}

Qt::Alignment DeclarativeGridLayoutAttached::alignment() const
{
  return d->alignment;
}

// DeclarativeGridLayout
DeclarativeGridLayout::DeclarativeGridLayout(QObject *parent) : QGridLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeGridLayoutAttached *DeclarativeGridLayout::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeGridLayoutAttached(widget, parent);

  QLayout *layout = qobject_cast<QLayout*>(parent);
  if (layout)
    return new DeclarativeGridLayoutAttached(layout, parent);

  DeclarativeSpacerItem *spacerItem = qobject_cast<DeclarativeSpacerItem*>(parent);
  if (spacerItem)
    return new DeclarativeGridLayoutAttached(spacerItem, parent);

  qmlInfo(parent) << "Can only attach GridLayout to widgets, spacers and layouts";
  return 0;
}

class GridLayoutContainer : public LayoutContainerInterface
{
  public:
    explicit GridLayoutContainer(QGridLayout *layout)
      : m_layout(layout)
    {
      Q_ASSERT(m_layout);
    }

    void addSpacer(DeclarativeSpacerItem *spacerItem);
    void addLayout(QLayout *layout);
    void addWidget(QWidget *widget);
    void setContentsMargins(int left, int top, int right, int bottom);
    void getContentsMargins(int &left, int &top, int &right, int &bottom);

  private:
    QGridLayout *m_layout;
};

DeclarativeGridLayoutExtension::DeclarativeGridLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(new GridLayoutContainer(qobject_cast<QGridLayout*>(parent)), parent)
{
}

void GridLayoutContainer::addLayout(QLayout *layout)
{
  int row = 0;
  int column = 0;
  int rowSpan = 1;
  int columnSpan = 1;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeGridLayout>(layout, false);
  DeclarativeGridLayoutAttached *properties = qobject_cast<DeclarativeGridLayoutAttached*>(attachedProperties);
  if (properties) {
    row = properties->row();
    column = properties->column();
    rowSpan = properties->rowSpan();
    columnSpan = properties->columnSpan();
    alignment = properties->alignment();

    properties->setParentLayout(m_layout);
  }

  m_layout->addLayout(layout, row, column, rowSpan, columnSpan, alignment);
}

void GridLayoutContainer::addSpacer(DeclarativeSpacerItem *spacerItem)
{
    int row = 0;
    int column = 0;
    int rowSpan = 1;
    int columnSpan = 1;
    Qt::Alignment alignment = 0;

    QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeGridLayout>(spacerItem, false);
    DeclarativeGridLayoutAttached *properties = qobject_cast<DeclarativeGridLayoutAttached*>(attachedProperties);
    if (properties) {
      row = properties->row();
      column = properties->column();
      rowSpan = properties->rowSpan();
      columnSpan = properties->columnSpan();
      alignment = properties->alignment();

      properties->setParentLayout(m_layout);
    }

    m_layout->addItem(spacerItem->spacer(), row, column, rowSpan, columnSpan, alignment);
}

void GridLayoutContainer::addWidget(QWidget *widget)
{
  int row = 0;
  int column = 0;
  int rowSpan = 1;
  int columnSpan = 1;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeGridLayout>(widget, false);
  DeclarativeGridLayoutAttached *properties = qobject_cast<DeclarativeGridLayoutAttached*>(attachedProperties);
  if (properties) {
    row = properties->row();
    column = properties->column();
    rowSpan = properties->rowSpan();
    columnSpan = properties->columnSpan();
    alignment = properties->alignment();

    properties->setParentLayout(m_layout);
  }

  m_layout->addWidget(widget, row, column, rowSpan, columnSpan, alignment);
}

void GridLayoutContainer::setContentsMargins(int left, int top, int right, int bottom)
{
  m_layout->setContentsMargins(left, top, right, bottom);
}

void GridLayoutContainer::getContentsMargins(int &left, int &top, int &right, int &bottom)
{
  m_layout->getContentsMargins(&left, &top, &right, &bottom);
}
