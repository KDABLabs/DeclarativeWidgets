/*
  declarativeinputdialog_p.h

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

#ifndef DECLARATIVEINPUTDIALOG_P_H
#define DECLARATIVEINPUTDIALOG_P_H

#include <QtGlobal>
#include "staticdialogmethodattached_p.h"

#include <QInputDialog>
#include <qqml.h>

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
    explicit DeclarativeInputDialogAttached(QObject *parent = 0);
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

class DeclarativeInputDialog : public QInputDialog
{
  Q_OBJECT

  Q_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode)
  Q_PROPERTY(QString labelText READ labelText WRITE setLabelText)
  Q_PROPERTY(InputDialogOptions options READ options WRITE setOptions)
  Q_PROPERTY(QString textValue READ textValue WRITE setTextValue NOTIFY customTextValueChanged)
  Q_PROPERTY(int intValue READ intValue WRITE setIntValue NOTIFY customIntValueChanged)
  Q_PROPERTY(int doubleValue READ doubleValue WRITE setDoubleValue NOTIFY customDoubleValueChanged)
  Q_PROPERTY(QLineEdit::EchoMode textEchoMode READ textEchoMode WRITE setTextEchoMode)
  Q_PROPERTY(bool comboBoxEditable READ isComboBoxEditable WRITE setComboBoxEditable)
  Q_PROPERTY(QStringList comboBoxItems READ comboBoxItems WRITE setComboBoxItems)
  Q_PROPERTY(int intMinimum READ intMinimum WRITE setIntMinimum)
  Q_PROPERTY(int intMaximum READ intMaximum WRITE setIntMaximum)
  Q_PROPERTY(int intStep READ intStep WRITE setIntStep)
  Q_PROPERTY(double doubleMinimum READ doubleMinimum WRITE setDoubleMinimum)
  Q_PROPERTY(double doubleMaximum READ doubleMaximum WRITE setDoubleMaximum)
  Q_PROPERTY(int doubleDecimals READ doubleDecimals WRITE setDoubleDecimals)
  Q_PROPERTY(QString okButtonText READ okButtonText WRITE setOkButtonText)
  Q_PROPERTY(QString cancelButtonText READ cancelButtonText WRITE setCancelButtonText)

  Q_ENUMS(InputMode)
  Q_ENUMS(InputDialogOption)

  public:
    explicit DeclarativeInputDialog(QWidget *parent = 0);

    static DeclarativeInputDialogAttached *qmlAttachedProperties(QObject *parent);

  Q_SIGNALS:
    void customTextValueChanged();
    void customIntValueChanged();
    void customDoubleValueChanged();
};

QML_DECLARE_TYPEINFO(DeclarativeInputDialog, QML_HAS_ATTACHED_PROPERTIES)

#endif
