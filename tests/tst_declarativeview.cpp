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

#include <QObject>
#include <QtQml>
#include <QtTest/QtTest>

#include <QQuickItem>
#include <QQuickWidget>

#include "declarativeqmlcontext_p.h"
#include "declarativequickwidgetextension_p.h"

class tst_DeclarativeView : public QObject
{
    Q_OBJECT
public:
    tst_DeclarativeView();

private slots:
    void instantiateQQuickWidget();
    void instantiateQQuickWidgetWithContext();
    void instantiateQQuickWidgetWithContextProperty();
};

tst_DeclarativeView::tst_DeclarativeView()
{
    qmlRegisterType<DeclarativeQmlContextProperty>("Qt.Widgets", 1, 0, "QmlContextProperty");
    qmlRegisterType<DeclarativeQmlContext>("Qt.Widgets", 1, 0, "QmlContext");

    qmlRegisterExtendedType<QQuickWidget, DeclarativeQuickWidgetExtension>("Qt.Widgets", 1, 0, "QuickWidget");
}

void tst_DeclarativeView::instantiateQQuickWidget()
{
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData("import Qt.Widgets 1.0;\n"
                      "QuickWidget { \n"
                      "    source: \"qrc:///rectangle.qml\"\n"
                      "}", QUrl());
    QScopedPointer<QObject> object(component.create());
    QVERIFY(!object.isNull());

    QQuickWidget *rootView = qobject_cast<QQuickWidget*>(object.data());
    QVERIFY(rootView != nullptr);

    QQuickItem *rootItem = rootView->rootObject();
    QVERIFY(rootItem != nullptr);
}

void tst_DeclarativeView::instantiateQQuickWidgetWithContext()
{
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData("import Qt.Widgets 1.0;\n"
                      "QuickWidget { \n"
                      "    source: \"qrc:///rectangle.qml\"\n"
                      "    rootContext: QmlContext { }"
                      "}", QUrl());
    {
        QScopedPointer<QObject> object(component.create());
        QVERIFY(!object.isNull());

        QQuickWidget *rootView = qobject_cast<QQuickWidget*>(object.data());
        QVERIFY(rootView != nullptr);
    }

    // Verify that the root context hasn't been deleted when the created object is deleted
    QVERIFY(engine.rootContext() != nullptr);
}

void tst_DeclarativeView::instantiateQQuickWidgetWithContextProperty()
{
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData("import Qt.Widgets 1.0;\n"
                      "QuickWidget { \n"
                      "    source: \"qrc:///rectangle-context.qml\"\n"
                      "    rootContext: QmlContext {\n"
                      "        QmlContextProperty {\n"
                      "            name: \"_colour\"\n"
                      "            value: \"lightblue\"\n"
                      "        }\n"
                      "    }\n"
                      "}", QUrl());
    QScopedPointer<QObject> object(component.create());
    QVERIFY(!object.isNull());

    QQuickWidget *rootView = qobject_cast<QQuickWidget*>(object.data());
    QVERIFY(rootView != nullptr);

    QQuickItem *rootItem = rootView->rootObject();
    QVERIFY(rootItem != nullptr);

    QQmlContext *context = QQmlEngine::contextForObject(rootItem);
    QVERIFY(context != nullptr);

    QVariant contextProperty = context->contextProperty(QStringLiteral("_colour"));
    QVERIFY(!contextProperty.isNull() && contextProperty.isValid());
}

QTEST_MAIN(tst_DeclarativeView)

#include "tst_declarativeview.moc"
