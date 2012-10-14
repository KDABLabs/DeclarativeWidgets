#include "declarativeobjects_p.h"

#include "qmetaobjectbuilder_p.h"

#include <QDebug>

/*
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
  if (QString(staticMetaObject.className()) == "DeclarativeLabel") { \
    qDebug("class: %s methodOffset: %d", qPrintable(staticMetaObject.className()), staticMetaObject.methodOffset()); \
    for (int i = 0; i < staticMetaObject.methodCount(); ++i) { \
      qDebug("  prop: %d=%s", i, staticMetaObject.method(i).signature()); \
    } \
  } \
*/

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
  ClassName::staticMetaObject = *builder.toMetaObject(); \
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
  if (call == QMetaObject::ReadProperty || call == QMetaObject::WriteProperty) { \
    if (id >= WidgetType::staticMetaObject.propertyCount()) { \
      id = DeclarativeObject::qt_metacall(call, id - WidgetType::staticMetaObject.propertyCount() + 1, argv); \
      id += WidgetType::staticMetaObject.propertyCount() - 1; \
    } else { \
      id = WidgetVariable->qt_metacall(call, id, argv); \
    } \
    if (id < 0) \
      return 0; \
  } else if (call == QMetaObject::InvokeMetaMethod) {\
    QMetaObject::activate(this, id, argv); \
  } \
  return id; \
}

static void connectAllSignals(QObject *sender, QObject *receiver)
{
  for (int i = 0; i < sender->metaObject()->methodCount(); ++i) {
    const QMetaMethod method = sender->metaObject()->method(i);
    if (method.methodType() == QMetaMethod::Signal) {
      const QByteArray signature = "2" + QByteArray(method.signature());
      QObject::connect(sender, signature.data(), receiver, signature.data());
    }
  }
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
  if (!object)
    return;

  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  if (that)
    that->dataAppend(object);
  else
    qWarning("cast went wrong in data_append");
}

int DeclarativeObject::data_count(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  if (that)
    return that->dataCount();
  else {
    qWarning("cast went wrong in data_count");
    return 0;
  }
}

QObject* DeclarativeObject::data_at(QDeclarativeListProperty<QObject> *property, int index)
{
  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  if (that)
    return that->dataAt(index);
  else {
    qWarning("cast went wrong in data_at");
    return 0;
  }
}

void DeclarativeObject::data_clear(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObject *that = dynamic_cast<DeclarativeObject*>(property->object);
  if (that)
    that->dataClear();
  else
    qWarning("cast went wrong in data_clear");
}

// DeclarativeHBoxLayout
DeclarativeHBoxLayout::DeclarativeHBoxLayout(QObject *parent)
  : DeclarativeObject(parent)
  , m_layout(new QHBoxLayout)
{
  connectAllSignals(m_layout, this);
}

DeclarativeHBoxLayout::~DeclarativeHBoxLayout()
{
  delete m_layout;
}

QObject* DeclarativeHBoxLayout::object()
{
  return m_layout;
}

void DeclarativeHBoxLayout::dataAppend(QObject *object)
{
  DeclarativeWidget *widget = dynamic_cast<DeclarativeWidget*>(object);
  DeclarativeHBoxLayout *hboxLayout = dynamic_cast<DeclarativeHBoxLayout*>(object);
  DeclarativeVBoxLayout *vboxLayout = dynamic_cast<DeclarativeVBoxLayout*>(object);

  if (widget) {
    m_children.append(object);
    m_layout->addWidget(qobject_cast<QWidget*>(widget->object()));
  } else if (hboxLayout) {
    m_children.append(object);
    m_layout->addLayout(qobject_cast<QLayout*>(hboxLayout->object()));
  } else if (vboxLayout) {
    m_children.append(object);
    m_layout->addLayout(qobject_cast<QLayout*>(vboxLayout->object()));
  } else {
    // TODO: error unknown type
  }
}

int DeclarativeHBoxLayout::dataCount()
{
  return m_children.count();
}

QObject* DeclarativeHBoxLayout::dataAt(int index)
{
  return m_children.at(index);
}

void DeclarativeHBoxLayout::dataClear()
{
  qDeleteAll(m_children);
  m_children.clear();
}

CUSTOM_METAOBJECT(DeclarativeHBoxLayout, DeclarativeObject, QHBoxLayout, m_layout)

