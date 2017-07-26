/*
  Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Nathan Collins, nathan.collins@kdab.com

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

#include <QtTest>

#include <QLabel>
#include <QMainWindow>

#include <QQmlComponent>
#include <QQmlEngine>

class tst_QmlPlugins : public QObject
{
    Q_OBJECT

public:
    tst_QmlPlugins();

private slots:
    void qtWidgetsPlugin();

private:
    QQmlEngine* m_qmlEngine;

};

tst_QmlPlugins::tst_QmlPlugins()
    : QObject()
    , m_qmlEngine(new QQmlEngine(this))
{
    // Add extensionplugin import path
    m_qmlEngine->addImportPath(QStringLiteral("%1/../../../qml").arg(QCoreApplication::applicationDirPath()));
}

void tst_QmlPlugins::qtWidgetsPlugin()
{
    QQmlComponent component(m_qmlEngine);
    component.setData(QStringLiteral("import QtWidgets 1.0; MainWindow { width: 100; height: 100; Label { text:\"QtWidgets\" } }").toUtf8(), QUrl());

    QScopedPointer<QMainWindow> window(qobject_cast<QMainWindow*>(component.create()));
    QVERIFY(window);

    QLabel* label = qobject_cast<QLabel*>(window->centralWidget());
    QVERIFY(label);
}

QTEST_MAIN(tst_QmlPlugins)

#include "tst_qmlplugins.moc"
