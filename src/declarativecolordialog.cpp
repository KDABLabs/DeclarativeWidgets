/*
  declarativecolordialog.cpp

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

#include "declarativecolordialog_p.h"

class DeclarativeColorDialogAttached::Private
{
  public:
    Private() : options(0) {}

  public:
    QString title;
    QColorDialog::ColorDialogOptions options;
};

DeclarativeColorDialogAttached::DeclarativeColorDialogAttached(QObject *parent)
  : StaticDialogMethodAttached(parent), d(new Private)
{
}

DeclarativeColorDialogAttached::~DeclarativeColorDialogAttached()
{
  delete d;
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

void DeclarativeColorDialogAttached::setOptions(unsigned int options)
{
  if (d->options == options)
    return;

  d->options = static_cast<QColorDialog::ColorDialogOptions>(options);
  emit optionsChanged(options);
}

unsigned int DeclarativeColorDialogAttached::options() const
{
  return d->options;
}

QColor DeclarativeColorDialogAttached::getColor()
{
  QWidget *parent = bestParentWindow();
  if (!d->title.isEmpty() || d->options != 0)
    return QColorDialog::getColor(Qt::white, parent, d->title, d->options);
  else
    return QColorDialog::getColor(Qt::white, parent);
}

QColor DeclarativeColorDialogAttached::getColor(const QColor &initialColor)
{
  QWidget *parent = bestParentWindow();
  if (!d->title.isEmpty() || d->options != 0)
    return QColorDialog::getColor(initialColor, parent, d->title, d->options);
  else
    return QColorDialog::getColor(initialColor, parent);
}

Q_DECLARE_METATYPE(Qt::WindowFlags)

DeclarativeColorDialog::DeclarativeColorDialog(QWidget *parent) : QColorDialog(parent)
{
  setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
}

DeclarativeColorDialogAttached *DeclarativeColorDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeColorDialogAttached(parent);
}
