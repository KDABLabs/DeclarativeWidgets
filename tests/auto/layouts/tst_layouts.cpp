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

#include "hboxlayoutwidget.h"
#include "vboxlayoutwidget.h"

#include "declarativewidgetsdocument.h"

#include <QLayout>

class tst_Layouts : public QObject
{
    Q_OBJECT
public:
    tst_Layouts();

private slots:
    void hBoxLayout();
    void vBoxLayout();

private:
    void compareLayouts(QLayout *a, QLayout *b);
    void compareLayoutItems(QLayoutItem* a, QLayoutItem* b);
    void compareWidgets(QWidget* a, QWidget* b);
    void compareGeometry(const QRect& a, const QRect& b);
};

tst_Layouts::tst_Layouts()
    : QObject()
{

}

void tst_Layouts::hBoxLayout()
{
    HBoxLayoutWidget* uiWidget = new HBoxLayoutWidget();

    DeclarativeWidgetsDocument* document = new DeclarativeWidgetsDocument(QStringLiteral("qrc:/qml/HBoxLayoutTest.qml"), this);
    QWidget* declarativeWidget = document->create<QWidget>();

    QVERIFY2(declarativeWidget != nullptr, "Failed to create widget from document");

    // Show the widgets to trigger geometry updates
    uiWidget->show();
    declarativeWidget->show();

    // Compare the widgets
    compareWidgets(uiWidget, declarativeWidget);
}

void tst_Layouts::vBoxLayout()
{
    VBoxLayoutWidget* uiWidget = new VBoxLayoutWidget();

    DeclarativeWidgetsDocument* document = new DeclarativeWidgetsDocument(QStringLiteral("qrc:/qml/VBoxLayoutTest.qml"), this);
    QWidget* declarativeWidget = document->create<QWidget>();

    QVERIFY2(declarativeWidget != nullptr, "Failed to create widget from document");

    // Show the widgets to trigger geometry updates
    uiWidget->show();
    declarativeWidget->show();

    // Compare the widgets
    compareWidgets(uiWidget, declarativeWidget);
}

void tst_Layouts::compareLayouts(QLayout *a, QLayout *b)
{
    if (QTest::currentTestFailed())
        return;

    if (a == nullptr) {
        QVERIFY2(b == nullptr, "Expected b QLayout to be a nullptr");
        return;
    }

    QVERIFY2(b != nullptr, "Expected b QLayout to be a valid pointer");

    // Verify matching super-classes
    // Expects b to be the declarative layout
    // Expects declarative layouts to derive from the non-declarative type
    QVERIFY2(b->metaObject()->inherits(a->metaObject())
             , qPrintable(QStringLiteral("Expected layouts to derive from the same type (%2 from %1)")
                          .arg(a->metaObject()->className())
                          .arg(b->metaObject()->className())));

    // Verify that the layouts have a matching number of children
    QVERIFY2(a->count() == b->count()
             , qPrintable(QStringLiteral("Widgets do not have the same number of children (%1 != %2)")
                          .arg(a->count())
                          .arg(b->count())));

    // Verify the layout items
    for (int i = 0; i < a->count() && !QTest::currentTestFailed(); ++i)
        compareLayoutItems(a->itemAt(i), b->itemAt(i));

    // Verify that the layout geometries are equal
    compareGeometry(a->geometry(), b->geometry());
}

void tst_Layouts::compareLayoutItems(QLayoutItem *a, QLayoutItem *b)
{
    if (QTest::currentTestFailed())
        return;

    QVERIFY2(a != nullptr, "a QLayoutItem is null");
    QVERIFY2(b != nullptr, "b QLayoutItem is null");

    if (a->isEmpty()) {
        QVERIFY2(b->isEmpty(), "Expected b QLayoutItem to be empty");
        return;
    }

    QVERIFY2(!b->isEmpty(), "Expected b QLayoutItem not to be empty");

    // Verify that the layout items have matching generic properties
    QVERIFY2(a->alignment() == b->alignment()
             , qPrintable(QStringLiteral("Expected QLayoutItems to have matching alignment (%1 != %2)")
                          .arg(a->alignment())
                          .arg(b->alignment())));
    QVERIFY2(a->expandingDirections() == b->expandingDirections()
             , qPrintable(QStringLiteral("Expected matching expanding directions (%1 != %2)")
                          .arg(a->expandingDirections())
                          .arg(b->expandingDirections())));

    // Verify that the layout item contents match
    if (a->widget() != nullptr) {
        QVERIFY2(b->widget() != nullptr, "Expected b QLayoutItem to manage a QWidget");
        compareWidgets(a->widget(), b->widget());
    } else if (a->layout() != nullptr) {
        QVERIFY2(b->layout() != nullptr, "Expected b QLayoutItem to manage a QLayout");
        compareLayouts(a->layout(), b->layout());
    } else if (a->spacerItem() != nullptr) {
        QVERIFY2(b->spacerItem() != nullptr, "Expected b QLayoutItem to manage a QSpacerItem");
        compareGeometry(a->spacerItem()->geometry(), b->spacerItem()->geometry());
    } else {
        QVERIFY2(false, "a QLayoutItem manages unhandled type");
    }
}

void tst_Layouts::compareWidgets(QWidget *a, QWidget *b)
{
    if (QTest::currentTestFailed())
        return;

    QVERIFY2(a != nullptr, "a QWidget is null");
    QVERIFY2(b != nullptr, "b QWidget is null");

    compareLayouts(a->layout(), b->layout());
    compareGeometry(a->geometry(), b->geometry());
}

void tst_Layouts::compareGeometry(const QRect &a, const QRect &b)
{
    if (QTest::currentTestFailed())
        return;

    QVERIFY2(a.x() == b.x()
             , qPrintable(QStringLiteral("Geometries do not have the same x coordinate (%1 != %2)")
                          .arg(a.x())
                          .arg(b.x())));
    QVERIFY2(a.y() == b.y()
             , qPrintable(QStringLiteral("Geometries do not have the same y coordinate (%1 != %2)")
                          .arg(a.y())
                          .arg(b.y())));
    QVERIFY2(a.width() == b.width()
             , qPrintable(QStringLiteral("Geometries do not have the same width (%1 != %2)")
                          .arg(a.width())
                          .arg(b.width())));
    QVERIFY2(a.height() == b.height()
             , qPrintable(QStringLiteral("Geometries do not have the same height (%1 != %2)")
                          .arg(a.height())
                          .arg(b.height())));
}

QTEST_MAIN(tst_Layouts)

#include "tst_layouts.moc"
