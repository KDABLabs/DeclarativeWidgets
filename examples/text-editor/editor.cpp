#include "editor.h"

#include <QTextDocument>

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

void Editor::newDocument()
{
  m_document->clear();
  m_document->setModified(false);
}
