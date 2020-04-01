/*
  declarativeqmlcontext.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2017-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "declarativeqmlcontext_p.h"

#include <QQuickWidget>

DeclarativeQmlContext::DeclarativeQmlContext(QObject *parent)
  : DeclarativeObjectProxy<DeclarativeContext>(parent)
{
}

void DeclarativeQmlContext::createProxiedObject() const
{
  AbstractDeclarativeObject *declarativeParent = dynamic_cast<AbstractDeclarativeObject*>(parent());
  if (declarativeParent) {
    DeclarativeContext *parentContext = qobject_cast<DeclarativeContext*>(declarativeParent->object());
    if (parentContext) {
      DeclarativeContext *context = new DeclarativeContext(parentContext);
      m_proxiedObject = QPointer<DeclarativeContext>(context);
      connectAllSignals(m_proxiedObject, this);
      return;
    }
  } else {
    QQuickWidget *view = qobject_cast<QQuickWidget*>(parent());
    if (view) {
      DeclarativeContext *context = DeclarativeContext::createWrapper(view->rootContext(), view);
      m_proxiedObject = QPointer<DeclarativeContext>(context);
      connectAllSignals(m_proxiedObject, this);
      return;
    }
  }

  qmlInfo(this) << "Cannot create DeclarativeContext, parent is neither QuickWidget nor DeclarativeContext";
}

void DeclarativeQmlContext::dataAppend(QObject *object)
{
  DeclarativeQmlContextProperty *contextProperty = qobject_cast<DeclarativeQmlContextProperty*>(object);
  if (contextProperty) {
    if (!m_proxiedObject)
      createProxiedObject();

    contextProperty->setContext(m_proxiedObject);
  }

  DeclarativeObjectProxy<DeclarativeContext>::dataAppend(object);
}

CUSTOM_METAOBJECT(DeclarativeQmlContext, DeclarativeContext)
