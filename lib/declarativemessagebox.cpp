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

#include "declarativemessagebox_p.h"

DeclarativeMessageBoxAttached::DeclarativeMessageBoxAttached(QObject *parent)
  : QObject(parent)
{
}

void DeclarativeMessageBoxAttached::about(QObject *parent, const QString &title, const QString &text)
{
  QMessageBox::about(bestParentWindow(parent), title, text);
}

void DeclarativeMessageBoxAttached::aboutQt(QObject *parent, const QString &title)
{
  QMessageBox::aboutQt(bestParentWindow(parent), title);
}

int DeclarativeMessageBoxAttached::critical(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::critical(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

int DeclarativeMessageBoxAttached::information(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::information(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

int DeclarativeMessageBoxAttached::question(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::question(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

int DeclarativeMessageBoxAttached::warning(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::warning(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

QWidget *DeclarativeMessageBoxAttached::bestParentWindow(QObject *parent) const
{
  if (!parent)
    parent = this->parent();

  // if parent is a Declarative Object, search the proxied hierarchy
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject)
    parent = declarativeObject->object();

  while (parent) {
    QWidget *widget = qobject_cast<QWidget*>(parent);
    if (widget)
      return widget->topLevelWidget();

    parent = parent->parent();
  }

  return 0;
}

DeclarativeMessageBox::DeclarativeMessageBox(QObject *parent) : DeclarativeObjectProxy<QMessageBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeMessageBoxAttached *DeclarativeMessageBox::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeMessageBoxAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeMessageBox, QMessageBox)
