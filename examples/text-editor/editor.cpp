/*
  editor.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "editor.h"

#include <QFile>
#include <QTextDocument>
#include <QTextStream>

Editor::Editor(QObject *parent)
  : QObject(parent)
  , m_document(new QTextDocument)
  , m_undoAvailable(false)
  , m_redoAvailable(false)
{
  connect(m_document, SIGNAL(undoAvailable(bool)), SLOT(undoAvailable(bool)));
  connect(m_document, SIGNAL(redoAvailable(bool)), SLOT(redoAvailable(bool)));
}

Editor::~Editor()
{
  delete m_document;
}

QTextDocument *Editor::document() const
{
  return m_document;
}

bool Editor::undoAvailable() const
{
  return m_undoAvailable;
}

bool Editor::redoAvailable() const
{
  return m_redoAvailable;
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

void Editor::undoAvailable(bool available)
{
  if (m_undoAvailable == available)
    return;

  m_undoAvailable = available;
  emit undoAvailableChanged();
}

void Editor::redoAvailable(bool available)
{
  if (m_redoAvailable == available)
    return;

  m_redoAvailable = available;
  emit redoAvailableChanged();
}
