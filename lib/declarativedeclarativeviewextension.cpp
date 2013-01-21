/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

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

#include "declarativedeclarativeviewextension_p.h"

#include "declarativedeclarativecontext_p.h"

#include <QDeclarativeView>

DeclarativeDeclarativeViewExtension::DeclarativeDeclarativeViewExtension(QObject *parent)
  : DeclarativeWidgetExtension(parent)
{
}

DeclarativeDeclarativeViewExtension::~DeclarativeDeclarativeViewExtension()
{
}

QDeclarativeView *DeclarativeDeclarativeViewExtension::extendedDeclarativeView() const
{
  QDeclarativeView *declarativeView = qobject_cast<QDeclarativeView*>(extendedWidget());
  Q_ASSERT(declarativeView);

  return declarativeView;
}

void DeclarativeDeclarativeViewExtension::setDeclarativeRootContext(QObject *context)
{
  DeclarativeContext *declarativeContext = dynamic_cast<DeclarativeContext*>(context);
  if (!declarativeContext) {
    AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(context);
    if (declarativeObject)
      declarativeContext = dynamic_cast<DeclarativeContext*>(declarativeObject->object());
  }

  if (!declarativeContext) {
    qmlInfo(extendedDeclarativeView()) << "Cannot set object of type " << context->metaObject()->className()
                                       << " as root context";
    return;
  }

  if (declarativeContext == m_rootContext.data())
    return;

  // we can only set a different wrapper, not replace the view's root context
  Q_ASSERT(declarativeContext->context() == m_rootContext->context());

  m_rootContext = QPointer<DeclarativeContext>(declarativeContext);
  emit declarativeRootContextChanged();
}

QObject *DeclarativeDeclarativeViewExtension::declarativeRootContext() const
{
  return m_rootContext;
}
