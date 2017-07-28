/*
  Copyright (C) 2012-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEBOXLAYOUT_P_H
#define DECLARATIVEBOXLAYOUT_P_H

#include "declarativewidgets_export.h"

#include <QBoxLayout>

class DeclarativeSpacerItem;

class DECLARATIVEWIDGETS_EXPORT DeclarativeBoxLayoutAttached : public QObject
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
