/*
  declarativelistitem.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Lova Widmark <znurree@gmail.com>

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

#include "declarativelistitem_p.h"

#include <QStyleOptionViewItem>
#include <QStylePainter>

DeclarativeListItem::DeclarativeListItem()
{
  setMouseTracking(true);
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
}

void DeclarativeListItem::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  QStyleOptionViewItem option;
  option.initFrom(this);

  QStylePainter stylePainter(this);
  stylePainter.drawControl(QStyle::CE_ItemViewItem, option);
}

void DeclarativeListItem::enterEvent(QEvent *event)
{
  Q_UNUSED(event);

  update();
}

void DeclarativeListItem::leaveEvent(QEvent *event)
{
  Q_UNUSED(event);

  update();
}

void DeclarativeListItem::mousePressEvent(QMouseEvent *event)
{
  Q_UNUSED(event);

  emit clicked();
}
