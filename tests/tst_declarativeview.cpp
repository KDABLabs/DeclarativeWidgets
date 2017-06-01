#include <QObject>
#include <QtQml>
#include <QtTest/QtTest>

#include <QQuickItem>
#include <QQuickWidget>

#include "declarativedeclarativecontext_p.h"
#include "declarativedeclarativeviewextension_p.h"

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
    qmlRegisterType<DeclarativeContextProperty>("Qt.Widgets", 1, 0, "DeclarativeContextProperty");
    qmlRegisterType<DeclarativeDeclarativeContext>("Qt.Widgets", 1, 0, "DeclarativeContext");

    qmlRegisterExtendedType<QQuickWidget, DeclarativeDeclarativeViewExtension>("Qt.Widgets", 1, 0, "DeclarativeView");
}

void tst_DeclarativeView::instantiateQQuickWidget()
{
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData("import Qt.Widgets 1.0;\n"
                      "DeclarativeView { \n"
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
                      "DeclarativeView { \n"
                      "    source: \"qrc:///rectangle.qml\"\n"
                      "    rootContext: DeclarativeContext { }"
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
                      "DeclarativeView { \n"
                      "    source: \"qrc:///rectangle.qml\"\n"
                      "    rootContext: DeclarativeContext {\n"
                      "        DeclarativeContextProperty {\n"
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
