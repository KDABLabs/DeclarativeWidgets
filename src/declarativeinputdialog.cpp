/*
  declarativeinputdialog.cpp

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

#include "declarativeinputdialog_p.h"

class DeclarativeInputDialogAttached::Private
{
  public:
    Private() : dialogAccepted(false),
                value(0), min(-2147483647), max(2147483647), decimals(1), step(1),
                currentItem(0), itemsEditable(true),
                echoMode(QLineEdit::Normal)
    {}

  public:
    QString title;
    QString label;
    bool dialogAccepted;

    QVariant value;
    QVariant min;
    QVariant max;
    int decimals;
    int step;

    int currentItem;
    bool itemsEditable;

    QLineEdit::EchoMode echoMode;
    QString text;
};

DeclarativeInputDialogAttached::DeclarativeInputDialogAttached(QObject *parent)
  : StaticDialogMethodAttached(parent), d(new Private)
{
}

DeclarativeInputDialogAttached::~DeclarativeInputDialogAttached()
{
  delete d;
}

void DeclarativeInputDialogAttached::setTitle(const QString &title)
{
  if (title == d->title)
    return;

  d->title = title;
  emit titleChanged(title);
}

QString DeclarativeInputDialogAttached::title() const
{
  return d->title;
}

void DeclarativeInputDialogAttached::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;
  emit labelChanged(label);
}

QString DeclarativeInputDialogAttached::label() const
{
  return d->label;
}

bool DeclarativeInputDialogAttached::dialogAccepted() const
{
  return d->dialogAccepted;
}

void DeclarativeInputDialogAttached::setValue(const QVariant &value)
{
  if (value == d->value)
    return;

  d->value = value;
  emit valueChanged(value);
}

QVariant DeclarativeInputDialogAttached::value() const
{
  return d->value;
}

void DeclarativeInputDialogAttached::setMin(const QVariant &min)
{
  if (min == d->min)
    return;

  d->min = min;
  emit minChanged(min);
}

QVariant DeclarativeInputDialogAttached::min() const
{
  return d->min;
}

void DeclarativeInputDialogAttached::setMax(const QVariant &max)
{
  if (max == d->max)
    return;

  d->max = max;
  emit maxChanged(max);
}

QVariant DeclarativeInputDialogAttached::max() const
{
  return d->max;
}

void DeclarativeInputDialogAttached::setDecimals(int decimals)
{
  if (decimals == d->decimals)
    return;

  d->decimals = decimals;
  emit decimalsChanged(decimals);
}

int DeclarativeInputDialogAttached::decimals() const
{
  return d->decimals;
}

void DeclarativeInputDialogAttached::setStep(int step)
{
  if (step == d->step)
    return;

  d->step = step;
  emit stepChanged(step);
}

int DeclarativeInputDialogAttached::step() const
{
  return d->step;
}

void DeclarativeInputDialogAttached::setCurrentItem(int current)
{
  if (current == d->currentItem)
    return;

  d->currentItem = current;
  emit currentItemChanged(current);
}

int DeclarativeInputDialogAttached::currentItem() const
{
  return d->currentItem;
}

void DeclarativeInputDialogAttached::setItemsEditable(bool editable)
{
  if (editable == d->itemsEditable)
    return;

  d->itemsEditable = editable;
  emit itemsEditableChanged(editable);
}

bool DeclarativeInputDialogAttached::itemsEditable() const
{
  return d->itemsEditable;
}

void DeclarativeInputDialogAttached::setEchoMode(QLineEdit::EchoMode echoMode)
{
  if (echoMode == d->echoMode)
    return;

  d->echoMode = echoMode;
  emit echoModeChanged(echoMode);
}

QLineEdit::EchoMode DeclarativeInputDialogAttached::echoMode() const
{
  return d->echoMode;
}

void DeclarativeInputDialogAttached::setText(const QString &text)
{
  if (text == d->text)
    return;

  d->text = text;
  emit textChanged(text);
}

QString DeclarativeInputDialogAttached::text() const
{
  return d->text;
}

double DeclarativeInputDialogAttached::getDouble()
{
  QWidget *parent = bestParentWindow();
  bool ok = false;
  const double value = d->value.canConvert<double>() ? d->value.value<double>() : 0.0;
  const double min = d->min.canConvert<double>() ? d->min.value<double>() : -2147483647;
  const double max = d->max.canConvert<double>() ? d->max.value<double>() : 2147483647;

  const double retVal = QInputDialog::getDouble(parent, d->title, d->label, value, min, max, d->decimals, &ok);

  setDialogAccepted(ok);
  return retVal;
}

int DeclarativeInputDialogAttached::getInt()
{
  QWidget *parent = bestParentWindow();
  bool ok = false;
  const int value = d->value.canConvert<int>() ? d->value.value<int>() : 0;
  const int min = d->min.canConvert<int>() ? d->min.value<int>() : -2147483647;
  const int max = d->max.canConvert<int>() ? d->max.value<int>() : 2147483647;

  const int retVal = QInputDialog::getInt(parent, d->title, d->label, value, min, max, d->step, &ok);

  setDialogAccepted(ok);
  return retVal;
}

QString DeclarativeInputDialogAttached::getItem(const QStringList &items)
{
  QWidget *parent = bestParentWindow();
  bool ok = false;

  const QString retVal = QInputDialog::getItem(parent, d->title, d->label, items, d->currentItem, d->itemsEditable, &ok);

  setDialogAccepted(ok);
  return retVal;
}

QString DeclarativeInputDialogAttached::getText()
{
  QWidget *parent = bestParentWindow();
  bool ok = false;

  const QString retVal = QInputDialog::getText(parent, d->title, d->label, d->echoMode, d->text, &ok);

  setDialogAccepted(ok);
  return retVal;
}

void DeclarativeInputDialogAttached::setDialogAccepted(bool accepted)
{
  if (accepted == d->dialogAccepted)
    return;

  d->dialogAccepted = accepted;
  emit dialogAcceptedChanged(accepted);
}

Q_DECLARE_METATYPE(Qt::WindowFlags)

DeclarativeInputDialog::DeclarativeInputDialog(QWidget *parent) : QInputDialog(parent)
{
  setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));

  connect(this, SIGNAL(textValueChanged(QString)), this, SIGNAL(customTextValueChanged()));
  connect(this, SIGNAL(intValueChanged(int)), this, SIGNAL(customIntValueChanged()));
  connect(this, SIGNAL(doubleValueChanged(double)), this, SIGNAL(customDoubleValueChanged()));
}

DeclarativeInputDialogAttached *DeclarativeInputDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeInputDialogAttached(parent);
}
