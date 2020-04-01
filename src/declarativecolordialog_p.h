/*
  declarativecolordialog_p.h

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

#ifndef DECLARATIVECOLORDIALOG_P_H
#define DECLARATIVECOLORDIALOG_P_H

#include <QtGlobal>
#include "staticdialogmethodattached_p.h"

#include <QColorDialog>
#include <qqml.h>

class DeclarativeColorDialogAttached : public StaticDialogMethodAttached
{
  Q_OBJECT
  Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(unsigned int options READ options WRITE setOptions NOTIFY optionsChanged)

  public:
    explicit DeclarativeColorDialogAttached(QObject *parent = 0);
    ~DeclarativeColorDialogAttached();

    void setTitle(const QString &title);
    QString title() const;

    void setOptions(unsigned int options);
    unsigned int options() const;

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
    explicit DeclarativeColorDialog(QWidget *parent = 0);

    static DeclarativeColorDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeColorDialog, QML_HAS_ATTACHED_PROPERTIES)

#endif
