/*
  declarativelayoutextension.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2013-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVELAYOUTEXTENSION_H
#define DECLARATIVELAYOUTEXTENSION_H

#include "declarativeobjectextension.h"

class LayoutContainerInterface;

QT_BEGIN_NAMESPACE
class QLayout;
class QWidget;
QT_END_NAMESPACE

class DeclarativeLayoutContentsMargins : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int left READ leftMargin WRITE setLeftMargin NOTIFY marginsChanged)
  Q_PROPERTY(int top READ topMargin WRITE setTopMargin NOTIFY marginsChanged)
  Q_PROPERTY(int right READ rightMargin WRITE setRightMargin NOTIFY marginsChanged)
  Q_PROPERTY(int bottom READ bottomMargin WRITE setBottomMargin NOTIFY marginsChanged)

  public:
    explicit DeclarativeLayoutContentsMargins(LayoutContainerInterface *layoutContainer, QObject *parent = 0);

    void setLeftMargin(int margin);
    int leftMargin() const;

    void setTopMargin(int margin);
    int topMargin() const;

    void setRightMargin(int margin);
    int rightMargin() const;

    void setBottomMargin(int margin);
    int bottomMargin() const;

  Q_SIGNALS:
    void marginsChanged();

  private:
    LayoutContainerInterface *m_layoutContainer;

  private:
    void changeMargins(int left, int top, int right, int bottom);
};

class DeclarativeLayoutExtension : public DeclarativeObjectExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QQmlListProperty<QObject> data READ data DESIGNABLE false CONSTANT)
  Q_PROPERTY(DeclarativeLayoutContentsMargins* contentsMargins READ contentsMargins CONSTANT)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    QLayout *extendedLayout() const;
    DeclarativeLayoutContentsMargins *contentsMargins() const;

  protected:
    explicit DeclarativeLayoutExtension(LayoutContainerInterface *layoutContainer, QObject *parent = 0);

  private:
    DeclarativeLayoutContentsMargins *m_contentsMargins;
};

#endif // DECLARATIVELAYOUTEXTENSION_H
