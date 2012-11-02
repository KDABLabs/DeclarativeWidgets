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

#include "declarativefiledialog_p.h"

class DeclarativeFileDialogAttached::Private
{
  public:
    QPointer<QObject> dialogParent;
    QString caption;
    QString dir;
    QStringList nameFilters;
    QString selectedFilter;
};

DeclarativeFileDialogAttached::DeclarativeFileDialogAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

DeclarativeFileDialogAttached::~DeclarativeFileDialogAttached()
{
  delete d;
}

void DeclarativeFileDialogAttached::setDialogParent(QObject *parent)
{
  if (parent == d->dialogParent)
    return;

  d->dialogParent = parent;
  emit dialogParentChanged(parent);
}

QObject *DeclarativeFileDialogAttached::dialogParent() const
{
  return d->dialogParent;
}

void DeclarativeFileDialogAttached::setCaption(const QString &caption)
{
  if (caption == d->caption)
    return;

  d->caption = caption;
  emit captionChanged(caption);
}

QString DeclarativeFileDialogAttached::caption() const
{
  return d->caption;
}

void DeclarativeFileDialogAttached::setDir(const QString &dir)
{
  if (dir == d->dir)
    return;

  d->dir = dir;
  emit dirChanged(dir);
}

QString DeclarativeFileDialogAttached::dir() const
{
  return d->dir;
}

void DeclarativeFileDialogAttached::setNameFilters(const QStringList &nameFilters)
{
  if (nameFilters == d->nameFilters)
    return;

  d->nameFilters = nameFilters;
  emit nameFiltersChanged(nameFilters);
}

QStringList DeclarativeFileDialogAttached::nameFilters() const
{
  return d->nameFilters;
}

QString DeclarativeFileDialogAttached::selectedFilter() const
{
  return d->selectedFilter;
}

QString DeclarativeFileDialogAttached::getExistingDirectory()
{
  return QFileDialog::getExistingDirectory(bestParentWindow(d->dialogParent), d->caption, d->dir, QFileDialog::ShowDirsOnly);
}

QString DeclarativeFileDialogAttached::getOpenFileName()
{
  QString selectedFilter;
  const QString retVal = QFileDialog::getOpenFileName(bestParentWindow(d->dialogParent), d->caption, d->dir,
                                                      d->nameFilters.join(";;"), &selectedFilter, 0);
  setSelectedFilter(selectedFilter);
  return retVal;
}

QStringList DeclarativeFileDialogAttached::getOpenFileNames()
{
  QString selectedFilter;
  const QStringList retVal = QFileDialog::getOpenFileNames(bestParentWindow(d->dialogParent), d->caption, d->dir,
                                                           d->nameFilters.join(";;"), &selectedFilter, 0);
  setSelectedFilter(selectedFilter);
  return retVal;
}

QString DeclarativeFileDialogAttached::getSaveFileName()
{
  QString selectedFilter;
  const QString retVal = QFileDialog::getSaveFileName(bestParentWindow(d->dialogParent), d->caption, d->dir,
                                                      d->nameFilters.join(";;"), &selectedFilter, 0);
  setSelectedFilter(selectedFilter);
  return retVal;
}

QWidget *DeclarativeFileDialogAttached::bestParentWindow(QObject *parent) const
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

void DeclarativeFileDialogAttached::setSelectedFilter(const QString &filter)
{
  if (filter == d->selectedFilter)
    return;

  d->selectedFilter = filter;
  emit selectedFilterChanged(filter);
}


DeclarativeFileDialog::DeclarativeFileDialog(QObject *parent)
  : DeclarativeWidgetProxy<FileDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeFileDialogAttached *DeclarativeFileDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeFileDialogAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeFileDialog, FileDialog)
