/*
  declarativeboxlayout_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEBOXLAYOUT_P_H
#define DECLARATIVEBOXLAYOUT_P_H

#include <QtGlobal>

#include <QBoxLayout>

class DeclarativeSpacerItem;

class DeclarativeBoxLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int stretch READ stretch WRITE setStretch NOTIFY stretchChanged)
  Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

  public:
    DeclarativeBoxLayoutAttached(QWidget *widget, QObject *parent);
    DeclarativeBoxLayoutAttached(QLayout *layout, QObject *parent);
    DeclarativeBoxLayoutAttached(DeclarativeSpacerItem *spacerItem, QObject *parent);
    ~DeclarativeBoxLayoutAttached();

    void setParentLayout(QBoxLayout *parentLayout);

    void setStretch(int stretch);
    int stretch() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

  Q_SIGNALS:
    void stretchChanged(int stretch);
    void alignmentChanged(Qt::Alignment alignment);

  private:
    class Private;
    Private *const d;
};

#endif
