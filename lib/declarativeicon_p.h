/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEICON_P_H
#define DECLARATIVEICON_P_H

#include <QIcon>
#include <QObject>
#include <qqml.h>
#include <QStringList>

class DeclarativeIconAttached : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString themeName READ themeName WRITE setThemeName NOTIFY themeNameChanged)
  Q_PROPERTY(QStringList themeSearchPaths READ themeSearchPaths WRITE setThemeSearchPaths NOTIFY themeSearchPathsChanged)

  public:
    explicit DeclarativeIconAttached(QObject *parent = 0);

    QString themeName() const;
    void setThemeName(const QString &name);

    QStringList themeSearchPaths() const;
    void setThemeSearchPaths(const QStringList &paths);

    Q_INVOKABLE QIcon fromTheme(const QString &name);
    Q_INVOKABLE QIcon fromFileName(const QString &fileName);

  Q_SIGNALS:
    void themeNameChanged(const QString &themeName);
    void themeSearchPathsChanged(const QStringList &themeSearchPaths);
};

class DeclarativeIcon : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)
  Q_PROPERTY(QString name READ name NOTIFY nameChanged)
  Q_PROPERTY(bool isNull READ isNull NOTIFY isNullChanged)

  public:
    explicit DeclarativeIcon(QObject *parent = 0);
    ~DeclarativeIcon();

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QString name() const;

    bool isNull() const;

    static DeclarativeIconAttached *qmlAttachedProperties(QObject *parent);

  Q_SIGNALS:
    void iconChanged(const QIcon &icon);
    void nameChanged(const QString &name);
    void isNullChanged(bool isNull);

  private:
    class Private;
    Private *const d;
};

QML_DECLARE_TYPEINFO(DeclarativeIcon, QML_HAS_ATTACHED_PROPERTIES)

#endif // DECLARATIVEICON_P_H
