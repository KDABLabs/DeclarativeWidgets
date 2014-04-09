/*
  Copyright (C) 2013-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com
  Author: Tobias Koenig, tobias.koenig@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef PARSER_H
#define PARSER_H

#include <QSet>
#include <QSharedPointer>
#include <QScopedPointer>

class QIODevice;
class QXmlStreamReader;

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
