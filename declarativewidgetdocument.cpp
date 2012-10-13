#include "declarativewidgetdocument.h"

#include "declarativeobjects_p.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeEngine>

class DeclarativeWidgetDocument::Private
{
  public:
    Private(DeclarativeWidgetDocument *qq, const QUrl &url)
      : q(qq)
      , m_url(url)
      , m_engine(new QDeclarativeEngine(q))
      , m_component(new QDeclarativeComponent(m_engine, q))
    {
    }

    DeclarativeWidgetDocument* q;
    QUrl m_url;
    QDeclarativeEngine* m_engine;
    QDeclarativeComponent* m_component;
};

DeclarativeWidgetDocument::DeclarativeWidgetDocument(const QUrl &url, QObject *parent)
  : QObject(parent)
  , d(new Private(this, url))
{
  qmlRegisterType<DeclarativeWidget>("qtgui.widgets", 1, 0, "Widget");
  qmlRegisterType<DeclarativeLabel>("qtgui.widgets", 1, 0, "Label");
  qmlRegisterType<DeclarativeVBoxLayout>("qtgui.widgets", 1, 0, "VBoxLayout");
  qmlRegisterType<DeclarativeTabWidget>("qtgui.widgets", 1, 0, "TabWidget");
  d->m_component->loadUrl(d->m_url);
  if (d->m_component->isError()) {
    foreach (const QDeclarativeError &error, d->m_component->errors())
      qDebug() << error.toString();
  }
}

DeclarativeWidgetDocument::~DeclarativeWidgetDocument()
{
  delete d;
}

QWidget* DeclarativeWidgetDocument::createWidget()
{
  QObject *object = d->m_component->create();
  if (!object) {
    qWarning("Unable to create component");
    return 0;
  }

  DeclarativeObject *declarativeObject = qobject_cast<DeclarativeObject*>(object);
  if (!declarativeObject) {
    qWarning("Root element is no DeclarativeObject subclass");
    return 0;
  }

  declarativeObject->setParent(this);

  return qobject_cast<QWidget*>(declarativeObject->object());
}
