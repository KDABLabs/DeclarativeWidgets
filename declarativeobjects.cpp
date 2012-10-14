#include "declarativeobjects_p.h"

#include "qmetaobjectbuilder_p.h"

#include <QDebug>

#define CUSTOM_METAOBJECT(ClassName, BaseType, WidgetType, WidgetVariable) \
QMetaObject ClassName::staticMetaObject;\
bool ClassName::metaObjectInitialized = ClassName::initializeMetaObject(); \
bool ClassName::initializeMetaObject() \
{ \
  QMetaObjectBuilder builder; \
  const QMetaObject *mo = &WidgetType::staticMetaObject; \
  builder.addMetaObject(mo); \
  builder.addMetaObject(&DeclarativeObject::staticMetaObject); \
  builder.setSuperClass(WidgetType::staticMetaObject.superClass()); \
  builder.setClassName(""#ClassName); \
  QMetaObject *mo2 = builder.toMetaObject(); \
  ClassName::staticMetaObject = *mo2; \
  if (QString(staticMetaObject.className()) == "DeclarativeLabel") { \
    qDebug("class: %s propOffset: %d", qPrintable(staticMetaObject.className()), staticMetaObject.propertyOffset()); \
    for (int i = 0; i < staticMetaObject.propertyCount(); ++i) { \
      qDebug("  prop: %d=%s", i, staticMetaObject.property(i).name()); \
    } \
    qDebug("class: DeclarativeObject"); \
    for (int i = 0; i < DeclarativeObject::staticMetaObject.propertyCount(); ++i) { \
      qDebug("  prop: %d=%s", i, DeclarativeObject::staticMetaObject.property(i).name()); \
    } \
  } \
  return true; \
} \
const QMetaObject &ClassName::getStaticMetaObject() \
{ \
  return ClassName::staticMetaObject; \
} \
const QMetaObject* ClassName::metaObject() const \
{ \
  return &ClassName::staticMetaObject; \
} \
void* ClassName::qt_metacast(const char *name) \
{ \
  return 0; \
} \
int ClassName::qt_metacall(QMetaObject::Call call, int id, void **argv) \
{ \
  qDebug("%s call=%d id=%d", staticMetaObject.className(), call, id); \
  if (call == QMetaObject::ReadProperty || call == QMetaObject::WriteProperty) { \
    if (id >= WidgetType::staticMetaObject.propertyCount()) { \
      qDebug() << "dobject" << this << id << (id - WidgetType::staticMetaObject.propertyCount() + 1); \
      id = DeclarativeObject::qt_metacall(call, id - WidgetType::staticMetaObject.propertyCount() + 1, argv); \
      qDebug() << "after" << id; \
      id += WidgetType::staticMetaObject.propertyCount() - 1; \
    } else { \
      qDebug() << "widget" << WidgetVariable << id; \
      WidgetVariable->qt_metacall(call, id, argv); \
      qDebug() << "after" << id; \
      id -= 1; \
    } \
    if (id < 0) \
      return 0; \
  } \
  return id; \
}

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
  qDebug("tokoe: 1");
  if (!object)
    return;

  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  that->dataAppend(object);
}

int DeclarativeObject::data_count(QDeclarativeListProperty<QObject> *property)
{
  qDebug("tokoe: 2");
  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  return that->dataCount();
}

QObject* DeclarativeObject::data_at(QDeclarativeListProperty<QObject> *property, int index)
{
  qDebug("tokoe: 3");
  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  return that->dataAt(index);
}

void DeclarativeObject::data_clear(QDeclarativeListProperty<QObject> *property)
{
  qDebug("tokoe: 4");
  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  that->dataClear();
}

// DeclarativeVBoxLayout
DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent)
  : DeclarativeObject(parent)
  , m_layout(new QVBoxLayout)
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
  DeclarativeWidget *widget = dynamic_cast<DeclarativeWidget*>(object);
  DeclarativeVBoxLayout *layout = dynamic_cast<DeclarativeVBoxLayout*>(object);

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

CUSTOM_METAOBJECT(DeclarativeVBoxLayout, DeclarativeObject, QVBoxLayout, m_layout)

// DeclarativeWidget
DeclarativeWidget::DeclarativeWidget(QObject *parent)
  : DeclarativeObject(parent)
  , m_widget(new QWidget)
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
  DeclarativeWidget *widget = dynamic_cast<DeclarativeWidget*>(object);
  DeclarativeVBoxLayout *layout = dynamic_cast<DeclarativeVBoxLayout*>(object);

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

CUSTOM_METAOBJECT(DeclarativeWidget, DeclarativeObject, QWidget, m_widget)

// DeclarativeLabel
DeclarativeLabel::DeclarativeLabel(QObject *parent)
  : DeclarativeWidget(parent)
  , m_label(new QLabel("<empty>"))
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

CUSTOM_METAOBJECT(DeclarativeLabel, DeclarativeWidget, QLabel, m_label)

// DeclarativeTabWidget
DeclarativeTabWidget::DeclarativeTabWidget(QObject *parent)
  : DeclarativeWidget(parent)
  , m_tabWidget(new QTabWidget)
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
  DeclarativeWidget *widget = dynamic_cast<DeclarativeWidget*>(object);

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

CUSTOM_METAOBJECT(DeclarativeTabWidget, DeclarativeWidget, QTabWidget, m_tabWidget)

// DeclarativePushButton
DeclarativePushButton::DeclarativePushButton(QObject *parent)
  : DeclarativeWidget(parent)
  , m_pushButton(new QPushButton)
{
}

QObject* DeclarativePushButton::object()
{
  if (!m_pushButton)
    m_pushButton = new QPushButton("Hello QML Widgets");

  return m_pushButton;
}

CUSTOM_METAOBJECT(DeclarativePushButton, DeclarativeWidget, QPushButton, m_pushButton)

