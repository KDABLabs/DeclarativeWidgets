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

#include "declarativelayoutextension.h"

#include "declarativespaceritem_p.h"
#include "defaultobjectcontainer_p.h"
#include "layoutcontainerinterface_p.h"

#include <QLayout>
#include <QWidget>

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

DeclarativeLayoutExtension::DeclarativeLayoutExtension(LayoutContainerInterface *layoutContainer, QObject *parent)
  : DeclarativeObjectExtension(new LayoutContainerDelegate(layoutContainer), parent)
{
  parent->setParent(0); // otherwise first call to parentWidget() will complain about wrong parent class
}
