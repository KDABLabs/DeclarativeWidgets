/*
  declarativeiconloader.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2018 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer <kevin.krammer@kdab.com>
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

#include "declarativeiconloader_p.h"

DeclarativeIconLoader::DeclarativeIconLoader(QObject *parent)
    : QObject(parent)
{
}

QString DeclarativeIconLoader::themeName() const
{
    return QIcon::themeName();
}

void DeclarativeIconLoader::setThemeName(const QString &name)
{
    if (name == QIcon::themeName())
        return;

    QIcon::setThemeName(name);

    emit themeNameChanged(name);
}

QStringList DeclarativeIconLoader::themeSearchPaths() const
{
    return QIcon::themeSearchPaths();
}

void DeclarativeIconLoader::setThemeSearchPaths(const QStringList &paths)
{
    if (paths == QIcon::themeSearchPaths())
        return;

    QIcon::setThemeSearchPaths(paths);

    emit themeSearchPathsChanged(paths);
}

QIcon DeclarativeIconLoader::fromTheme(const QString &name)
{
  return QIcon::fromTheme(name);
}

QIcon DeclarativeIconLoader::fromFileName(const QString &fileName)
{
    return QIcon(fileName);
}

QObject *DeclarativeIconLoader::instance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return new DeclarativeIconLoader();
}
