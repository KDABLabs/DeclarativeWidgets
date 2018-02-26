/*
  declarativerepeater.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Lova Widmark <znurree@gmail.com>

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

#include "declarativerepeater_p.h"

#include <private/qqmldelegatemodel_p.h>

#include <QLayout>
#include <QWidget>
#include <QQmlInfo>
#include <QPointer>

class QQmlContext;
class QQmlInstanceModel;

class DeclarativeRepeater::Private
{
  public:
    Private()
      : model(nullptr)
      , itemCount(0)
    {
    }

    ~Private()
    {
      delete model;
    }

    void requestItems()
    {
      for (int i = 0; i < itemCount; i++) {
        QObject *object = model->object(i, QQmlIncubator::AsynchronousIfNested);
        if (object)
          model->release(object);
      }
    }

    QPointer<QQmlDelegateModel> model;
    QVector<QPointer<QWidget>> deletables;
    QVariant dataSource;

    int itemCount;
};

DeclarativeRepeater::DeclarativeRepeater(QObject *parent)
  : QObject(parent)
  , d(new Private)
{
}

QVariant DeclarativeRepeater::model() const
{
  return d->dataSource;
}

void DeclarativeRepeater::setModel(const QVariant &model)
{
  clear();

  if (d->model) {
    qmlobject_disconnect(d->model, QQmlInstanceModel, SIGNAL(modelUpdated(QQmlChangeSet,bool)),
              this, DeclarativeRepeater, SLOT(modelUpdated(QQmlChangeSet,bool)));
    qmlobject_disconnect(d->model, QQmlInstanceModel, SIGNAL(createdItem(int,QObject*)),
              this, DeclarativeRepeater, SLOT(createdItem(int,QObject*)));
    qmlobject_disconnect(d->model, QQmlInstanceModel, SIGNAL(initItem(int,QObject*)),
              this, DeclarativeRepeater, SLOT(initItem(int,QObject*)));
  } else {
    d->model = new QQmlDelegateModel(qmlContext(this));
    d->model->componentComplete();
  }

  d->model->setModel(model);
  d->dataSource = model;

  qmlobject_connect(d->model, QQmlInstanceModel, SIGNAL(modelUpdated(QQmlChangeSet,bool)),
          this, DeclarativeRepeater, SLOT(modelUpdated(QQmlChangeSet,bool)));
  qmlobject_connect(d->model, QQmlInstanceModel, SIGNAL(createdItem(int,QObject*)),
          this, DeclarativeRepeater, SLOT(createdItem(int,QObject*)));
  qmlobject_connect(d->model, QQmlInstanceModel, SIGNAL(initItem(int,QObject*)),
          this, DeclarativeRepeater, SLOT(initItem(int,QObject*)));

  regenerate();

  emit modelChanged();
  emit countChanged();
}

QQmlComponent *DeclarativeRepeater::delegate() const
{
  if (d->model)
    return d->model->delegate();

  return Q_NULLPTR;
}

void DeclarativeRepeater::setDelegate(QQmlComponent *delegate)
{
  if (d->model) {
    if (delegate == d->model->delegate())
      return;
  } else {
    d->model = new QQmlDelegateModel(qmlContext(this));
  }

  d->model->setDelegate(delegate);

  regenerate();

  emit delegateChanged();
}

int DeclarativeRepeater::count() const
{
  if (d->model)
    return d->model->count();

  return 0;
}

QWidget *DeclarativeRepeater::itemAt(int index) const
{
  if (index >= 0 && index < d->deletables.count())
    return d->deletables[index];

  return Q_NULLPTR;
}

void DeclarativeRepeater::componentComplete()
{
  if (d->model)
    d->model->componentComplete();

  regenerate();

  if (d->model && d->model->count())
    emit countChanged();
}

void DeclarativeRepeater::clear()
{
  if (d->model) {
    // We remove in reverse order deliberately; so that signals are emitted
    // with sensible indices.
    for (int i = d->deletables.count() - 1; i >= 0; --i) {
      if (QWidget *widget = d->deletables.at(i)) {
        emit itemRemoved(i, widget);
        d->model->release(widget);
      }
    }
  }

  QLayout *layout = qobject_cast<QLayout *>(parent());

  if (!layout) {
    qmlInfo(this) << "Parent must be of BoxLayout type";
    return;
  }

  for (QWidget *widget : d->deletables) {
    layout->removeWidget(widget);
  }

  d->deletables.clear();
  d->itemCount = 0;
}

void DeclarativeRepeater::regenerate()
{
  clear();

  if (!d->model || !d->model->count() || !d->model->isValid() || !parent())
    return;

  d->itemCount = count();
  d->deletables.resize(d->itemCount);
  d->requestItems();
}

void DeclarativeRepeater::classBegin()
{
}

void DeclarativeRepeater::createdItem(int index, QObject *)
{
  QObject *object = d->model->object(index, QQmlIncubator::AsynchronousIfNested);
  QWidget *item = qmlobject_cast<QWidget*>(object);

  emit itemAdded(index, item);
}

void DeclarativeRepeater::initItem(int index, QObject *object)
{
  QWidget *widget = qobject_cast<QWidget *>(object);

  if (!d->deletables.at(index)) {
    if (!widget) {
      if (object) {
        d->model->release(object);
        qmlInfo(this) << "Delegate must be of Widget type";
      }
      return;
    }

    QLayout *layout = qobject_cast<QLayout *>(parent());

    if (!layout) {
      qmlInfo(this) << "Parent must be of BoxLayout type";
      return;
    }

    layout->addWidget(widget);

    d->deletables[index] = widget;
  }
}

void DeclarativeRepeater::modelUpdated(const QQmlChangeSet &changeSet, bool reset)
{
  Q_UNUSED(reset);

  regenerate();

  if (changeSet.difference() != 0)
    emit countChanged();
}
