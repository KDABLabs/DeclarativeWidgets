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

#ifndef DECLARATIVEINPUTDIALOG_P_H
#define DECLARATIVEINPUTDIALOG_P_H

#include "declarativewidgetproxy_p.h"

#include "objectadaptors_p.h"
#include "staticdialogmethodattached_p.h"

class DeclarativeInputDialogAttached : public StaticDialogMethodAttached
{
  Q_OBJECT
  Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
  Q_PROPERTY(bool ok READ dialogAccepted NOTIFY dialogAcceptedChanged)

  Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
  Q_PROPERTY(QVariant min READ min WRITE setMin NOTIFY minChanged)
  Q_PROPERTY(QVariant max READ max WRITE setMax NOTIFY maxChanged)
  Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)
  Q_PROPERTY(int step READ step WRITE setStep NOTIFY stepChanged)

  Q_PROPERTY(int current READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged)
  Q_PROPERTY(bool editable READ itemsEditable WRITE setItemsEditable NOTIFY itemsEditableChanged)

  Q_PROPERTY(QLineEdit::EchoMode echoMode READ echoMode WRITE setEchoMode NOTIFY echoModeChanged)
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

  public:
    DeclarativeInputDialogAttached(QObject *parent = 0);
    ~DeclarativeInputDialogAttached();

    void setTitle(const QString &title);
    QString title() const;

    void setLabel(const QString &label);
    QString label() const;

    bool dialogAccepted() const;

    void setValue(const QVariant &value);
    QVariant value() const;

    void setMin(const QVariant &min);
    QVariant min() const;

    void setMax(const QVariant &max);
    QVariant max() const;

    void setDecimals(int decimals);
    int decimals() const;

    void setStep(int step);
    int step() const;

    void setCurrentItem(int current);
    int currentItem() const;

    void setItemsEditable(bool editable);
    bool itemsEditable() const;

    void setEchoMode(QLineEdit::EchoMode echoMode);
    QLineEdit::EchoMode echoMode() const;

    void setText(const QString &text);
    QString text() const;

    Q_INVOKABLE double getDouble();

    Q_INVOKABLE int getInt();

    Q_INVOKABLE QString getItem(const QStringList &items);

    Q_INVOKABLE QString getText();

  Q_SIGNALS:
    void titleChanged(const QString &title);
    void labelChanged(const QString &label);
    void dialogAcceptedChanged(bool accepted);

    void valueChanged(const QVariant &value);
    void minChanged(const QVariant &min);
    void maxChanged(const QVariant &max);
    void decimalsChanged(int decimals);
    void stepChanged(int step);

    void currentItemChanged(int current);
    void itemsEditableChanged(bool editable);

    void echoModeChanged(QLineEdit::EchoMode echoMode);
    void textChanged(const QString &text);

  private:
    void setDialogAccepted(bool accepted);

    class Private;
    Private *const d;
};

class DeclarativeInputDialog : public DeclarativeWidgetProxy<InputDialog>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeInputDialog(QObject *parent = 0);

    static DeclarativeInputDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeInputDialog, QML_HAS_ATTACHED_PROPERTIES)

#endif
