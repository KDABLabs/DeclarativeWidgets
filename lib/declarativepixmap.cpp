/*
  Copyright (C) 2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativepixmap_p.h"

DeclarativePixmapAttached::DeclarativePixmapAttached(QObject *parent)
  : QObject(parent)
{
}

QPixmap DeclarativePixmapAttached::fromFileName(const QString &fileName)
{
  return QPixmap(fileName);
}

class DeclarativePixmap::Private
{
  public:
    QPixmap pixmap;
};

DeclarativePixmap::DeclarativePixmap(QObject *parent)
  : QObject(parent)
  , d(new Private)
{
}

DeclarativePixmap::~DeclarativePixmap()
{
  delete d;
}

QPixmap DeclarativePixmap::pixmap() const
{
  return d->pixmap;
}

void DeclarativePixmap::setPixmap(const QPixmap &pixmap)
{
  if (pixmap.handle() == d->pixmap.handle())
    return;

  const int oldHeight = d->pixmap.height();
  const int oldWidth = d->pixmap.width();
  const bool oldIsNull = d->pixmap.isNull();

  d->pixmap = pixmap;
  emit pixmapChanged(pixmap);

  if (oldHeight != d->pixmap.height())
    emit heightChanged(d->pixmap.height());

  if (oldWidth != d->pixmap.width())
    emit widthChanged(d->pixmap.width());

  if (oldIsNull == d->pixmap.isNull())
    emit isNullChanged(d->pixmap.isNull());
}

int DeclarativePixmap::height() const
{
  return d->pixmap.height();
}

int DeclarativePixmap::width() const
{
  return d->pixmap.width();
}

bool DeclarativePixmap::isNull() const
{
  return d->pixmap.isNull();
}

DeclarativePixmapAttached *DeclarativePixmap::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativePixmapAttached(parent);
}
