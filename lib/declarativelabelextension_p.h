/*
  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVELABELEXTENSION_P_H
#define DECLARATIVELABELEXTENSION_P_H

#include "declarativewidgets_export.h"
#include "declarativewidgetextension.h"

class DECLARATIVEWIDGETS_EXPORT DeclarativeLabelExtension : public DeclarativeWidgetExtension
{
  Q_OBJECT
  Q_PROPERTY(QWidget* buddy READ buddy WRITE setBuddy NOTIFY buddyChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeLabelExtension(QObject *parent = 0);

    void setBuddy(QWidget *buddy);
    QWidget* buddy() const;

  Q_SIGNALS:
    void buddyChanged();

  private:
    QWidget* m_buddy;

  private Q_SLOTS:
    void buddyDestroyed();
};

#endif // DECLARATIVELABELEXTENSION_P_H
