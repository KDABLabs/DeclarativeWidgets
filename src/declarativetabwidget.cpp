/*
  declarativetabwidget.cpp

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

#include "declarativetabwidget_p.h"

#include <QPointer>
#include <QQmlInfo>

class DeclarativeTabWidgetAttached::Private
{
  public:
    QString label;
    QIcon icon;
    QPointer<QTabWidget> tabWidget;
    int index;
};

DeclarativeTabWidgetAttached::DeclarativeTabWidgetAttached(QObject *parent)
  : QObject(parent), d(new DeclarativeTabWidgetAttached::Private)
{
}

DeclarativeTabWidgetAttached::~DeclarativeTabWidgetAttached()
{
  delete d;
}

void DeclarativeTabWidgetAttached::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;

  if (d->tabWidget)
    d->tabWidget->setTabText(d->index, d->label);

  emit labelChanged(label);
}

QString DeclarativeTabWidgetAttached::label() const
{
  return d->label;
}

void DeclarativeTabWidgetAttached::setIcon(const QIcon &icon)
{
  d->icon = icon;

  if (d->tabWidget)
    d->tabWidget->setTabIcon(d->index, d->icon);

  emit iconChanged(icon);
}

QIcon DeclarativeTabWidgetAttached::icon() const
{
  return d->icon;
}

void DeclarativeTabWidgetAttached::setAssociation(QTabWidget *widget, int index)
{
  d->tabWidget = widget;
  d->index = index;
}

DeclarativeTabWidget::DeclarativeTabWidget(QObject *parent)
  : QTabWidget(qobject_cast<QWidget*>(parent))
{
}

DeclarativeTabWidgetAttached *DeclarativeTabWidget::qmlAttachedProperties(QObject *object)
{
  return new DeclarativeTabWidgetAttached(object);
}

TabWidgetWidgetContainer::TabWidgetWidgetContainer(QObject *parent)
  : DefaultWidgetContainer(qobject_cast<QTabWidget*>(parent))
{
  Q_ASSERT(m_widget);
}

void TabWidgetWidgetContainer::addWidget(QWidget *widget)
{
  QTabWidget *tabWidget = extendedTabWidget();

  // TODO: error when layout is set

  QString label;
  QIcon icon;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeTabWidget>(widget, false);
  DeclarativeTabWidgetAttached *tabHeader = qobject_cast<DeclarativeTabWidgetAttached*>(attachedProperties);
  if (tabHeader) {
    label = tabHeader->label();
    icon = tabHeader->icon();
  }

  const int index = tabWidget->addTab(widget, icon, label);
  if (tabHeader)
    tabHeader->setAssociation(tabWidget, index);
}

void TabWidgetWidgetContainer::setLayout(QLayout *layout)
{
  Q_UNUSED(layout);
  qmlInfo(m_widget) << "Can not add QLayout to QTabWidget";
}

QTabWidget *TabWidgetWidgetContainer::extendedTabWidget() const
{
  return static_cast<QTabWidget*>(m_widget);
}
