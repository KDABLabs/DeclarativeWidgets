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

