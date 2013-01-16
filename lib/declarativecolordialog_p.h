/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

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

#ifndef DECLARATIVECOLORDIALOG_P_H
#define DECLARATIVECOLORDIALOG_P_H

#include "staticdialogmethodattached_p.h"

#include <qdeclarative.h>
#include <QColorDialog>

class DeclarativeColorDialogAttached : public StaticDialogMethodAttached
{
  Q_OBJECT
  Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(int options READ options WRITE setOptions NOTIFY optionsChanged)

  public:
    explicit DeclarativeColorDialogAttached(QObject *parent = 0);
    ~DeclarativeColorDialogAttached();

    void setTitle(const QString &title);
    QString title() const;

    void setOptions(int options);
    int options() const;

    Q_INVOKABLE QColor getColor();
    Q_INVOKABLE QColor getColor(const QColor &initialColor);

  Q_SIGNALS:
    void titleChanged(const QString &title);
    void optionsChanged(int options);

  private:
    class Private;
    Private *const d;
};

class DeclarativeColorDialog : public QColorDialog
{
  Q_OBJECT

  public:
    DeclarativeColorDialog(QWidget *parent = 0);

    static DeclarativeColorDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeColorDialog, QML_HAS_ATTACHED_PROPERTIES)

#endif
