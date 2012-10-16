#include "declarativeobjects_p.h"

#include "qmetaobjectbuilder_p.h"

#include <QDebug>

/*
  if (QString(staticMetaObject.className()) == "DeclarativeLabel") { \
    qDebug("class: %s propOffset: %d", qPrintable(staticMetaObject.className()), staticMetaObject.propertyOffset()); \
    for (int i = 0; i < staticMetaObject.propertyCount(); ++i) { \
      qDebug("  prop: %d=%s", i, staticMetaObject.property(i).name()); \
    } \
    qDebug("class: AbstractDeclarativeObject"); \
    for (int i = 0; i < AbstractDeclarativeObject::staticMetaObject.propertyCount(); ++i) { \
      qDebug("  prop: %d=%s", i, AbstractDeclarativeObject::staticMetaObject.property(i).name()); \
    } \
  } \
  if (QString(staticMetaObject.className()) == "DeclarativeLabel") { \
    qDebug("class: %s methodOffset: %d", qPrintable(staticMetaObject.className()), staticMetaObject.methodOffset()); \
    for (int i = 0; i < staticMetaObject.methodCount(); ++i) { \
      qDebug("  prop: %d=%s", i, staticMetaObject.method(i).signature()); \
    } \
  } \
*/

#define CUSTOM_METAOBJECT(ClassName, WidgetType, WidgetVariable) \
QMetaObject ClassName::staticMetaObject;\
bool ClassName::metaObjectInitialized = ClassName::initializeMetaObject(); \
bool ClassName::initializeMetaObject() \
{ \
  QMetaObjectBuilder builder; \
  const QMetaObject *mo = &WidgetType::staticMetaObject; \
  builder.addMetaObject(mo); \
  builder.addMetaObject(&AbstractDeclarativeObject::staticMetaObject); \
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
  return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject; \
} \
void* ClassName::qt_metacast(const char*) \
{ \
  return 0; \
} \
int ClassName::qt_metacall(QMetaObject::Call call, int id, void **argv) \
{ \
  if (call == QMetaObject::ReadProperty || call == QMetaObject::WriteProperty) { \
    if (id >= WidgetType::staticMetaObject.propertyCount()) { \
      id = AbstractDeclarativeObject::qt_metacall(call, id - WidgetType::staticMetaObject.propertyCount() + 1, argv); \
      id += WidgetType::staticMetaObject.propertyCount() - 1; \
    } else { \
      id = WidgetVariable->qt_metacall(call, id, argv); \
    } \
    if (id < 0) \
      return 0; \
  } else if (call == QMetaObject::InvokeMetaMethod) {\
    QMetaObject::activate(this, id, argv); \
    id -= 1; \
  } \
  return id; \
}

// AbstractDeclarativeObject
AbstractDeclarativeObject::AbstractDeclarativeObject(QObject *parent)
  : QObject(parent)
{
}

AbstractDeclarativeObject::~AbstractDeclarativeObject()
{
}

QDeclarativeListProperty<QObject> AbstractDeclarativeObject::data()
{
  return QDeclarativeListProperty<QObject>(this, 0, AbstractDeclarativeObject::data_append,
                                                    AbstractDeclarativeObject::data_count,
                                                    AbstractDeclarativeObject::data_at,
                                                    AbstractDeclarativeObject::data_clear);
}

void AbstractDeclarativeObject::dataAppend(QObject *)
{
}

int AbstractDeclarativeObject::dataCount() const
{
  return 0;
}

QObject* AbstractDeclarativeObject::dataAt(int) const
{
  return 0;
}

void AbstractDeclarativeObject::dataClear()
{
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

void AbstractDeclarativeObject::data_append(QDeclarativeListProperty<QObject> *property, QObject *object)
{
  if (!object)
    return;

  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    that->dataAppend(object);
  else
    qWarning("cast went wrong in data_append");
}

int AbstractDeclarativeObject::data_count(QDeclarativeListProperty<QObject> *property)
{
  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    return that->dataCount();
  else {
    qWarning("cast went wrong in data_count");
    return 0;
  }
}

QObject* AbstractDeclarativeObject::data_at(QDeclarativeListProperty<QObject> *property, int index)
{
  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    return that->dataAt(index);
  else {
    qWarning("cast went wrong in data_at");
    return 0;
  }
}

void AbstractDeclarativeObject::data_clear(QDeclarativeListProperty<QObject> *property)
{
  AbstractDeclarativeObject *that = dynamic_cast<AbstractDeclarativeObject*>(property->object);
  if (that)
    that->dataClear();
  else
    qWarning("cast went wrong in data_clear");
}

// DeclarativeHBoxLayout
DeclarativeHBoxLayout::DeclarativeHBoxLayout(QObject *parent) : DeclarativeBoxLayout<QHBoxLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeHBoxLayout, QHBoxLayout, m_proxiedObject)

// DeclarativeVBoxLayout
DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent) : DeclarativeBoxLayout<QVBoxLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeVBoxLayout, QVBoxLayout, m_proxiedObject)

// DeclarativeWidget
DeclarativeWidget::DeclarativeWidget(QObject *parent) : DeclarativeWidgetProxy<QWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeWidget, QWidget, m_proxiedObject)

// DeclarativeLabel
DeclarativeLabel::DeclarativeLabel(QObject *parent) : DeclarativeWidgetProxy<QLabel>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeLabel, QLabel, m_proxiedObject)

// DeclarativeTabWidget
DeclarativeTabWidget::DeclarativeTabWidget(QObject *parent) : DeclarativeWidgetProxy<QTabWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeTabWidget::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  // TODO: error when layout is set
  m_children.append(declarativeObject);
  m_proxiedObject->addTab(widget, "MyTab");
}

void DeclarativeTabWidget::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not add QLayout to QTabWidget";
}

CUSTOM_METAOBJECT(DeclarativeTabWidget, QTabWidget, m_proxiedObject)

// DeclarativePushButton
DeclarativePushButton::DeclarativePushButton(QObject *parent) : DeclarativeWidgetProxy<QPushButton>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativePushButton, QPushButton, m_proxiedObject)

// DeclarativeCheckBox
DeclarativeCheckBox::DeclarativeCheckBox(QObject *parent) : DeclarativeWidgetProxy<QCheckBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeCheckBox, QCheckBox, m_proxiedObject)

// DeclarativeSlider
DeclarativeSlider::DeclarativeSlider(QObject *parent) : DeclarativeWidgetProxy<QSlider>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeSlider, QSlider, m_proxiedObject)
