/*
  declarativespaceritem.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2014-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativespaceritem_p.h"

#include <QSpacerItem>

class DeclarativeSpacerItem::Private : public QSpacerItem
{
    DeclarativeSpacerItem *q;

  public:
    Private(DeclarativeSpacerItem *parent)
      : QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum), q(parent),
        horizontalSizePolicy(QSizePolicy::Minimum), verticalSizePolicy(QSizePolicy::Minimum)
    {
    }

    ~Private()
    {
      q->d = 0;
    }

    void setGeometry(const QRect &rect)
    {
      const QRect oldRect = geometry();
      QSpacerItem::setGeometry(rect);

      if (oldRect.width() != geometry().width()) {
        Q_EMIT q->widthChanged(geometry().width());
      }

      if (oldRect.height() != geometry().height()) {
        Q_EMIT q->heightChanged(geometry().height());
      }

      if (oldRect.size() != rect.size()) {
        Q_EMIT q->sizeHintChanged();
      }
    }

  public:
    QSizePolicy::Policy horizontalSizePolicy;
    QSizePolicy::Policy verticalSizePolicy;
};

DeclarativeSpacerItem::DeclarativeSpacerItem(QObject *parent)
  : QObject(parent)
  , d(new Private(this))
{
}

DeclarativeSpacerItem::~DeclarativeSpacerItem()
{
  delete d;
}

QSpacerItem *DeclarativeSpacerItem::spacer() const
{
  return d;
}

int DeclarativeSpacerItem::width() const
{
  return d->geometry().width();
}

int DeclarativeSpacerItem::height() const
{
  return d->geometry().height();
}

void DeclarativeSpacerItem::setSizeHint(const QSize &sizeHint)
{
  d->changeSize(sizeHint.width(), sizeHint.height(), d->horizontalSizePolicy, d->verticalSizePolicy);

  // notification signal handled by setGeometry()
}

QSize DeclarativeSpacerItem::sizeHint() const
{
  return d->geometry().size();
}

void DeclarativeSpacerItem::setHorizontalPolicy(SizePolicy policy)
{
  //QSizePolicy::Policy sizePolicy = d->convertToPolicyEnum(policy);
  QSizePolicy::Policy sizePolicy = static_cast<QSizePolicy::Policy>(policy);

  if (sizePolicy == d->horizontalSizePolicy)
    return;

  d->horizontalSizePolicy = sizePolicy;

  const QRect rect = d->geometry();
  d->changeSize(rect.width(), rect.height(), d->horizontalSizePolicy, d->verticalSizePolicy);

  emit horizontalPolicyChanged();
}

DeclarativeSpacerItem::SizePolicy DeclarativeSpacerItem::horizontalPolicy() const
{
  return static_cast<SizePolicy>(d->horizontalSizePolicy);
}

void DeclarativeSpacerItem::setVerticalPolicy(SizePolicy policy)
{
  //QSizePolicy::Policy sizePolicy = d->convertToPolicyEnum(policy);
  QSizePolicy::Policy sizePolicy = static_cast<QSizePolicy::Policy>(policy);

  if (sizePolicy == d->verticalSizePolicy)
    return;

  d->verticalSizePolicy = sizePolicy;

  const QRect rect = d->geometry();
  d->changeSize(rect.width(), rect.height(), d->horizontalSizePolicy, d->verticalSizePolicy);

  emit verticalPolicyChanged();
}

DeclarativeSpacerItem::SizePolicy DeclarativeSpacerItem::verticalPolicy() const
{
  return static_cast<SizePolicy>(d->verticalSizePolicy);
}
