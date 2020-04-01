/*
  declarativefontdialog.cpp

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

#include "declarativefontdialog_p.h"

class DeclarativeFontDialogAttached::Private
{
  public:
    Private() : dialogAccepted(false), options(0) {}

  public:
    QFont initial;
    QString title;
    bool dialogAccepted;
    QFontDialog::FontDialogOptions options;
};


DeclarativeFontDialogAttached::DeclarativeFontDialogAttached(QObject *parent)
  : StaticDialogMethodAttached(parent), d(new Private)
{
}

DeclarativeFontDialogAttached::~DeclarativeFontDialogAttached()
{
  delete d;
}

void DeclarativeFontDialogAttached::setTitle(const QString &title)
{
  if (title == d->title)
    return;

  d->title = title;
  emit titleChanged(title);
}

QString DeclarativeFontDialogAttached::title() const
{
  return d->title;
}

bool DeclarativeFontDialogAttached::dialogAccepted() const
{
  return d->dialogAccepted;
}

void DeclarativeFontDialogAttached::setOptions(unsigned int options)
{
  if (options == d->options)
    return;

  d->options = static_cast<QFontDialog::FontDialogOptions>(options);
  emit optionsChanged(options);
}

unsigned int DeclarativeFontDialogAttached::options() const
{
  return d->options;
}

QFont DeclarativeFontDialogAttached::getFont()
{
  QWidget *parent = bestParentWindow();
  bool ok = false;

  QFont retVal;
  if (d->title.isEmpty() && d->options == 0) {
    retVal = QFontDialog::getFont(&ok, d->initial, parent);
  } else if (d->options != 0) {
    retVal = QFontDialog::getFont(&ok, d->initial, parent, d->title, d->options);
  } else {
    retVal = QFontDialog::getFont(&ok, d->initial, parent, d->title);
  }

  setDialogAccepted(ok);
  return retVal;
}

QFont DeclarativeFontDialogAttached::getFont(const QString &fontFamily)
{
  d->initial = QFont(fontFamily);
  return getFont();
}

void DeclarativeFontDialogAttached::setDialogAccepted(bool accepted)
{
  if (accepted == d->dialogAccepted)
    return;

  d->dialogAccepted = accepted;
  emit dialogAcceptedChanged(accepted);
}

Q_DECLARE_METATYPE(Qt::WindowFlags)

DeclarativeFontDialog::DeclarativeFontDialog(QWidget *parent)
  : QFontDialog(parent)
{
  setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
}

DeclarativeFontDialogAttached *DeclarativeFontDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeFontDialogAttached(parent);
}
