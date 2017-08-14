/*
  declarativewidgetsdocument.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEWIDGETSDOCUMENT_H
#define DECLARATIVEWIDGETSDOCUMENT_H

#include "declarativewidgets_export.h"

#include <QObject>
#include <QUrl>

class QQmlEngine;

class DECLARATIVEWIDGETS_EXPORT DeclarativeWidgetsDocument : public QObject
{
  Q_OBJECT

  public:
    explicit DeclarativeWidgetsDocument(const QUrl &url, QObject *parent = 0);
    ~DeclarativeWidgetsDocument();

    void setContextProperty(const QString &name, const QVariant &value);
    void setContextProperty(const QString &name, QObject *object);

    QQmlEngine* engine() const;

    template <typename T>
    T* create()
    {
      QWidget *widget = createWidget();
      if (!widget)
        return 0;

      return qobject_cast<T*>(widget);
    }

  private:
    QWidget* createWidget();

    class Private;
    Private* const d;
};

#endif
