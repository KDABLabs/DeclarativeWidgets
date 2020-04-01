/*
  configeditor.h

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

#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

#include <QTextDocument>
#include <QUrl>

class SettingsAdaptor;

QT_BEGIN_NAMESPACE
class QFileInfo;
QT_END_NAMESPACE

class ConfigEditor : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
  Q_PROPERTY(QTextDocument* textDocument READ textDocument CONSTANT)
  Q_PROPERTY(QUrl editorQml READ editorQml NOTIFY editorQmlChanged)
  Q_PROPERTY(QObject* settings READ settings CONSTANT)

  public:
    explicit ConfigEditor(QObject *parent = 0);

    QString fileName() const;

    QTextDocument *textDocument() const;

    QUrl editorQml() const;

    QObject *settings() const;

  public Q_SLOTS:
    void openFile(const QString &fileName);
    void saveText();
    void saveSettings();
    void updateOnSaveDone();

  Q_SIGNALS:
    void fileNameChanged();
    void editorQmlChanged();
    void requestUpdateOnSave();

  private:
    QString m_fileName;
    QUrl m_editorQml;
    QTextDocument *m_textDocument;
    SettingsAdaptor *m_settings;

  private:
    void setFileName(const QString &fileName);
    void setEditorQml(const QUrl &qmlUrl);
    void loadAsText();
    void loadAsSettings(const QUrl &customEditorQml);
    QUrl findCustomEditorQml(const QFileInfo &configFile) const;
};

#endif // EDITOR_H
