/*
  declarativemessagebox_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEMESSAGEBOX_P_H
#define DECLARATIVEMESSAGEBOX_P_H

#include <QtGlobal>
#include "staticdialogmethodattached_p.h"

#include <QMessageBox>
#include <qqml.h>

class DeclarativeMessageBoxAttached : public StaticDialogMethodAttached
{
  Q_OBJECT
  Q_PROPERTY(int buttons READ buttons WRITE setButtons NOTIFY buttonsChanged)
  Q_PROPERTY(int defaultButton READ defaultButton WRITE setDefaultButton NOTIFY defaultButtonChanged)

  public:
    explicit DeclarativeMessageBoxAttached(QObject *parent = 0);
    ~DeclarativeMessageBoxAttached();

    void setButtons(int buttons);
    int buttons() const;

    void setDefaultButton(int defaultButton);
    int defaultButton() const;

    Q_INVOKABLE void about(const QString &title, const QString &text);
    Q_INVOKABLE void aboutQt();
    Q_INVOKABLE void aboutQt(const QString &title);
    Q_INVOKABLE int critical(const QString &title, const QString &text);
    Q_INVOKABLE int information(const QString &title, const QString &text);
    Q_INVOKABLE int question(const QString &title, const QString &text);
    Q_INVOKABLE int warning(const QString &title, const QString &text);

  Q_SIGNALS:
    void buttonsChanged(int buttons);
    void defaultButtonChanged(int defaultButton);

  private:
    class Private;
    Private *const d;
};

class DeclarativeMessageBox : public QMessageBox
{
  Q_OBJECT

  public:
    explicit DeclarativeMessageBox(QWidget *parent = 0);

    static DeclarativeMessageBoxAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeMessageBox, QML_HAS_ATTACHED_PROPERTIES)

#endif
