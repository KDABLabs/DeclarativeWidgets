#include "configeditor.h"

#include "settingsadaptor.h"

#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

ConfigEditor::ConfigEditor(QObject *parent)
  : QObject(parent)
  , m_textDocument(new QTextDocument(this))
  , m_settings(new SettingsAdaptor(this))
{
}

QString ConfigEditor::fileName() const
{
  return m_fileName;
}

QTextDocument *ConfigEditor::textDocument() const
{
  return m_textDocument;
}

QUrl ConfigEditor::editorQml() const
{
  return m_editorQml;
}

QObject *ConfigEditor::settings() const
{
  return m_settings;
}

void ConfigEditor::openFile(const QString &fileName)
{
  const QFileInfo fileInfo(fileName);
  if (!fileInfo.exists() || !fileInfo.isReadable()) {
    qWarning() << Q_FUNC_INFO << fileName << "does not exists or is unreadable";
    return;
  }

  setFileName(fileInfo.absoluteFilePath());

  const QUrl customEditorQml = findCustomEditorQml(fileInfo);
  if (customEditorQml.isValid()) {
    loadAsSettings(customEditorQml);
  }
  loadAsText();
}

void ConfigEditor::saveText()
{
  QFile file(m_fileName);
  if (!file.open(QIODevice::WriteOnly)) {
    qWarning() << "Failed to open" << m_fileName << "for writing";
    return;
  }

  QTextStream stream(&file);
  stream << m_textDocument->toPlainText();
}

void ConfigEditor::saveSettings()
{
  // if the custom editor has indicated that it updates value when saving
  // request that it does that
  // otherwise assume it has changed values already and save directly
  if (m_settings->updatesOnSave()) {
    emit requestUpdateOnSave();
  } else {
    m_settings->save();
  }
}

void ConfigEditor::updateOnSaveDone()
{
  m_settings->save();
}

void ConfigEditor::setFileName(const QString &fileName)
{
  if (fileName == m_fileName)
    return;

  m_fileName = fileName;
  emit fileNameChanged();
}

void ConfigEditor::setEditorQml(const QUrl &qmlUrl)
{
  if (qmlUrl == m_editorQml)
    return;

  m_editorQml = qmlUrl;
  emit editorQmlChanged();
}

void ConfigEditor::loadAsText()
{
  QFile file(m_fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Failed to open" << m_fileName << "for reading";
    m_textDocument->clear();
    return;
  }

  QTextStream stream(&file);
  m_textDocument->setPlainText(stream.readAll());
}

void ConfigEditor::loadAsSettings(const QUrl &customEditorQml)
{
  m_settings->load(m_fileName);
  m_settings->setUpdatesOnSave(false);

  setEditorQml(customEditorQml);
}

QUrl ConfigEditor::findCustomEditorQml(const QFileInfo &configFile) const
{
  // first check in the location of the config itself
  const QString baseName = configFile.baseName();
  const QString qmlFile = QString("%1-editor.qml").arg(baseName);

  QFileInfo qmlFileInfo(configFile.dir(), qmlFile);
  if (qmlFileInfo.exists()) {
    return QUrl::fromLocalFile(qmlFileInfo.absoluteFilePath());
  }

  // otherwise look into our data storage location
#if defined(QT5_PORT)
  const QString dataDirLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
  qDebug() << "dataDirLocation" << dataDirLocation;
  if (!dataDirLocation.isEmpty()) {
    qmlFileInfo = QFileInfo(QDir(dataDirLocation + "config-editor"), qmlFile);
    if (qmlFileInfo.exists()) {
      return QUrl::fromLocalFile(qmlFileInfo.absoluteFilePath());
    }
  }
#else
#warning NOT PORTED YET
#endif

  // finally check our resources
  qmlFileInfo = QFileInfo(QDir(":/editors"), qmlFile);
  if (qmlFileInfo.exists()) {
    return QUrl(QString("qrc:///editors/%1").arg(qmlFile));
  }

  return QUrl();
}
