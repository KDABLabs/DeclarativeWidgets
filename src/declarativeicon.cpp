/*
  declarativeicon.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativeicon_p.h"

DeclarativeIconAttached::DeclarativeIconAttached(QObject *parent)
  : QObject(parent)
{
}

QString DeclarativeIconAttached::themeName() const
{
  return QIcon::themeName();
}

void DeclarativeIconAttached::setThemeName(const QString &name)
{
  if (name == QIcon::themeName())
    return;

  QIcon::setThemeName(name);
  emit themeNameChanged(name);
}

QStringList DeclarativeIconAttached::themeSearchPaths() const
{
  return QIcon::themeSearchPaths();
}

void DeclarativeIconAttached::setThemeSearchPaths(const QStringList &paths)
{
  if (paths == QIcon::themeSearchPaths())
    return;

  QIcon::setThemeSearchPaths(paths);
  emit themeSearchPathsChanged(paths);
}

QIcon DeclarativeIconAttached::fromTheme(const QString &name)
{
  return QIcon::fromTheme(name);
}

QIcon DeclarativeIconAttached::fromFileName(const QString &fileName)
{
  return QIcon(fileName);
}

class DeclarativeIcon::Private
{
  public:
    QIcon icon;
};

DeclarativeIcon::DeclarativeIcon(QObject *parent)
  : QObject(parent)
  , d(new Private)
{
}

DeclarativeIcon::~DeclarativeIcon()
{
  delete d;
}

QIcon DeclarativeIcon::icon() const
{
  return d->icon;
}

void DeclarativeIcon::setIcon(const QIcon &icon)
{
  if (icon.cacheKey() == d->icon.cacheKey())
    return;

  const QString oldName = d->icon.name();
  const bool oldIsNull = d->icon.isNull();

  d->icon = icon;
  emit iconChanged(icon);

  if (oldName != d->icon.name())
    emit nameChanged(d->icon.name());

  if (oldIsNull == d->icon.isNull())
    emit isNullChanged(d->icon.isNull());
}

QString DeclarativeIcon::name() const
{
  return d->icon.name();
}

bool DeclarativeIcon::isNull() const
{
  return d->icon.isNull();
}

DeclarativeIconAttached *DeclarativeIcon::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeIconAttached(parent);
}
