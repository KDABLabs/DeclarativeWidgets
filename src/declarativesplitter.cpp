/*
  declarativesplitter.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativesplitter_p.h"

#include <QPointer>
#include <QWidget>
#include <QQmlInfo>

class DeclarativeSplitterAttached::Private
{
  public:
    Private(QWidget *w)
      : stretch(0)
      , widget(w)
    {
    }

    int stretch;

    QPointer<QWidget> widget;
};

DeclarativeSplitterAttached::DeclarativeSplitterAttached(QWidget *widget, QObject *parent)
  : QObject(parent)
  , d(new Private(widget))
{
}

DeclarativeSplitterAttached::~DeclarativeSplitterAttached()
{
  delete d;
}

void DeclarativeSplitterAttached::setStretch(int stretch)
{
  if (stretch == d->stretch)
    return;

  d->stretch = stretch;

  emit stretchChanged(stretch);
}

int DeclarativeSplitterAttached::stretch() const
{
  return d->stretch;
}

DeclarativeSplitter::DeclarativeSplitter(QWidget *parent)
  : QSplitter(parent)
{
}

DeclarativeSplitterAttached *DeclarativeSplitter::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeSplitterAttached(widget, parent);

  qmlInfo(parent) << "Can only attach Splitter to widgets";

  return Q_NULLPTR;
}
