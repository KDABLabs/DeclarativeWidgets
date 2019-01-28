/*
  settingsadaptor.cpp

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

#include "settingsadaptor.h"

#include <QDebug>
#include <QSettings>

SettingsAdaptor::SettingsAdaptor(QObject *parent)
  : QObject(parent)
  , m_updatesOnSave(false)
  , m_settings(0)
{
}

void SettingsAdaptor::load(const QString &fileName)
{
  delete m_settings;
  m_settings = new QSettings(fileName, QSettings::IniFormat, this);
}

void SettingsAdaptor::save()
{
  m_settings->sync();
}

void SettingsAdaptor::setUpdatesOnSave(bool enable)
{
  if (enable == m_updatesOnSave)
    return;

  m_updatesOnSave = enable;
  emit updatesOnSaveChanged();
}

bool SettingsAdaptor::updatesOnSave() const
{
  return m_updatesOnSave;
}

QVariant SettingsAdaptor::valueWithDefault(const QString &key, const QVariant &defValue) const
{
    return m_settings->value(key, defValue);
}

QVariant SettingsAdaptor::value(const QString &key) const
{
  return m_settings->value(key);
}

void SettingsAdaptor::setValue(const QString &key, const QVariant &value)
{
  m_settings->setValue(key, value);
}
