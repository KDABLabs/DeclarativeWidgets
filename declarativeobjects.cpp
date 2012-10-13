#include "declarativeobjects_p.h"

// DeclarativeObject
DeclarativeObject::DeclarativeObject(QObject *parent)
  : QObject(parent)
{
}

DeclarativeObject::~DeclarativeObject()
{
}

QDeclarativeListProperty<QObject> DeclarativeObject::data()
{
  return QDeclarativeListProperty<QObject>(this, 0, DeclarativeObject::data_append,
                                                    DeclarativeObject::data_count,
                                                    DeclarativeObject::data_at,
                                                    DeclarativeObject::data_clear);
}

void DeclarativeObject::dataAppend(QObject *)
{
}

int DeclarativeObject::dataCount()
{
  return 0;
}

QObject* DeclarativeObject::dataAt(int)
{
  return 0;
}

void DeclarativeObject::dataClear()
{
}

void DeclarativeObject::data_append(QDeclarativeListProperty<QObject> *property, QObject *object)
{
  if (!object)
    return;

  DeclarativeObject *that = qobject_cast<DeclarativeObject*>(property->object);
  that->dataAppend(object);
}

int DeclarativeObject::data_count(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObject *that = qobject_cast<DeclarativeObject*>(property->object);
  return that->dataCount();
}

QObject* DeclarativeObject::data_at(QDeclarativeListProperty<QObject> *property, int index)
{
  DeclarativeObject *that = qobject_cast<DeclarativeObject*>(property->object);
  return that->dataAt(index);
}

void DeclarativeObject::data_clear(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObject *that = qobject_cast<DeclarativeObject*>(property->object);
  that->dataClear();
}

// DeclarativeVBoxLayout
DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent)
  : DeclarativeObject(parent)
  , m_layout(0)
{
}

DeclarativeVBoxLayout::~DeclarativeVBoxLayout()
{
}

QObject* DeclarativeVBoxLayout::object()
{
  if (!m_layout)
    m_layout = new QVBoxLayout;

  return m_layout;
}

void DeclarativeVBoxLayout::dataAppend(QObject *object)
{
  DeclarativeWidget *widget = qobject_cast<DeclarativeWidget*>(object);
  DeclarativeVBoxLayout *layout = qobject_cast<DeclarativeVBoxLayout*>(object);

  if (widget) {
    m_children.append(object);
    qobject_cast<QVBoxLayout*>(this->object())->addWidget(qobject_cast<QWidget*>(widget->object()));
  } else if (layout) {
    m_children.append(object);
    qobject_cast<QVBoxLayout*>(this->object())->addLayout(qobject_cast<QVBoxLayout*>(layout->object()));
  } else {
    // TODO: error unknown type
  }
}

int DeclarativeVBoxLayout::dataCount()
{
  return m_children.count();
}

QObject* DeclarativeVBoxLayout::dataAt(int index)
{
  return m_children.at(index);
}

void DeclarativeVBoxLayout::dataClear()
{
  qDeleteAll(m_children);
  m_children.clear();
}

// DeclarativeWidget
DeclarativeWidget::DeclarativeWidget(QObject *parent)
  : DeclarativeObject(parent)
  , m_widget(0)
{
}

DeclarativeWidget::~DeclarativeWidget()
{
}

QObject* DeclarativeWidget::object()
{
  if (!m_widget)
    m_widget = new QWidget();

  return m_widget;
}

void DeclarativeWidget::dataAppend(QObject *object)
{
  DeclarativeWidget *widget = qobject_cast<DeclarativeWidget*>(object);
  DeclarativeVBoxLayout *layout = qobject_cast<DeclarativeVBoxLayout*>(object);

  if (widget) {
    // TODO: error when layout is set
    m_children.append(object);
    qobject_cast<QWidget*>(widget->object())->setParent(qobject_cast<QWidget*>(this->object()));
  } else if (layout) {
    // TODO: error when widget is set

    m_children.append(layout);
    qobject_cast<QWidget*>(this->object())->setLayout(qobject_cast<QVBoxLayout*>(layout->object()));
  } else {
    // TODO: error unknown type
  }
}

int DeclarativeWidget::dataCount()
{
  return m_children.count();
}

QObject *DeclarativeWidget::dataAt(int index)
{
  return m_children.at(index);
}

void DeclarativeWidget::dataClear()
{
  qDeleteAll(m_children);
  m_children.clear();
}

// DeclarativeLabel
DeclarativeLabel::DeclarativeLabel(QObject *parent)
  : DeclarativeWidget(parent)
  , m_label(0)
{
}

DeclarativeLabel::~DeclarativeLabel()
{
}

QObject* DeclarativeLabel::object()
{
  if (!m_label)
    m_label = new QLabel("Hello QML Widgets");

  return m_label;
}

// DeclarativeTabWidget
DeclarativeTabWidget::DeclarativeTabWidget(QObject *parent)
  : DeclarativeWidget(parent)
  , m_tabWidget(0)
{
}

QObject* DeclarativeTabWidget::object()
{
  if (!m_tabWidget)
    m_tabWidget = new QTabWidget();

  return m_tabWidget;
}

void DeclarativeTabWidget::dataAppend(QObject *object)
{
  DeclarativeWidget *widget = qobject_cast<DeclarativeWidget*>(object);

  if (widget) {
    // TODO: error when layout is set
    m_children.append(object);
    qobject_cast<QTabWidget*>(this->object())->addTab(qobject_cast<QWidget*>(widget->object()), "MyTab");
  } else {
    // TODO: error unknown type
  }
}

int DeclarativeTabWidget::dataCount()
{
  return m_children.count();
}

QObject *DeclarativeTabWidget::dataAt(int index)
{
  return m_children.at(index);
}

void DeclarativeTabWidget::dataClear()
{
  qDeleteAll(m_children);
  m_children.clear();
}
