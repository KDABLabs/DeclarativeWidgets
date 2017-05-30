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

#ifndef DECLARATIVETABWIDGET_P_H
#define DECLARATIVETABWIDGET_P_H

#include "defaultwidgetcontainer.h"

#include <qqml.h>
#include <QTabWidget>

class DeclarativeTabWidgetAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
  Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)

  public:
    explicit DeclarativeTabWidgetAttached(QObject *parent = 0);
    ~DeclarativeTabWidgetAttached();

    void setLabel(const QString &label);
    QString label() const;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

    void setAssociation(QTabWidget *widget, int index);

  Q_SIGNALS:
    void labelChanged(const QString &label);
    void iconChanged(const QIcon &icon);

  private:
    class Private;
    Private *const d;
};

class DeclarativeTabWidget : public QTabWidget
{
  Q_OBJECT

  public:
    explicit DeclarativeTabWidget(QObject *parent = 0);

    static DeclarativeTabWidgetAttached *qmlAttachedProperties(QObject *object);
};

QML_DECLARE_TYPEINFO(DeclarativeTabWidget, QML_HAS_ATTACHED_PROPERTIES)

class TabWidgetWidgetContainer : public DefaultWidgetContainer
{
  public:
    explicit TabWidgetWidgetContainer(QObject *parent = 0);
    void setLayout(QLayout *layout);
    void addWidget(QWidget *widget);

  private:
    QTabWidget *extendedTabWidget() const;
};

#endif
