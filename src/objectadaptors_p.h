/*
  objectadaptors_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Tobias Koenig <tobias.koenig@kdab.com>
  Author: Kevin Krammer <kevin.krammer@kdab.com>
  Author: Nathan Collins <nathan.collins@kdab.com>

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

#ifndef OBJECTADAPTORS_P_H
#define OBJECTADAPTORS_P_H

#include <QtGlobal>

#include <QDialog>
#include <QMenu>
#include <QPointer>
#include <QQmlContext>

class DeclarativeContext : public QObject
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

class DeclarativeQmlContextProperty : public QObject
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

class  Menu : public QMenu
{
  Q_OBJECT

public:
  Menu() : QMenu()
  {
    setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
  }
};

#endif
