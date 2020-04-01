/*
  declarativefontdialog_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Tobias Koenig <tobias.koenig@kdab.com>
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

#ifndef DECLARATIVEFONTDIALOG_P_H
#define DECLARATIVEFONTDIALOG_P_H

#include <QtGlobal>
#include "staticdialogmethodattached_p.h"

#include <QFontDialog>
#include <qqml.h>

class DeclarativeFontDialogAttached : public StaticDialogMethodAttached
{
  Q_OBJECT
  Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(bool ok READ dialogAccepted NOTIFY dialogAcceptedChanged)
  Q_PROPERTY(unsigned int options READ options WRITE setOptions NOTIFY optionsChanged)

  public:
    explicit DeclarativeFontDialogAttached(QObject *parent = 0);
    ~DeclarativeFontDialogAttached();

    void setTitle(const QString &title);
    QString title() const;

    bool dialogAccepted() const;

    void setOptions(unsigned int options);
    unsigned int options() const;

    Q_INVOKABLE QFont getFont();
    Q_INVOKABLE QFont getFont(const QString &fontFamily);

  Q_SIGNALS:
    void titleChanged(const QString &title);
    void dialogAcceptedChanged(bool accepted);
    void optionsChanged(int options);

  private:
    void setDialogAccepted(bool accepted);

    class Private;
    Private *const d;
};

class DeclarativeFontDialog : public QFontDialog
{
  Q_OBJECT

  public:
    explicit DeclarativeFontDialog(QWidget *parent = 0);

    static DeclarativeFontDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeFontDialog, QML_HAS_ATTACHED_PROPERTIES)

#endif
