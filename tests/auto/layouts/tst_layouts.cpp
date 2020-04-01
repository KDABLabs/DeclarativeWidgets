/*
  tst_layouts.cpp

  This file is part of DeclarativeWidgets, library and tools for creating QtWidget UIs with QML.

  Copyright (C) 2017-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include <QtTest>

#include "hboxlayoutwidget.h"
#include "vboxlayoutwidget.h"
#include "formlayoutwidget.h"
#include "gridlayoutwidget.h"
#include "stackedlayoutwidget.h"
#include "stackedwidget.h"

#include <QFormLayout>
#include <QLayout>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QSizePolicy>

typedef QSharedPointer<QWidget> QWidgetPtr;
Q_DECLARE_METATYPE(QWidgetPtr)

class tst_Layouts : public QObject
{
    Q_OBJECT
public:
    tst_Layouts();

private slots:
    void initTestCase();
    void hBoxLayout_data();
    void hBoxLayout();
    void vBoxLayout_data();
    void vBoxLayout();
    void formLayout_data();
    void formLayout();
    void gridLayout_data();
    void gridLayout();
    void stackedLayout_data();
    void stackedLayout();
    void stackedWidget_data();
    void stackedWidget();
    void sizePolicy_data();
    void sizePolicy();

private:
    QQmlEngine* m_qmlEngine;

    void testLayouts(QWidgetPtr uiWidget, QWidgetPtr declarativeWidget);
    void compareLayouts(QLayout *a, QLayout *b);
    void compareLayoutItems(QLayoutItem* a, QLayoutItem* b);
    void compareWidgets(QWidget* a, QWidget* b);
    void compareGeometry(const QRect& a, const QRect& b);
    void compareSizePolicy(const QSizePolicy& aPolicy, const QSizePolicy& bPolicy);
};

tst_Layouts::tst_Layouts()
    : QObject()
    , m_qmlEngine(new QQmlEngine(this))
{

}

void tst_Layouts::initTestCase()
{
    // Add QtWidgets QML plugin import path
    const QString importPath(PLUGIN_IMPORT_PATH);
    QVERIFY2(QFileInfo::exists(importPath),
             qPrintable(QStringLiteral("QtWidgets QML plugin import path does not exist: %1").
                        arg(importPath)));
    m_qmlEngine->addImportPath(importPath);
}

void tst_Layouts::hBoxLayout_data()
{
    QQmlComponent component(m_qmlEngine, QUrl(QStringLiteral("qrc:/qml/HBoxLayoutTest.qml")));
    QWidgetPtr declarativeWidget( qobject_cast<QWidget *>(component.create()));
    QVERIFY(declarativeWidget != nullptr);

    QTest::addColumn<QWidgetPtr>("uiWidget");
    QTest::addColumn<QWidgetPtr>("declarativeWidget");

    QTest::newRow("hBoxLayout") << QWidgetPtr(new HBoxLayoutWidget()) << declarativeWidget;
}

void tst_Layouts::hBoxLayout()
{
    QFETCH(QWidgetPtr, uiWidget);
    QFETCH(QWidgetPtr, declarativeWidget);

    testLayouts(uiWidget, declarativeWidget);
}

void tst_Layouts::vBoxLayout_data()
{
    QQmlComponent component(m_qmlEngine, QUrl(QStringLiteral("qrc:/qml/VBoxLayoutTest.qml")));
    QWidgetPtr declarativeWidget( qobject_cast<QWidget *>(component.create()));
    QVERIFY(declarativeWidget != nullptr);

    QTest::addColumn<QWidgetPtr>("uiWidget");
    QTest::addColumn<QWidgetPtr>("declarativeWidget");

    QTest::newRow("vBoxLayout") << QWidgetPtr(new VBoxLayoutWidget()) << declarativeWidget;
}

void tst_Layouts::vBoxLayout()
{
    QFETCH(QWidgetPtr, uiWidget);
    QFETCH(QWidgetPtr, declarativeWidget);

    testLayouts(uiWidget, declarativeWidget);
}

void tst_Layouts::formLayout_data()
{
    QQmlComponent component(m_qmlEngine, QUrl(QStringLiteral("qrc:/qml/FormLayoutTest.qml")));
    QWidgetPtr declarativeWidget( qobject_cast<QWidget *>(component.create()));
    QVERIFY(declarativeWidget != nullptr);

    QTest::addColumn<QWidgetPtr>("uiWidget");
    QTest::addColumn<QWidgetPtr>("declarativeWidget");

    QTest::newRow("formLayout") << QWidgetPtr(new FormLayoutWidget()) << declarativeWidget;
}

void tst_Layouts::formLayout()
{
    QFETCH(QWidgetPtr, uiWidget);
    QFETCH(QWidgetPtr, declarativeWidget);

    testLayouts(uiWidget, declarativeWidget);
}

void tst_Layouts::gridLayout_data()
{
    QQmlComponent component(m_qmlEngine, QUrl(QStringLiteral("qrc:/qml/GridLayoutTest.qml")));
    QWidgetPtr declarativeWidget( qobject_cast<QWidget *>(component.create()));
    QVERIFY(declarativeWidget != nullptr);

    QTest::addColumn<QWidgetPtr>("uiWidget");
    QTest::addColumn<QWidgetPtr>("declarativeWidget");

    QTest::newRow("gridLayout") << QWidgetPtr(new GridLayoutWidget()) << declarativeWidget;
}

void tst_Layouts::gridLayout()
{
    QFETCH(QWidgetPtr, uiWidget);
    QFETCH(QWidgetPtr, declarativeWidget);

    testLayouts(uiWidget, declarativeWidget);
}

void tst_Layouts::stackedLayout_data()
{
    QQmlComponent component(m_qmlEngine, QUrl(QStringLiteral("qrc:/qml/StackedLayoutTest.qml")));
    QWidgetPtr declarativeWidget( qobject_cast<QWidget *>(component.create()));
    QVERIFY(declarativeWidget != nullptr);

    QTest::addColumn<QWidgetPtr>("uiWidget");
    QTest::addColumn<QWidgetPtr>("declarativeWidget");

    QTest::newRow("stackedLayout") << QWidgetPtr(new StackedLayoutWidget()) << declarativeWidget;
}

void tst_Layouts::stackedLayout()
{
    QFETCH(QWidgetPtr, uiWidget);
    QFETCH(QWidgetPtr, declarativeWidget);

    testLayouts(uiWidget, declarativeWidget);
}

void tst_Layouts::stackedWidget_data()
{
    QQmlComponent component(m_qmlEngine, QUrl(QStringLiteral("qrc:/qml/StackedWidgetTest.qml")));
    QWidgetPtr declarativeWidget( qobject_cast<QWidget *>(component.create()));
    QVERIFY(declarativeWidget != nullptr);

    QTest::addColumn<QWidgetPtr>("uiWidget");
    QTest::addColumn<QWidgetPtr>("declarativeWidget");

    QTest::newRow("stackedWidget") << QWidgetPtr(new StackedWidget()) << declarativeWidget;
}

void tst_Layouts::stackedWidget()
{
    QFETCH(QWidgetPtr, uiWidget);
    QFETCH(QWidgetPtr, declarativeWidget);

    testLayouts(uiWidget, declarativeWidget);
}

void tst_Layouts::sizePolicy_data()
{
    // QSizePolicy::ControlType is not registered with the meta-type system.
    QTest::addColumn<int>("controlType");
    QTest::addColumn<QSizePolicy::Policy>("horizontalPolicy");
    QTest::addColumn<QSizePolicy::Policy>("verticalPolicy");
    QTest::addColumn<bool>("hasHeightForWidth");
    QTest::addColumn<bool>("hasWidthForHeight");
    QTest::addColumn<int>("horizontalStretch");
    QTest::addColumn<int>("verticalStretch");
    QTest::addColumn<bool>("retainSizeWhenHidden");

    QTest::addColumn<QString>("declarativeControlType");
    QTest::addColumn<QString>("declarativeHorizontalPolicy");
    QTest::addColumn<QString>("declarativeVerticalPolicy");

    QTest::newRow("Default") << (int) QSizePolicy::DefaultType << QSizePolicy::Fixed << QSizePolicy::Fixed << false << false << 0 << 0 << false
                       << "SizePolicy.DefaultType" << "SizePolicy.Fixed" << "SizePolicy.Fixed";
    QTest::newRow("Control Type") << (int) QSizePolicy::ToolButton << QSizePolicy::Fixed << QSizePolicy::Fixed << false << false << 0 << 0 << false
                       << "SizePolicy.ToolButton" << "SizePolicy.Fixed" << "SizePolicy.Fixed";
    QTest::newRow("Horizontal Policy") << (int) QSizePolicy::DefaultType << QSizePolicy::Ignored << QSizePolicy::Fixed << false << false << 0 << 0 << false
                       << "SizePolicy.DefaultType" << "SizePolicy.Ignored" << "SizePolicy.Fixed";
    QTest::newRow("Vertical Policy") << (int) QSizePolicy::DefaultType << QSizePolicy::Fixed << QSizePolicy::Ignored << false << false << 0 << 0 << false
                       << "SizePolicy.DefaultType" << "SizePolicy.Fixed" << "SizePolicy.Ignored";
    QTest::newRow("hasHeightForWidth") << (int) QSizePolicy::DefaultType << QSizePolicy::Fixed << QSizePolicy::Fixed << true << false << 0 << 0 << false
                       << "SizePolicy.DefaultType" << "SizePolicy.Fixed" << "SizePolicy.Fixed";
    QTest::newRow("hasWidthForHeight") << (int) QSizePolicy::DefaultType << QSizePolicy::Fixed << QSizePolicy::Fixed << false << true << 0 << 0 << false
                       << "SizePolicy.DefaultType" << "SizePolicy.Fixed" << "SizePolicy.Fixed";
    QTest::newRow("Horizontal Stretch") << (int) QSizePolicy::DefaultType << QSizePolicy::Fixed << QSizePolicy::Fixed << false << false << 255 << 0 << false
                       << "SizePolicy.DefaultType" << "SizePolicy.Fixed" << "SizePolicy.Fixed";
    QTest::newRow("Vertical Stretch") << (int) QSizePolicy::DefaultType << QSizePolicy::Fixed << QSizePolicy::Fixed << false << false << 0 << 255 << false
                       << "SizePolicy.DefaultType" << "SizePolicy.Fixed" << "SizePolicy.Fixed";
    QTest::newRow("retainSizeWhenHidden") << (int) QSizePolicy::DefaultType << QSizePolicy::Fixed << QSizePolicy::Fixed << false << false << 0 << 0 << true
                       << "SizePolicy.DefaultType" << "SizePolicy.Fixed" << "SizePolicy.Fixed";
}

void tst_Layouts::sizePolicy()
{
    auto printErrors = [](const QQmlComponent &component) {
        if (component.isError()) {
            for (auto error : component.errors()) {
                QWARN(qPrintable(error.toString()));
            }
        }
    };

    QFETCH(int, controlType);
    QFETCH(QSizePolicy::Policy, horizontalPolicy);
    QFETCH(QSizePolicy::Policy, verticalPolicy);
    QFETCH(bool, hasHeightForWidth);
    QFETCH(bool, hasWidthForHeight);
    QFETCH(int, horizontalStretch);
    QFETCH(int, verticalStretch);
    QFETCH(bool, retainSizeWhenHidden);

    QFETCH(QString, declarativeControlType);
    QFETCH(QString, declarativeHorizontalPolicy);
    QFETCH(QString, declarativeVerticalPolicy);

    QSizePolicy aPolicy(horizontalPolicy, verticalPolicy, (QSizePolicy::ControlType) controlType);
    aPolicy.setHeightForWidth(hasHeightForWidth);
    aPolicy.setWidthForHeight(hasWidthForHeight);
    aPolicy.setHorizontalStretch(horizontalStretch);
    aPolicy.setVerticalStretch(verticalStretch);
    aPolicy.setRetainSizeWhenHidden(retainSizeWhenHidden);

    QString declarativePolicy =
QStringLiteral(R"(
sizePolicy {
    controlType: %1
    horizontalPolicy: %2
    verticalPolicy: %3
    hasHeightForWidth: %4
    hasWidthForHeight: %5
    horizontalStretch: %6
    verticalStretch: %7
    retainSizeWhenHidden: %8
})")
            .arg(declarativeControlType)
            .arg(declarativeHorizontalPolicy)
            .arg(declarativeVerticalPolicy)
            .arg(hasHeightForWidth ? "true" : "false")
            .arg(hasWidthForHeight ? "true" : "false")
            .arg(horizontalStretch)
            .arg(verticalStretch)
            .arg(retainSizeWhenHidden ? "true" : "false");

    QQmlComponent component(m_qmlEngine);
    component.setData(
                QStringLiteral("import QtWidgets 1.0; Widget { %1 }")
                .arg(declarativePolicy).toUtf8()
                , QUrl());
    printErrors(component);

    QScopedPointer<QWidget> widget(qobject_cast<QWidget*>(component.create()));
    QVERIFY(!widget.isNull());

    QSizePolicy bPolicy = widget->sizePolicy();

    compareSizePolicy(aPolicy, bPolicy);
}

void tst_Layouts::testLayouts(QWidgetPtr uiWidget, QWidgetPtr declarativeWidget)
{
    QVERIFY(uiWidget != nullptr);
    QVERIFY(declarativeWidget != nullptr);

    // Show the widgets to trigger geometry updates
    uiWidget->show();
    declarativeWidget->show();

    // Compare the widgets
    compareWidgets(uiWidget.data(), declarativeWidget.data());
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
    QVERIFY2(b->metaObject()->inherits(a->metaObject()),
             qPrintable(QStringLiteral("Expected layouts to derive from the same type (%2 from %1)")
                        .arg(a->metaObject()->className())
                        .arg(b->metaObject()->className())));

    // Verify that the layouts have a matching number of children
    QVERIFY2(a->count() == b->count(),
             qPrintable(QStringLiteral("Widgets do not have the same number of children (%1 != %2)")
                        .arg(a->count())
                        .arg(b->count())));

    // Verify the layout items
    // Items get added to a declarative QFormLayout in a different order, due
    // to the FormLayout.label attached property. Make sure we inspect the rows,
    // not the arbitrary order in which things were added.
    if (auto formA = qobject_cast<QFormLayout*>(a)) {
        auto formB = qobject_cast<QFormLayout*>(b);
        QVERIFY2(formB != nullptr, "Expected b to be a QFormLayout");

        // Verify that the layouts have a matching number of children
        QVERIFY2(formA->rowCount() == formB->rowCount(),
                 qPrintable(QStringLiteral("QFormLayouts do not have the same number of rows (%1 != %2)")
                            .arg(formA->rowCount())
                            .arg(formB->rowCount())));

        for (int i = 0; i < formA->rowCount() && !QTest::currentTestFailed(); ++i) {
            compareLayoutItems(formA->itemAt(i, QFormLayout::LabelRole), formB->itemAt(i, QFormLayout::LabelRole));
            compareLayoutItems(formA->itemAt(i, QFormLayout::FieldRole), formB->itemAt(i, QFormLayout::FieldRole));
        }
    } else {
        for (int i = 0; i < a->count() && !QTest::currentTestFailed(); ++i)
            compareLayoutItems(a->itemAt(i), b->itemAt(i));
    }

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
    QVERIFY2(a->alignment() == b->alignment(),
             qPrintable(QStringLiteral("Expected QLayoutItems to have matching alignment (%1 != %2)")
                        .arg(a->alignment())
                        .arg(b->alignment())));
    QVERIFY2(a->expandingDirections() == b->expandingDirections(),
             qPrintable(QStringLiteral("Expected matching expanding directions (%1 != %2)")
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

    compareSizePolicy(a->sizePolicy(), b->sizePolicy());
    compareLayouts(a->layout(), b->layout());
    compareGeometry(a->geometry(), b->geometry());
}

void tst_Layouts::compareGeometry(const QRect &a, const QRect &b)
{
    if (QTest::currentTestFailed())
        return;

    QVERIFY2(a.x() == b.x(),
             qPrintable(QStringLiteral("Geometries do not have the same x coordinate (%1 != %2)")
                        .arg(a.x())
                        .arg(b.x())));
    QVERIFY2(a.y() == b.y(),
             qPrintable(QStringLiteral("Geometries do not have the same y coordinate (%1 != %2)")
                        .arg(a.y())
                        .arg(b.y())));
    QVERIFY2(a.width() == b.width(),
             qPrintable(QStringLiteral("Geometries do not have the same width (%1 != %2)")
                        .arg(a.width())
                        .arg(b.width())));
    QVERIFY2(a.height() == b.height(),
             qPrintable(QStringLiteral("Geometries do not have the same height (%1 != %2)")
                        .arg(a.height())
                        .arg(b.height())));
}

void tst_Layouts::compareSizePolicy(const QSizePolicy& aPolicy, const QSizePolicy& bPolicy)
{
    QVERIFY2(aPolicy.expandingDirections() == bPolicy.expandingDirections()
             , qPrintable(QStringLiteral("Expanding directions do not match (%1 != %2")
                          .arg(aPolicy.expandingDirections())
                          .arg(bPolicy.expandingDirections())));
    QVERIFY2(aPolicy.hasHeightForWidth() == bPolicy.hasHeightForWidth()
             , qPrintable(QStringLiteral("hasHeightForWidth does not match (%1 != %2")
                          .arg(aPolicy.hasHeightForWidth())
                          .arg(bPolicy.hasHeightForWidth())));
    QVERIFY2(aPolicy.hasWidthForHeight() == bPolicy.hasWidthForHeight()
             , qPrintable(QStringLiteral("hasWidthForHeight does not match (%1 != %2")
                          .arg(aPolicy.hasWidthForHeight())
                          .arg(bPolicy.hasWidthForHeight())));
    QVERIFY2(aPolicy.horizontalPolicy() == bPolicy.horizontalPolicy()
             , qPrintable(QStringLiteral("horizontalPolicy does not match (%1 != %2")
                          .arg(aPolicy.horizontalPolicy())
                          .arg(bPolicy.horizontalPolicy())));
    QVERIFY2(aPolicy.horizontalStretch() == bPolicy.horizontalStretch()
             , qPrintable(QStringLiteral("horizontalStretch does not match (%1 != %2")
                          .arg(aPolicy.horizontalStretch())
                          .arg(bPolicy.horizontalStretch())));
    QVERIFY2(aPolicy.horizontalStretch() == bPolicy.horizontalStretch()
             , qPrintable(QStringLiteral("horizontalStretch does not match (%1 != %2")
                          .arg(aPolicy.horizontalStretch())
                          .arg(bPolicy.horizontalStretch())));
    QVERIFY2(aPolicy.retainSizeWhenHidden() == bPolicy.retainSizeWhenHidden()
             , qPrintable(QStringLiteral("retainSizeWhenHidden does not match (%1 != %2")
                          .arg(aPolicy.retainSizeWhenHidden())
                          .arg(bPolicy.retainSizeWhenHidden())));
    QVERIFY2(aPolicy.verticalPolicy() == bPolicy.verticalPolicy()
             , qPrintable(QStringLiteral("verticalPolicy does not match (%1 != %2")
                          .arg(aPolicy.verticalPolicy())
                          .arg(bPolicy.verticalPolicy())));
    QVERIFY2(aPolicy.verticalStretch() == bPolicy.verticalStretch()
             , qPrintable(QStringLiteral("verticalStretch does not match (%1 != %2")
                          .arg(aPolicy.verticalStretch())
                          .arg(bPolicy.verticalStretch())));
    // Tests may fail here due to [QTBUG-66747] uic generates incorrect code to set QSizePolicy
    QVERIFY2(aPolicy.controlType() == bPolicy.controlType()
             , qPrintable(QStringLiteral("controlType does not match (%1 != %2")
                          .arg(aPolicy.controlType())
                          .arg(bPolicy.controlType())));
    QVERIFY2(aPolicy == bPolicy, "Expected size policy to match");
}

QTEST_MAIN(tst_Layouts)

#include "tst_layouts.moc"
