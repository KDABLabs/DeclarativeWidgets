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

#include <QDirIterator>
#include <QtQml>

class tst_InstantiateTypes : public QObject
{
    Q_OBJECT

public:
    tst_InstantiateTypes();

private slots:
    void initTestCase();
    void creatableTypes();
    void uncreatableTypes();

private:
    QQmlEngine* m_qmlEngine;

};

tst_InstantiateTypes::tst_InstantiateTypes()
    : QObject()
    , m_qmlEngine(new QQmlEngine(this))
{

}

void tst_InstantiateTypes::initTestCase()
{
    // Add extensionplugin import path
    m_qmlEngine->addImportPath(QStringLiteral("%1/../../../qml")
                               .arg(QCoreApplication::applicationDirPath()));
}

void tst_InstantiateTypes::creatableTypes()
{
    QDirIterator iterator(QStringLiteral(":/qml/creatable/"), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        QFileInfo fileInfo(iterator.next());
        if (fileInfo.isDir())
            continue;

        QUrl url = QUrl::fromLocalFile(fileInfo.filePath());

        auto printErrors = [](const QQmlComponent& component) {
            if (component.isError()) {
                for (auto error : component.errors())
                    QWARN(qPrintable(error.toString()));
            }
        };

        QQmlComponent component(m_qmlEngine, url);
        printErrors(component);
        QVERIFY2(component.status() == QQmlComponent::Ready,
                 qPrintable(QString("Failed to load \"%1\" (%2)")
                            .arg(url.toString())
                            .arg(component.status())));

        QSharedPointer<QObject> creatableWidget(component.create());
        printErrors(component);
        QVERIFY2(creatableWidget != nullptr,
                 qPrintable(QString("Failed to create \"%1\"")
                            .arg(url.toString())));
    }
}

void tst_InstantiateTypes::uncreatableTypes()
{
    QDirIterator iterator(QStringLiteral(":/qml/uncreatable/"));
    while (iterator.hasNext()) {
        QUrl url = QUrl::fromLocalFile(iterator.next());

        QQmlComponent component(m_qmlEngine, url);
        QVERIFY2(component.status() == QQmlComponent::Error,
                 qPrintable(QString("Should not be able to instantiate \"%1\" (%2)")
                            .arg(url.toString())
                            .arg(component.status())));

        QTest::ignoreMessage(QtWarningMsg, "QQmlComponent: Component is not ready");
        QSharedPointer<QObject> uncreatableWidget(component.create());
        QVERIFY2(uncreatableWidget == nullptr,
                 qPrintable(QString("Should not be able to create \"%1\"")
                            .arg(url.toString())));
    }
}

QTEST_MAIN(tst_InstantiateTypes)

#include "tst_instantiatetypes.moc"
