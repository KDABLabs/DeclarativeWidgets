/*
  editor.h

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

#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class Editor : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QTextDocument* document READ document CONSTANT)
  Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

  Q_PROPERTY(bool undoAvailable READ undoAvailable NOTIFY undoAvailableChanged)
  Q_PROPERTY(bool redoAvailable READ redoAvailable NOTIFY redoAvailableChanged)

  public:
    explicit Editor(QObject *parent = 0);
    ~Editor();

    QTextDocument *document() const;
    bool undoAvailable() const;
    bool redoAvailable() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

  Q_SIGNALS:
    void fileNameChanged(const QString &fileName);
    void requestSaveFileName();
    void undoAvailableChanged();
    void redoAvailableChanged();

    void information(const QString &message);
    void critical(const QString &message);

  public Q_SLOTS:
    void newDocument();
    void open(const QString &fileName);
    void save();

  private Q_SLOTS:
    void undoAvailable(bool);
    void redoAvailable(bool);

  private:
    QTextDocument *m_document;
    QString m_fileName;
    bool m_undoAvailable;
    bool m_redoAvailable;
};

#endif // EDITOR_H
