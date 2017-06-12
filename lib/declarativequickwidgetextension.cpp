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

#include "declarativequickwidgetextension_p.h"

#include "declarativeqmlcontext_p.h"

#include <QQuickWidget>

DeclarativeQuickWidgetExtension::DeclarativeQuickWidgetExtension(QObject *parent)
  : DeclarativeWidgetExtension(parent)
{
}

DeclarativeQuickWidgetExtension::~DeclarativeQuickWidgetExtension()
{
}

QQuickWidget *DeclarativeQuickWidgetExtension::extendedDeclarativeView() const
{
  QQuickWidget *declarativeView = qobject_cast<QQuickWidget*>(extendedWidget());
  Q_ASSERT(declarativeView);

  return declarativeView;
}

void DeclarativeQuickWidgetExtension::setDeclarativeRootContext(QObject *context)
{
  DeclarativeContext *declarativeContext = dynamic_cast<DeclarativeContext*>(context);
  if (!declarativeContext) {
    AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(context);
    if (declarativeObject)
      declarativeContext = dynamic_cast<DeclarativeContext*>(declarativeObject->object());
  }

  if (!declarativeContext) {
    qWarning() << Q_FUNC_INFO << "Cannot set object of type " << context->metaObject()->className()
                                       << " as root context";
    return;
  }

  if (declarativeContext == m_rootContext.data())
    return;

  // we can only set a different wrapper, not replace the view's root context
  Q_ASSERT(m_rootContext.isNull() || declarativeContext->context() == m_rootContext->context());

  m_rootContext = QPointer<DeclarativeContext>(declarativeContext);
  emit declarativeRootContextChanged();
}

QObject *DeclarativeQuickWidgetExtension::declarativeRootContext() const
{
  return m_rootContext;
}
