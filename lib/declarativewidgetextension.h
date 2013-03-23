/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEWIDGETEXTENSION_H
#define DECLARATIVEWIDGETEXTENSION_H

#include "declarativeobjectextension.h"

#include <QRect>

class WidgetContainerInterface;

class QAction;
class QLayout;
class QWidget;

class DeclarativeWidgetExtension : public DeclarativeObjectExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_PROPERTY(int x READ x WRITE setX NOTIFY posChanged)
  Q_PROPERTY(int y READ y WRITE setY NOTIFY posChanged)
  Q_PROPERTY(int width READ width WRITE setWidth NOTIFY sizeChanged)
  Q_PROPERTY(int height READ height WRITE setHeight NOTIFY sizeChanged)
  Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeWidgetExtension(QObject *parent = 0);

    QWidget *extendedWidget() const;

    int x() const;
    void setX(int value);

    int y() const;
    void setY(int value);

    int width() const;
    void setWidth(int value);

    int height() const;
    void setHeight(int value);

    QRect geometry() const;
    void setGeometry(const QRect &rect);

    bool eventFilter(QObject *watched, QEvent *event);

  protected:
    explicit DeclarativeWidgetExtension(WidgetContainerInterface *widgetContainer, QObject *parent = 0);

  Q_SIGNALS:
    void posChanged();
    void sizeChanged();
    void geometryChanged();
};

#endif // DECLARATIVEWIDGETEXTENSION_H
