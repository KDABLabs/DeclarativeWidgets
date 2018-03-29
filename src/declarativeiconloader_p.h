/*
  declarativeiconloader_p.h

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

#ifndef DECLARATIVEICONLOADER_P_H
#define DECLARATIVEICONLOADER_P_H

#include <QIcon>
#include <QObject>

QT_BEGIN_NAMESPACE
class QQmlEngine;
class QJSEngine;
QT_END_NAMESPACE

class DeclarativeIconLoader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString themeName READ themeName WRITE setThemeName NOTIFY themeNameChanged)
    Q_PROPERTY(QStringList themeSearchPaths READ themeSearchPaths WRITE setThemeSearchPaths NOTIFY themeSearchPathsChanged)

public:
    explicit DeclarativeIconLoader(QObject *parent = Q_NULLPTR);

    QString themeName() const;
    void setThemeName(const QString &name);

    QStringList themeSearchPaths() const;
    void setThemeSearchPaths(const QStringList &paths);

    Q_INVOKABLE QIcon fromTheme(const QString &name);
    Q_INVOKABLE QIcon fromFileName(const QString &fileName);

    static QObject *instance(QQmlEngine *engine, QJSEngine *scriptEngine);

Q_SIGNALS:
    void themeNameChanged(const QString &themeName);
    void themeSearchPathsChanged(const QStringList &themeSearchPaths);
};

#endif // DECLARATIVEICONLOADER_P_H
