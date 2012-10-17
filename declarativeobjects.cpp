#include "declarativeobjects_p.h"

#include "qmetaobjectbuilder_p.h"

#include <QDebug>

#define CUSTOM_METAOBJECT(ClassName, ProxyObjectType) \
QMetaObject ClassName::staticMetaObject;\
bool ClassName::metaObjectInitialized = ClassName::initializeMetaObject(); \
bool ClassName::initializeMetaObject() \
{ \
  QMetaObjectBuilder builder; \
  const QMetaObject *mo = &ProxyObjectType::staticMetaObject; \
  builder.addMetaObject(mo); \
  builder.addMetaObject(&AbstractDeclarativeObject::staticMetaObject); \
  builder.setSuperClass(ProxyObjectType::staticMetaObject.superClass()); \
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
    if (id >= ProxyObjectType::staticMetaObject.propertyCount()) { \
      id = AbstractDeclarativeObject::qt_metacall(call, id - ProxyObjectType::staticMetaObject.propertyCount() + 1, argv); \
      id += ProxyObjectType::staticMetaObject.propertyCount() - 1; \
    } else { \
      id = m_proxiedObject->qt_metacall(call, id, argv); \
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

//// Layouts ////

// DeclarativeHBoxLayout
DeclarativeHBoxLayout::DeclarativeHBoxLayout(QObject *parent) : DeclarativeBoxLayout<QHBoxLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeHBoxLayout, QHBoxLayout)

// DeclarativeVBoxLayout
DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent) : DeclarativeBoxLayout<QVBoxLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeVBoxLayout, QVBoxLayout)

//// Widgets ////

// DeclarativeCalendarWidget
DeclarativeCalendarWidget::DeclarativeCalendarWidget(QObject *parent) : DeclarativeWidgetProxy<QCalendarWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeCalendarWidget, QCalendarWidget)

// DeclarativeCheckBox
DeclarativeCheckBox::DeclarativeCheckBox(QObject *parent) : DeclarativeWidgetProxy<QCheckBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeCheckBox, QCheckBox)

// DeclarativeLabel
DeclarativeLabel::DeclarativeLabel(QObject *parent) : DeclarativeWidgetProxy<QLabel>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeLabel, QLabel)

// DeclarativePushButton
DeclarativePushButton::DeclarativePushButton(QObject *parent) : DeclarativeWidgetProxy<QPushButton>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativePushButton, QPushButton)

// DeclarativeSlider
DeclarativeSlider::DeclarativeSlider(QObject *parent) : DeclarativeWidgetProxy<QSlider>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeSlider, QSlider)

// DeclarativeTabWidget
class TabWidgetTabHeader::Private
{
  public:
    QString label;
    QIcon icon;
};

TabWidgetTabHeader::TabWidgetTabHeader(QObject *parent)
  : QObject(parent), d(new TabWidgetTabHeader::Private)
{
}

TabWidgetTabHeader::~TabWidgetTabHeader()
{
  delete d;
}

void TabWidgetTabHeader::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;
  emit labelChanged(label);
}

QString TabWidgetTabHeader::label() const
{
  return d->label;
}

void TabWidgetTabHeader::setIcon(const QIcon &icon)
{
  d->icon = icon;
  emit iconChanged(icon);
}

QIcon TabWidgetTabHeader::icon() const
{
  return d->icon;
}

DeclarativeTabWidget::DeclarativeTabWidget(QObject *parent) : DeclarativeWidgetProxy<QTabWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeTabWidget::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  // TODO: error when layout is set

  m_children.append(declarativeObject);

  QString label;
  QIcon icon;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeTabWidget>(declarativeObject, false);
  TabWidgetTabHeader *tabHeader = qobject_cast<TabWidgetTabHeader*>(attachedProperties);
  if (tabHeader) {
    label = tabHeader->label();
    icon = tabHeader->icon();
  }

  m_proxiedObject->addTab(widget, icon, label);
}

void DeclarativeTabWidget::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not add QLayout to QTabWidget";
}

TabWidgetTabHeader *DeclarativeTabWidget::qmlAttachedProperties(QObject *object)
{
  return new TabWidgetTabHeader(object);
}

CUSTOM_METAOBJECT(DeclarativeTabWidget, QTabWidget)

// DeclarativeWidget
DeclarativeWidget::DeclarativeWidget(QObject *parent) : DeclarativeWidgetProxy<QWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeWidget, QWidget)

