/*
  settingsadaptor.h

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

#ifndef SETTINGSADAPTOR_H
#define SETTINGSADAPTOR_H

#include <QObject>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

class SettingsAdaptor : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool updatesOnSave READ updatesOnSave WRITE setUpdatesOnSave NOTIFY updatesOnSaveChanged)

  public:
    explicit SettingsAdaptor(QObject *parent = 0);

    void load(const QString &fileName);
    void save();

    void setUpdatesOnSave(bool enable);
    bool updatesOnSave() const;

    Q_INVOKABLE QVariant valueWithDefault(const QString &key, const QVariant &defValue) const;
    Q_INVOKABLE QVariant value(const QString &key) const;

  public Q_SLOTS:
    void setValue(const QString &key, const QVariant &value);

  Q_SIGNALS:
    void updatesOnSaveChanged();

  private:
    bool m_updatesOnSave;
    QSettings *m_settings;
};

#endif // SETTINGSADAPTOR_H
