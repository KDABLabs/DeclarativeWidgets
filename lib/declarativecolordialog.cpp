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

#include "declarativecolordialog_p.h"

class DeclarativeColorDialogAttached::Private
{
  public:
    Private() : options(0) {}

  public:
    QPointer<QObject> dialogParent;
    QString title;
    QColorDialog::ColorDialogOptions options;
};

DeclarativeColorDialogAttached::DeclarativeColorDialogAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

DeclarativeColorDialogAttached::~DeclarativeColorDialogAttached()
{
  delete d;
}

void DeclarativeColorDialogAttached::setDialogParent(QObject *parent)
{
  if (parent == d->dialogParent)
    return;

  d->dialogParent = parent;
  emit dialogParentChanged(parent);
}

QObject *DeclarativeColorDialogAttached::dialogParent() const
{
  return d->dialogParent;
}

void DeclarativeColorDialogAttached::setTitle(const QString &title)
{
  if (title == d->title)
    return;

  d->title = title;
  emit titleChanged(title);
}

QString DeclarativeColorDialogAttached::title() const
{
  return d->title;
}

QColor DeclarativeColorDialogAttached::getColor(const QColor &initialColor)
{
  QWidget *parent = bestParentWindow(d->dialogParent);
  if (!d->title.isEmpty() || d->options != 0)
    return QColorDialog::getColor(initialColor, parent, d->title, d->options);
  else
    return QColorDialog::getColor(initialColor, parent);
}

QWidget *DeclarativeColorDialogAttached::bestParentWindow(QObject *parent) const
{
  if (!parent)
    parent = this->parent();

  // if parent is a Declarative Object, search the proxied hierarchy
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject)
    parent = declarativeObject->object();

  while (parent) {
    QWidget *widget = qobject_cast<QWidget*>(parent);
    if (widget)
      return widget->topLevelWidget();

    parent = parent->parent();
  }

  return 0;
}

DeclarativeColorDialog::DeclarativeColorDialog(QObject *parent) : DeclarativeWidgetProxy<QColorDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeColorDialogAttached *DeclarativeColorDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeColorDialogAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeColorDialog, QColorDialog)
