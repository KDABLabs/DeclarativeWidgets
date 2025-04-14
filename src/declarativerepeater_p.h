/*
  declarativerepeater_p.h

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2012-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Lova Widmark <znurree@gmail.com>

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

#ifndef DECLARATIVEREPEATER_P_H
#define DECLARATIVEREPEATER_P_H

#include <QQmlParserStatus>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QQmlChangeSet;
class QQmlComponent;
QT_END_NAMESPACE

class DeclarativeRepeater : public QObject, public QQmlParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QVariant model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QQmlComponent *delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    Q_CLASSINFO("DefaultProperty", "delegate")

    Q_INTERFACES(QQmlParserStatus)

public:
    DeclarativeRepeater(QObject *parent = Q_NULLPTR);

    QVariant model() const;
    void setModel(const QVariant &model);

    QQmlComponent *delegate() const;
    void setDelegate(QQmlComponent *);

    int count() const;

    Q_INVOKABLE QWidget *itemAt(int index) const;

  Q_SIGNALS:
    void modelChanged();
    void delegateChanged();
    void countChanged();

    void itemAdded(int index, QWidget *item);
    void itemRemoved(int index, QWidget *item);

  private:
    class Private;
    Private *const d;

    void clear();
    void regenerate();

  protected:
    void classBegin() override;
    void componentComplete() override;

  private Q_SLOTS:
    void createdItem(int index, QObject *item);
    void initItem(int, QObject *item);
    void modelUpdated(const QQmlChangeSet &changeSet, bool reset);
};

#endif // DECLARATIVEREPEATER_P_H
