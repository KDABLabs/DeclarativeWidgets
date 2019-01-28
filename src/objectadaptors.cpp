/*
  objectadaptors.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "objectadaptors_p.h"

#include "abstractdeclarativeobject_p.h"

#include <QAbstractButton>
#include <QDebug>
#include <QQmlInfo>

// DeclarativeContext
DeclarativeContext::DeclarativeContext(QQmlEngine *engine, QObject *parent)
  : QObject(parent),
    m_context(new QQmlContext(engine, parent))
{
}

DeclarativeContext::DeclarativeContext(DeclarativeContext *parentContext, QObject *parent)
  : QObject(parent),
    m_context(new QQmlContext(parentContext->m_context.data(), parent))
{
}

DeclarativeContext::~DeclarativeContext()
{
  if (m_context && !m_context->parent())
    delete m_context;
}

void DeclarativeContext::setBaseUrl(const QUrl &url)
{
  if (!m_context) {
    qWarning() << Q_FUNC_INFO << "wrapped QQmlContext is no longer available";
    return;
  }

  if (url == m_context->baseUrl())
    return;

  m_context->setBaseUrl(url);
  emit baseUrlChanged(url);
}

QUrl DeclarativeContext::baseUrl() const
{
  if (!m_context) {
    qWarning() << Q_FUNC_INFO << "wrapped QQmlContext is no longer available";
    return QUrl();
  }

  return m_context->baseUrl();
}

DeclarativeContext *DeclarativeContext::createWrapper(QQmlContext *context, QObject *parent)
{
  DeclarativeContext *wrapper = new DeclarativeContext(parent);
  wrapper->m_context = QPointer<QQmlContext>(context);
  context->setParent(parent);

  return wrapper;
}

void DeclarativeContext::setContextProperty(const QString &name, const QVariant &value)
{
  if (!m_context) {
    qWarning() << Q_FUNC_INFO << "wrapped QQmlContext is no longer available";
    return;
  }

  m_context->setContextProperty(name, value);
}

DeclarativeContext::DeclarativeContext(QObject *parent)
  : QObject(parent)
{
}

// DeclarativeQmlContextProperty
DeclarativeQmlContextProperty::DeclarativeQmlContextProperty(QObject *parent)
  : QObject(parent)
{
}

void DeclarativeQmlContextProperty::setName(const QString &name)
{
  if (name == m_name)
    return;

  m_name = name;
  emit nameChanged(name);

  setOnContext();
}

QString DeclarativeQmlContextProperty::name() const
{
  return m_name;
}

void DeclarativeQmlContextProperty::setValue(const QVariant &value)
{
  if (value == m_value)
    return;

  m_value = value;
  emit valueChanged(value);

  setOnContext();
}

QVariant DeclarativeQmlContextProperty::value() const
{
  return m_value;
}

bool DeclarativeQmlContextProperty::isValid() const
{
  return !m_name.isEmpty() && m_value.isValid() && !m_value.isNull();
}

void DeclarativeQmlContextProperty::setContext(DeclarativeContext *context)
{
  m_context = QPointer<DeclarativeContext>(context);
  setOnContext();
}

void DeclarativeQmlContextProperty::setOnContext()
{
  if (!isValid() || !m_context)
    return;

  m_context->setContextProperty(m_name, m_value);
}
