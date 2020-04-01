/*
  declarativeformlayout.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativeformlayout_p.h"

#include "declarativespaceritem_p.h"
#include "layoutcontainerinterface_p.h"

#include <QLabel>
#include <QPointer>
#include <QQmlInfo>

class DeclarativeFormLayoutAttached::Private
{
  public:
    Private(QWidget *w, QLayout *l)
      : widget(w), layout(l)
    {}

    QString label;

    QPointer<QWidget> widget;
    QPointer<QLayout> layout;
    QPointer<QFormLayout> parentLayout;
};

DeclarativeFormLayoutAttached::DeclarativeFormLayoutAttached(QWidget *parent)
  : QObject(parent), d(new Private(parent, 0))
{
}

DeclarativeFormLayoutAttached::DeclarativeFormLayoutAttached(QLayout *parent)
  : QObject(parent), d(new Private(0, parent))
{
}

DeclarativeFormLayoutAttached::~DeclarativeFormLayoutAttached()
{
  delete d;
}

void DeclarativeFormLayoutAttached::setParentLayout(QFormLayout *parentLayout)
{
  d->parentLayout = parentLayout;
}

void DeclarativeFormLayoutAttached::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;
  emit labelChanged(label);

  if (d->parentLayout) {
    QWidget *labelWidget = 0;
    int row = -1;

    if (d->widget) {
      labelWidget = d->parentLayout->labelForField(d->widget);

      if (!labelWidget) {
        QFormLayout::ItemRole role;
        d->parentLayout->getWidgetPosition(d->widget, &row, &role);
       }
    } else if (d->layout) {
      labelWidget = d->parentLayout->labelForField(d->layout);

      if (!labelWidget) {
        QFormLayout::ItemRole role;
        d->parentLayout->getLayoutPosition(d->layout, &row, &role);
       }
    }

    QLabel *rowLabel = 0;
    if (labelWidget) {
      rowLabel = qobject_cast<QLabel*>(labelWidget);
    } else if (row != -1) {
      rowLabel = new QLabel(d->parentLayout->parentWidget());
      d->parentLayout->setWidget(row, QFormLayout::LabelRole, rowLabel);
    }

    if (rowLabel) {
      rowLabel->setText(label);
    }
  }
}

QString DeclarativeFormLayoutAttached::label() const
{
  return d->label;
}

// DeclarativeFormLayout
DeclarativeFormLayout::DeclarativeFormLayout(QObject *parent) : QFormLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeFormLayoutAttached *DeclarativeFormLayout::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeFormLayoutAttached(widget);

  QLayout *layout = qobject_cast<QLayout*>(parent);
  if (layout)
    return new DeclarativeFormLayoutAttached(layout);

  qmlInfo(parent) << "Can only attach FormLayout to widgets and layouts";
  return 0;
}

class FormLayoutContainer : public LayoutContainerInterface
{
  public:
    explicit FormLayoutContainer(QFormLayout *layout)
      : m_layout(layout)
    {
      Q_ASSERT(m_layout);
    }

    void addSpacer(DeclarativeSpacerItem *spacerItem);
    void addLayout(QLayout *layout);
    void addWidget(QWidget *widget);
    void setContentsMargins(int left, int top, int right, int bottom);
    void getContentsMargins(int &left, int &top, int &right, int &bottom);

  private:
    QFormLayout *m_layout;
};

DeclarativeFormLayoutExtension::DeclarativeFormLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(new FormLayoutContainer(qobject_cast<QFormLayout*>(parent)), parent)
{
}

void FormLayoutContainer::addLayout(QLayout *layout)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(layout, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    properties->setParentLayout(m_layout);

    if (!properties->label().isEmpty()) {
      m_layout->addRow(properties->label(), layout);
      return;
    }
  }
  m_layout->addRow(layout);
}

void FormLayoutContainer::addSpacer(DeclarativeSpacerItem *spacerItem)
{
    qWarning() << Q_FUNC_INFO << "Using QFormLayout::addItem for spacer item";
    m_layout->addItem(spacerItem->spacer());
}

void FormLayoutContainer::addWidget(QWidget *widget)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(widget, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    properties->setParentLayout(m_layout);

    if (!properties->label().isEmpty()) {
      m_layout->addRow(properties->label(), widget);
      return;
    }
  }

  m_layout->addRow(widget);
}

void FormLayoutContainer::setContentsMargins(int left, int top, int right, int bottom)
{
  m_layout->setContentsMargins(left, top, right, bottom);
}

void FormLayoutContainer::getContentsMargins(int &left, int &top, int &right, int &bottom)
{
  m_layout->getContentsMargins(&left, &top, &right, &bottom);
}
