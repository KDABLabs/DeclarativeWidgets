/*
  declarativeboxlayout.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativeboxlayout_p.h"

#include "declarativespaceritem_p.h"

#include <QPointer>
#include <QWidget>

class DeclarativeBoxLayoutAttached::Private
{
  public:
    Private(QWidget *w, QLayout *l, DeclarativeSpacerItem *s)
      : stretch(0), alignment(0), widget(w), layout(l), spacerItem(s) {}

    int stretch;
    Qt::Alignment alignment;

    QPointer<QWidget> widget;
    QPointer<QLayout> layout;
    QPointer<DeclarativeSpacerItem> spacerItem;
    QPointer<QBoxLayout> parentLayout;
};

DeclarativeBoxLayoutAttached::DeclarativeBoxLayoutAttached(QWidget *widget, QObject *parent)
  : QObject(parent), d(new Private(widget, 0, 0))
{
}

DeclarativeBoxLayoutAttached::DeclarativeBoxLayoutAttached(QLayout *layout, QObject *parent)
  : QObject(parent), d(new Private(0, layout, 0))
{
}

DeclarativeBoxLayoutAttached::DeclarativeBoxLayoutAttached(DeclarativeSpacerItem *spacerItem, QObject *parent)
  : QObject(parent), d(new Private(0, 0, spacerItem))
{
}

DeclarativeBoxLayoutAttached::~DeclarativeBoxLayoutAttached()
{
  delete d;
}

void DeclarativeBoxLayoutAttached::setParentLayout(QBoxLayout *parentLayout)
{
  d->parentLayout = parentLayout;
}

void DeclarativeBoxLayoutAttached::setStretch(int stretch)
{
  if (stretch == d->stretch)
    return;

  d->stretch = stretch;
  emit stretchChanged(stretch);
}

int DeclarativeBoxLayoutAttached::stretch() const
{
  return d->stretch;
}

void DeclarativeBoxLayoutAttached::setAlignment(Qt::Alignment alignment)
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

Qt::Alignment DeclarativeBoxLayoutAttached::alignment() const
{
  return d->alignment;
}

