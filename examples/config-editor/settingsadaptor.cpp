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
