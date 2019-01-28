/*
  tst_qmlplugins.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2017-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Nathan Collins, nathan.collins@kdab.com

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
    void initTestCase();
    void qtWidgetsPlugin();

private:
    QQmlEngine* m_qmlEngine;

};

tst_QmlPlugins::tst_QmlPlugins()
    : QObject()
    , m_qmlEngine(new QQmlEngine(this))
{

}

void tst_QmlPlugins::initTestCase()
{
    // Add QtWidgets QML plugin import path
    const QString importPath(PLUGIN_IMPORT_PATH);
    QVERIFY2(QFileInfo::exists(importPath),
             qPrintable(QStringLiteral("QtWidgets QML plugin import path does not exist: %1").
                        arg(importPath)));
    m_qmlEngine->addImportPath(importPath);
}

void tst_QmlPlugins::qtWidgetsPlugin()
{
    QQmlComponent component(m_qmlEngine);
    component.setData(QStringLiteral("import QtWidgets 1.0; MainWindow { width: 100; height: 100; Label { text:\"QtWidgets\" } }").toUtf8(), QUrl());
    if (component.isError()) {
        for (auto error : component.errors()) {
            QWARN(qPrintable(error.toString()));
        }
    }
    QVERIFY(component.isReady());
    QScopedPointer<QMainWindow> window(qobject_cast<QMainWindow*>(component.create()));
    QVERIFY(window);

    QLabel* label = qobject_cast<QLabel*>(window->centralWidget());
    QVERIFY(label);
}

QTEST_MAIN(tst_QmlPlugins)

#include "tst_qmlplugins.moc"
