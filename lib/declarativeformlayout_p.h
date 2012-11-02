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

#ifndef DECLARATIVEFORMLAYOUT_P_H
#define DECLARATIVEFORMLAYOUT_P_H

#include "declarativelayoutproxy_p.h"

#include <QFormLayout>

class DeclarativeFormLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

  public:
    DeclarativeFormLayoutAttached(QObject *parent);
    ~DeclarativeFormLayoutAttached();

    void setLabel(const QString &label);
    QString label() const;

  Q_SIGNALS:
    void labelChanged(const QString &label);

  private:
    class Private;
    Private *const d;
};

class DeclarativeFormLayout : public DeclarativeLayoutProxy<QFormLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeFormLayout(QObject *parent = 0);

    static DeclarativeFormLayoutAttached *qmlAttachedProperties(QObject *parent);

  protected:
    void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeFormLayout, QML_HAS_ATTACHED_PROPERTIES)

#endif
