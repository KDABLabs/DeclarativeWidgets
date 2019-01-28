/*
  declarativeloaderwidget.cpp

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

#include "declarativeloaderwidget_p.h"

#include "abstractdeclarativeobject_p.h"

#include <QDebug>
#include <QQmlComponent>
#include <QVBoxLayout>

class DeclarativeLoaderWidget::Private
{
  public:
    Private()
      : component(0)
    {}

  public:
    QUrl source;
    QQmlComponent *component;
};

DeclarativeLoaderWidget::DeclarativeLoaderWidget(QWidget *parent)
  : QWidget(parent)
  , d(new Private)
{
}

DeclarativeLoaderWidget::~DeclarativeLoaderWidget()
{
  delete d;
}

void DeclarativeLoaderWidget::setSource(const QUrl &source)
{
  if (source == d->source)
    return;

  d->source = source;

  updateDelegate();

  emit sourceChanged(source);
}

QUrl DeclarativeLoaderWidget::source() const
{
  return d->source;
}

void DeclarativeLoaderWidget::updateDelegate()
{
  delete d->component;

  // delete child widgets
  int i = 0;
  while (i < children().count()) {
    QObject *child = children().at(i);
    if (child->isWidgetType()) {
      delete child;
    } else {
      ++i;
    }
  }

  if (layout() == 0) {
    setLayout(new QVBoxLayout);
  }

  if (d->source.isEmpty()) {
    return;
  }

  d->component = new QQmlComponent(qmlEngine(this), d->source, this);
  if (d->component->isLoading()) {
    connect(d->component, SIGNAL(statusChanged(QQmlComponent::Status)), this, SLOT(onStatusChanged()));
    return;
  }

  onStatusChanged();
}

void DeclarativeLoaderWidget::onStatusChanged()
{
  if (d->component->isError()) {
    foreach (const QQmlError &error, d->component->errors()) {
      qDebug() << error.toString();
    }
    return;
  }

  QObject *object = d->component->create();
  if (!object) {
    qWarning() << "Unable to create component from" << d->source;
    return;
  }

  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);

  QWidget *widget = 0;
  if (declarativeObject) {
    declarativeObject->setParent(this);
    widget = qobject_cast<QWidget*>(declarativeObject->object());
  } else {
    widget = qobject_cast<QWidget*>(object);
  }

  if (!widget) {
    qWarning() << "Unable to create widget from" << d->source;
    return;
  }

  layout()->addWidget(widget);
}
