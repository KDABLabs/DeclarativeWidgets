/*
  declarativewidgetsdocument.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Tobias Koenig <tobias.koenig@kdab.com>
  Author: Kevin Krammer <kevin.krammer@kdab.com>
  Author: Nathan Collins <nathan.collins@kdab.com>

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

#include "declarativewidgetsdocument.h"

#include "abstractdeclarativeobject_p.h"

#include <QDebug>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QWidget>

class DeclarativeWidgetsDocument::Private
{
  public:
    Private(DeclarativeWidgetsDocument *qq, const QUrl &url, QQmlEngine* engine)
      : q(qq)
      , m_url(url)
      , m_engine(engine ? engine : new QQmlEngine(q))
      , m_component(new QQmlComponent(m_engine, q))
    {
    }

    DeclarativeWidgetsDocument* q;
    QUrl m_url;
    QQmlEngine* m_engine;
    QQmlComponent* m_component;
};

DeclarativeWidgetsDocument::DeclarativeWidgetsDocument(const QUrl &url, QObject *parent)
    : DeclarativeWidgetsDocument(url, nullptr, parent)
{

}

DeclarativeWidgetsDocument::DeclarativeWidgetsDocument(const QUrl &url, QQmlEngine *engine, QObject *parent)
  : QObject(parent)
  , d(new Private(this, url, engine))
{
  d->m_component->loadUrl(d->m_url);
  if (d->m_component->isError()) {
    foreach (const QQmlError &error, d->m_component->errors())
      qDebug() << error.toString();
  }
}

DeclarativeWidgetsDocument::~DeclarativeWidgetsDocument()
{
  delete d;
}

void DeclarativeWidgetsDocument::setContextProperty(const QString &name, const QVariant &value)
{
  d->m_engine->rootContext()->setContextProperty(name, value);
}

void DeclarativeWidgetsDocument::setContextProperty(const QString &name, QObject *object)
{
  d->m_engine->rootContext()->setContextProperty(name, object);
}

QQmlEngine* DeclarativeWidgetsDocument::engine() const
{
  return d->m_engine;
}

QWidget* DeclarativeWidgetsDocument::createWidget()
{
  QObject *object = d->m_component->create();
  if (!object) {
    qWarning("Unable to create component");
    return 0;
  }

  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);

  if (declarativeObject) {
    declarativeObject->setParent(this);
    return qobject_cast<QWidget*>(declarativeObject->object());
  }

  QWidget *widget = qobject_cast<QWidget*>(object);
  if (widget)
    return widget;

  qFatal("Root Element is neither an AbstractDeclarativeObject nor a widget");
  return 0;
}
