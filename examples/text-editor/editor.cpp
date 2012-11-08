#include "editor.h"

#include <QFile>
#include <QTextDocument>
#include <QTextStream>

Editor::Editor(QObject *parent)
  : QObject(parent)
  , m_document(new QTextDocument)
{
}

Editor::~Editor()
{
  delete m_document;
}

QTextDocument *Editor::document() const
{
  return m_document;
}

void Editor::setFileName(const QString &fileName)
{
  if (fileName == m_fileName)
    return;

  m_fileName = fileName;
  emit fileNameChanged(fileName);
}

QString Editor::fileName() const
{
  return m_fileName;
}

QIcon Editor::iconFromFile(const QString &fileName) const
{
  return QIcon(fileName);
}

QIcon Editor::iconFromTheme(const QString &iconName) const
{
  return QIcon::fromTheme(iconName);
}

void Editor::newDocument()
{
  m_fileName = QString();
  m_document->clear();
  m_document->setModified(false);
}

void Editor::open(const QString &fileName)
{
  if (fileName.isEmpty())
    return;

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    emit critical(tr("File %1 can not be read").arg(fileName));
    return;
  }

  QTextStream stream(&file);
  m_document->setPlainText(stream.readAll());
  m_document->setModified(false);

  setFileName(fileName);
}

void Editor::save()
{
  if (m_fileName.isEmpty()) {
    emit requestSaveFileName();
    return;
  }

  QFile file(m_fileName);
  if (!file.open(QIODevice::WriteOnly)) {
    emit requestSaveFileName();
    return;
  }

  QTextStream stream(&file);
  stream << m_document->toPlainText();
  file.close();

  m_document->setModified(false);
  emit information(tr("File %1 successfully saved").arg(m_fileName));
}
