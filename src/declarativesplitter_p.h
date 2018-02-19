/*
  declarativesplitter_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Lova Widmark <znurree@gmail.com>

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

#ifndef DECLARATIVESPLITTER_P_H
#define DECLARATIVESPLITTER_P_H

#include <QtGlobal>
#include <QObject>
#include <QSplitter>
#include <QtQml>

class DeclarativeSplitterAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int stretch READ stretch WRITE setStretch NOTIFY stretchChanged)

  public:
    DeclarativeSplitterAttached(QWidget *widget, QObject *parent);
    ~DeclarativeSplitterAttached();

    void setStretch(int stretch);
    int stretch() const;

  Q_SIGNALS:
    void stretchChanged(int stretch);

  private:
    class Private;
    Private *const d;
};

class DeclarativeSplitter : public QSplitter
{
  public:
    DeclarativeSplitter(QWidget *parent = Q_NULLPTR);

    static DeclarativeSplitterAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeSplitter, QML_HAS_ATTACHED_PROPERTIES)

#endif // DECLARATIVESPLITTER_P_H