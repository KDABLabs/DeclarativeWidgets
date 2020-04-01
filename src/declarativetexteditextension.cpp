/*
  declarativetexteditextension.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativetexteditextension_p.h"

#include <QTextEdit>

DeclarativeTextEditExtension::DeclarativeTextEditExtension(QObject *parent)
  : DeclarativeWidgetExtension(parent)
{
  connect(textEdit()->document(), SIGNAL(modificationChanged(bool)), this, SIGNAL(modifiedChanged()));
}

void DeclarativeTextEditExtension::setDocument(QTextDocument *document)
{
  if (document == 0)
    return;

  if (textEdit()->document() == document)
    return;

  if (textEdit()->document()) {
    disconnect(textEdit()->document(), SIGNAL(modificationChanged(bool)), this, SIGNAL(modifiedChanged()));
  }

  const bool oldModified = modified();

  textEdit()->setDocument(document);
  connect(document, SIGNAL(modificationChanged(bool)), this, SIGNAL(modifiedChanged()));

  emit documentChanged();

  if (oldModified != modified())
    emit modifiedChanged();
}

QTextDocument *DeclarativeTextEditExtension::document() const
{
  return textEdit()->document();
}

bool DeclarativeTextEditExtension::modified() const
{
  return textEdit()->document()->isModified();
}

QTextEdit *DeclarativeTextEditExtension::textEdit() const
{
  QTextEdit *textEdit = qobject_cast<QTextEdit*>(extendedWidget());
  Q_ASSERT(textEdit);

  return textEdit;
}
