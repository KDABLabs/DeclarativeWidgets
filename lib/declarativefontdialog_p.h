/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEFONTDIALOG_P_H
#define DECLARATIVEFONTDIALOG_P_H

#include "declarativewidgets_export.h"
#include "staticdialogmethodattached_p.h"

#include <QFontDialog>
#include <qqml.h>

class DECLARATIVEWIDGETS_EXPORT DeclarativeFontDialogAttached : public StaticDialogMethodAttached
{
  Q_OBJECT
  Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(bool ok READ dialogAccepted NOTIFY dialogAcceptedChanged)
  Q_PROPERTY(int options READ options WRITE setOptions NOTIFY optionsChanged)

  public:
    explicit DeclarativeFontDialogAttached(QObject *parent = 0);
    ~DeclarativeFontDialogAttached();

    void setTitle(const QString &title);
    QString title() const;

    bool dialogAccepted() const;

    void setOptions(int options);
    int options() const;

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

class DECLARATIVEWIDGETS_EXPORT DeclarativeFontDialog : public QFontDialog
{
  Q_OBJECT

  public:
    explicit DeclarativeFontDialog(QWidget *parent = 0);

    static DeclarativeFontDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeFontDialog, QML_HAS_ATTACHED_PROPERTIES)

#endif
