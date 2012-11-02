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

#ifndef DECLARATIVEWIDGETSDOCUMENT_H
#define DECLARATIVEWIDGETSDOCUMENT_H

#include <QObject>
#include <QUrl>

class QDeclarativeEngine;

class DeclarativeWidgetsDocument : public QObject
{
  Q_OBJECT

  public:
    DeclarativeWidgetsDocument(const QUrl &url, QObject *parent = 0);
    ~DeclarativeWidgetsDocument();

    void setContextProperty(const QString &name, const QVariant &value);
    void setContextProperty(const QString &name, QObject *object);

    QDeclarativeEngine* engine() const;

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
