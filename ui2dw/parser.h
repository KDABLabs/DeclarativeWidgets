/*
  parser.h

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

#ifndef PARSER_H
#define PARSER_H

#include <QSet>
#include <QSharedPointer>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QIODevice;
class QXmlStreamReader;
QT_END_NAMESPACE

class UiNode;
class UiTopNode;

class Parser
{
  public:
    explicit Parser(QIODevice *inputDevice);
    ~Parser();

    QSharedPointer<UiTopNode> parse();

    QString errorString() const;

    QXmlStreamReader *reader() const;

    bool readUntilElement(const QString &parent, const QString &element);

  protected:
    QScopedPointer<QXmlStreamReader> m_reader;
    const QSet<QString> m_ignoredElementNames;
    const QSet<QString> m_skippedElementNames;
};

#endif // PARSER_H
