#ifndef SETTINGSADAPTOR_H
#define SETTINGSADAPTOR_H

#include <QObject>
#include <QVariant>

class QSettings;

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