// DeclarativeVBoxLayout
DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent)
  : DeclarativeObject(parent)
  , m_layout(new QVBoxLayout)
{
  connectAllSignals(m_layout, this);
}

DeclarativeVBoxLayout::~DeclarativeVBoxLayout()
{
  delete m_layout;
}

QObject* DeclarativeVBoxLayout::object()
{
  return m_layout;
}

void DeclarativeVBoxLayout::dataAppend(QObject *object)
{
  DeclarativeWidget *widget = dynamic_cast<DeclarativeWidget*>(object);
  DeclarativeHBoxLayout *hboxLayout = dynamic_cast<DeclarativeHBoxLayout*>(object);
  DeclarativeVBoxLayout *vboxLayout = dynamic_cast<DeclarativeVBoxLayout*>(object);

  if (widget) {
    m_children.append(object);
    m_layout->addWidget(qobject_cast<QWidget*>(widget->object()));
  } else if (hboxLayout) {
    m_children.append(object);
    m_layout->addLayout(qobject_cast<QLayout*>(hboxLayout->object()));
  } else if (vboxLayout) {
    m_children.append(object);
    m_layout->addLayout(qobject_cast<QLayout*>(vboxLayout->object()));
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
  connectAllSignals(m_widget, this);
}

DeclarativeWidget::~DeclarativeWidget()
{
  delete m_widget;
}

QObject* DeclarativeWidget::object()
{
  return m_widget;
}

void DeclarativeWidget::dataAppend(QObject *object)
{
  DeclarativeWidget *widget = dynamic_cast<DeclarativeWidget*>(object);
  DeclarativeHBoxLayout *hboxLayout = dynamic_cast<DeclarativeHBoxLayout*>(object);
  DeclarativeVBoxLayout *vboxLayout = dynamic_cast<DeclarativeVBoxLayout*>(object);

  if (widget) {
    // TODO: error when layout is set
    m_children.append(object);
    qobject_cast<QWidget*>(widget->object())->setParent(m_widget);
  } else if (hboxLayout) {
    // TODO: error when widget is set

    m_children.append(object);
    m_widget->setLayout(qobject_cast<QLayout*>(hboxLayout->object()));
  } else if (vboxLayout) {
    // TODO: error when widget is set

    m_children.append(object);
    m_widget->setLayout(qobject_cast<QLayout*>(vboxLayout->object()));
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
  , m_label(new QLabel)
{
  connectAllSignals(m_label, this);
}

DeclarativeLabel::~DeclarativeLabel()
{
  delete m_label;
}

QObject* DeclarativeLabel::object()
{
  return m_label;
}

CUSTOM_METAOBJECT(DeclarativeLabel, DeclarativeWidget, QLabel, m_label)

// DeclarativeTabWidget
DeclarativeTabWidget::DeclarativeTabWidget(QObject *parent)
  : DeclarativeWidget(parent)
  , m_tabWidget(new QTabWidget)
{
  connectAllSignals(m_tabWidget, this);
}

DeclarativeTabWidget::~DeclarativeTabWidget()
{
  delete m_tabWidget;
}

QObject* DeclarativeTabWidget::object()
{
  return m_tabWidget;
}

void DeclarativeTabWidget::dataAppend(QObject *object)
{
  DeclarativeWidget *widget = dynamic_cast<DeclarativeWidget*>(object);

  if (widget) {
    // TODO: error when layout is set
    m_children.append(object);
    m_tabWidget->addTab(qobject_cast<QWidget*>(widget->object()), "MyTab");
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
  connectAllSignals(m_pushButton, this);
}

DeclarativePushButton::~DeclarativePushButton()
{
  delete m_pushButton;
}

QObject* DeclarativePushButton::object()
{
  return m_pushButton;
}

CUSTOM_METAOBJECT(DeclarativePushButton, DeclarativeWidget, QPushButton, m_pushButton)

// DeclarativeCheckBox
DeclarativeCheckBox::DeclarativeCheckBox(QObject *parent)
  : DeclarativeWidget(parent)
  , m_checkBox(new QCheckBox)
{
  connectAllSignals(m_checkBox, this);
}

DeclarativeCheckBox::~DeclarativeCheckBox()
{
  delete m_checkBox;
}

QObject* DeclarativeCheckBox::object()
{
  return m_checkBox;
}

CUSTOM_METAOBJECT(DeclarativeCheckBox, DeclarativeWidget, QCheckBox, m_checkBox)
