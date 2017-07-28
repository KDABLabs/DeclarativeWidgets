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

#ifndef OBJECTADAPTORS_P_H
#define OBJECTADAPTORS_P_H

#include "declarativewidgets_export.h"

#include <QDialog>
#include <QMenu>
#include <QPointer>
#include <QQmlContext>

class DECLARATIVEWIDGETS_EXPORT DeclarativeContext : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QUrl baseUrl READ baseUrl WRITE setBaseUrl NOTIFY baseUrlChanged)

  public:
    explicit DeclarativeContext(QQmlEngine *engine, QObject *parent = 0);
    explicit DeclarativeContext(DeclarativeContext *parentContext, QObject *parent = 0);
    ~DeclarativeContext();

    void setBaseUrl(const QUrl &url);
    QUrl baseUrl() const;

    static DeclarativeContext *createWrapper(QQmlContext *context, QObject *parent = 0);

    QQmlContext *context() const { return m_context.data(); }

    void setContextProperty(const QString &name, const QVariant &value);

  Q_SIGNALS:
    void baseUrlChanged(const QUrl &url);

  private:
    QPointer<QQmlContext> m_context;

    DeclarativeContext(QObject *parent);
};

Q_DECLARE_METATYPE(DeclarativeContext*)

class DECLARATIVEWIDGETS_EXPORT DeclarativeQmlContextProperty : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)

  public:
    explicit DeclarativeQmlContextProperty(QObject *parent = 0);

    void setName(const QString &name);
    QString name() const;

    void setValue(const QVariant &value);
    QVariant value() const;

    bool isValid() const;

    void setContext(DeclarativeContext *context);

  Q_SIGNALS:
    void nameChanged(const QString &name);
    void valueChanged(const QVariant &value);

  private:
    QString m_name;
    QVariant m_value;
    QPointer<DeclarativeContext> m_context;

    void setOnContext();
};


class DECLARATIVEWIDGETS_EXPORT Dialog : public QDialog
{
  Q_OBJECT

public:
  Dialog() : QDialog()
  {
    setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
  }
};

Q_DECLARE_METATYPE(Qt::WindowFlags)

class  DECLARATIVEWIDGETS_EXPORT Menu : public QMenu
{
  Q_OBJECT

public:
  Menu() : QMenu()
  {
    setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
  }
};

#endif
