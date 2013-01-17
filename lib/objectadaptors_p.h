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

#ifndef OBJECTADAPTORS_P_H
#define OBJECTADAPTORS_P_H

#include <QDeclarativeContext>
#include <QDeclarativeView>
#include <QDialog>
#include <QMenu>
#include <QPointer>

class DeclarativeContext : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QUrl baseUrl READ baseUrl WRITE setBaseUrl NOTIFY baseUrlChanged)

  public:
    explicit DeclarativeContext(QDeclarativeEngine *engine, QObject *parent = 0);
    explicit DeclarativeContext(DeclarativeContext *parentContext, QObject *parent = 0);
    ~DeclarativeContext();

    void setBaseUrl(const QUrl &url);
    QUrl baseUrl() const;

    static DeclarativeContext *createWrapper(QDeclarativeContext *context, QObject *parent = 0);

    QDeclarativeContext *context() const { return m_context.data(); }

    void setContextProperty(const QString &name, const QVariant &value);

  Q_SIGNALS:
    void baseUrlChanged(const QUrl &url);

  private:
    QPointer<QDeclarativeContext> m_context;

    DeclarativeContext(QObject *parent);
};

Q_DECLARE_METATYPE(DeclarativeContext*)

class DeclarativeContextProperty : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)

  public:
    explicit DeclarativeContextProperty(QObject *parent = 0);

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


class DeclarativeView : public QDeclarativeView
{
  Q_OBJECT
  Q_PROPERTY(QObject* rootContext READ declarativeRootContext WRITE setDeclarativeRootContext
             NOTIFY declarativeRootContextChanged)

  public:
    explicit DeclarativeView(QWidget *parent = 0);
    ~DeclarativeView();

    void setDeclarativeRootContext(QObject *context);
    QObject *declarativeRootContext() const;

  Q_SIGNALS:
    void declarativeRootContextChanged();

  private:
    QPointer<DeclarativeContext> m_rootContext;
};

class Dialog : public QDialog
{
  Q_OBJECT

public:
  Dialog() : QDialog()
  {
    setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
  }
};

Q_DECLARE_METATYPE(Qt::WindowFlags)

class Menu : public QMenu
{
  Q_OBJECT

public:
  Menu() : QMenu()
  {
    setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
  }
};

#endif
