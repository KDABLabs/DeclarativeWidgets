/*
  declarativelayoutextension.cpp

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

#include "declarativelayoutextension.h"

#include "declarativespaceritem_p.h"
#include "defaultobjectcontainer_p.h"
#include "layoutcontainerinterface_p.h"

#include <QLayout>
#include <QWidget>

#define GET_CONTENTS_MARGINS \
  int left = 0; \
  int top = 0; \
  int right = 0; \
  int bottom = 0; \
  m_layoutContainer->getContentsMargins(left, top, right, bottom)

DeclarativeLayoutContentsMargins::DeclarativeLayoutContentsMargins(LayoutContainerInterface *layoutContainer, QObject *parent)
  : QObject(parent)
  , m_layoutContainer(layoutContainer)
{
}

void DeclarativeLayoutContentsMargins::setLeftMargin(int margin)
{
  GET_CONTENTS_MARGINS;

  changeMargins(margin, top, right, bottom);
}

int DeclarativeLayoutContentsMargins::leftMargin() const
{
  GET_CONTENTS_MARGINS;

  return left;
}

void DeclarativeLayoutContentsMargins::setTopMargin(int margin)
{
  GET_CONTENTS_MARGINS;

  changeMargins(left, margin, right, bottom);
}

int DeclarativeLayoutContentsMargins::topMargin() const
{
  GET_CONTENTS_MARGINS;

  return top;
}

void DeclarativeLayoutContentsMargins::setRightMargin(int margin)
{
  GET_CONTENTS_MARGINS;

  changeMargins(left, top, margin, bottom);
}

int DeclarativeLayoutContentsMargins::rightMargin() const
{
  GET_CONTENTS_MARGINS;

  return right;
}

void DeclarativeLayoutContentsMargins::setBottomMargin(int margin)
{
  GET_CONTENTS_MARGINS;

  changeMargins(left, top, right, margin);
}

int DeclarativeLayoutContentsMargins::bottomMargin() const
{
  GET_CONTENTS_MARGINS;

  return bottom;
}

void DeclarativeLayoutContentsMargins::changeMargins(int left, int top, int right, int bottom)
{
  int oldLeft = 0;
  int oldTop = 0;
  int oldRight = 0;
  int oldBottom = 0;

  m_layoutContainer->getContentsMargins(oldLeft, oldTop, oldRight, oldBottom);

  const bool changed = (oldLeft != left) || (oldTop != top) || (oldRight != right) || (oldBottom != bottom);

  m_layoutContainer->setContentsMargins(left, top, right, bottom);

  if (changed) {
    emit marginsChanged();
  }
}


class LayoutContainerDelegate : public DefaultObjectContainer
{
  public:
    explicit LayoutContainerDelegate(LayoutContainerInterface *layoutContainer)
      : m_layoutContainer(layoutContainer)
    {
    }

    ~LayoutContainerDelegate()
    {
      delete m_layoutContainer;
    }

    void dataAppend(QObject *object)
    {
      DefaultObjectContainer::dataAppend(object);
      QWidget *widget = qobject_cast<QWidget*>(object);
      if (widget) {
        m_layoutContainer->addWidget(widget);
        return;
      }

      QLayout *layout = qobject_cast<QLayout*>(object);
      if (layout) {
        m_layoutContainer->addLayout(layout);
        return;
      }

      DeclarativeSpacerItem *spacer = qobject_cast<DeclarativeSpacerItem*>(object);
      if (spacer) {
          m_layoutContainer->addSpacer(spacer);
          return;
      }
    }

  private:
    LayoutContainerInterface *m_layoutContainer;
};

QLayout *DeclarativeLayoutExtension::extendedLayout() const
{
  QLayout *parentLayout = qobject_cast<QLayout*>(parent());
  Q_ASSERT(parentLayout);
  Q_UNUSED(parentLayout);

  return parentLayout;
}

DeclarativeLayoutContentsMargins *DeclarativeLayoutExtension::contentsMargins() const
{
  return m_contentsMargins;
}

DeclarativeLayoutExtension::DeclarativeLayoutExtension(LayoutContainerInterface *layoutContainer, QObject *parent)
  : DeclarativeObjectExtension(new LayoutContainerDelegate(layoutContainer), parent)
  , m_contentsMargins(new DeclarativeLayoutContentsMargins(layoutContainer, this))
{
  parent->setParent(0); // otherwise first call to parentWidget() will complain about wrong parent class
}
