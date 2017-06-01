#include <QObject>
#include <QtQml>
#include <QtTest/QtTest>

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

QTEST_MAIN(tst_DeclarativeView)

#include "tst_declarativeview.moc"