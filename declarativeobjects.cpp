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
    if (ClassName::staticMetaObject.method(id).methodType() == QMetaMethod::Signal) \
      QMetaObject::activate(this, id, argv); \
    else \
      id = m_proxiedObject->qt_metacall(call, id, argv); \
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

static void connectAllSignals(QObject *sender, QObject *receiver, const QSet<QByteArray> &blacklist = QSet<QByteArray>())
{
  for (int i = 0; i < sender->metaObject()->methodCount(); ++i) {
    const QMetaMethod method = sender->metaObject()->method(i);
    if (method.methodType() == QMetaMethod::Signal) {
      if (blacklist.contains(method.signature()))
        continue;

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

//// Objects ////

// DeclarativeAction
DeclarativeAction::DeclarativeAction(QObject *parent) : DeclarativeObjectProxy<QAction, true>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeAction, QAction)

// DeclarativeActionItem
DeclarativeActionItem::DeclarativeActionItem(QObject *parent) : DeclarativeObjectProxy<ActionItem>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeActionItem, ActionItem)

// DeclarativeButtonGroup
DeclarativeButtonGroup::DeclarativeButtonGroup(QObject *parent) : DeclarativeObjectProxy<ButtonGroup>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeButtonGroup, ButtonGroup)

// DeclarativeSeparator
DeclarativeSeparator::DeclarativeSeparator(QObject *parent) : DeclarativeObjectProxy<QAction, true>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeSeparator, QAction)

//// Layouts ////
class DeclarativeBoxLayoutAttached::Private
{
  public:
    Private(QWidget *w, QLayout *l) : stretch(0), alignment(0), widget(w), layout(l) {}

    int stretch;
    Qt::Alignment alignment;

    QPointer<QWidget> widget;
    QPointer<QLayout> layout;
    QPointer<QBoxLayout> parentLayout;
};

DeclarativeBoxLayoutAttached::DeclarativeBoxLayoutAttached(QWidget *widget, QObject *parent)
  : QObject(parent), d(new Private(widget, 0))
{
}

DeclarativeBoxLayoutAttached::DeclarativeBoxLayoutAttached(QLayout *layout, QObject *parent)
  : QObject(parent), d(new Private(0, layout))
{
}

DeclarativeBoxLayoutAttached::~DeclarativeBoxLayoutAttached()
{
  delete d;
}

void DeclarativeBoxLayoutAttached::setParentLayout(QBoxLayout *parentLayout)
{
  d->parentLayout = parentLayout;
}

void DeclarativeBoxLayoutAttached::setStretch(int stretch)
{
  if (stretch == d->stretch)
    return;

  d->stretch = stretch;
  emit stretchChanged(stretch);
}

int DeclarativeBoxLayoutAttached::stretch() const
{
  return d->stretch;
}

void DeclarativeBoxLayoutAttached::setAlignment(Qt::Alignment alignment)
{
  if (alignment == d->alignment)
    return;

  d->alignment = alignment;
  emit alignmentChanged(alignment);

  if (d->parentLayout) {
    if (d->widget)
      d->parentLayout->setAlignment(d->widget, d->alignment);

    if (d->layout)
      d->parentLayout->setAlignment(d->layout, d->alignment);
  }
}

Qt::Alignment DeclarativeBoxLayoutAttached::alignment() const
{
  return d->alignment;
}

class DeclarativeFormLayoutAttached::Private
{
  public:
    QString label;
};

DeclarativeFormLayoutAttached::DeclarativeFormLayoutAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

DeclarativeFormLayoutAttached::~DeclarativeFormLayoutAttached()
{
  delete d;
}

void DeclarativeFormLayoutAttached::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;
  emit labelChanged(label);
}

class DeclarativeGridLayoutAttached::Private
{
  public:
    Private(QWidget *w, QLayout *l)
      : row(0), column(0), rowSpan(1), columnSpan(1), alignment(0),
        widget(w), layout(l)
    {}

    int row;
    int column;
    int rowSpan;
    int columnSpan;
    Qt::Alignment alignment;

    QPointer<QWidget> widget;
    QPointer<QLayout> layout;
    QPointer<QGridLayout> parentLayout;
};

DeclarativeGridLayoutAttached::DeclarativeGridLayoutAttached(QWidget *widget, QObject *parent)
  : QObject(parent), d(new Private(widget, 0))
{
}

DeclarativeGridLayoutAttached::DeclarativeGridLayoutAttached(QLayout *layout, QObject *parent)
  : QObject(parent), d(new Private(0, layout))
{
}

DeclarativeGridLayoutAttached::~DeclarativeGridLayoutAttached()
{
  delete d;
}

void DeclarativeGridLayoutAttached::setParentLayout(QGridLayout *parentLayout)
{
  d->parentLayout = parentLayout;
}

void DeclarativeGridLayoutAttached::setRow(int row)
{
  if (row == d->row)
    return;

  d->row = row;
  emit rowChanged(row);
}

int DeclarativeGridLayoutAttached::row() const
{
  return d->row;
}

void DeclarativeGridLayoutAttached::setColumn(int column)
{
  if (column == d->column)
    return;

  d->column = column;
  emit columnChanged(column);
}

int DeclarativeGridLayoutAttached::column() const
{
  return d->column;
}

void DeclarativeGridLayoutAttached::setRowSpan(int rowSpan)
{
  if (rowSpan == d->rowSpan)
    return;

  d->rowSpan = rowSpan;
  emit rowSpanChanged(rowSpan);
}

int DeclarativeGridLayoutAttached::rowSpan() const
{
  return d->rowSpan;
}

void DeclarativeGridLayoutAttached::setColumnSpan(int columnSpan)
{
  if (columnSpan == d->columnSpan)
    return;

  d->columnSpan = columnSpan;
  emit columnSpanChanged(columnSpan);
}

int DeclarativeGridLayoutAttached::columnSpan() const
{
  return d->columnSpan;
}

void DeclarativeGridLayoutAttached::setAlignment(Qt::Alignment alignment)
{
  if (alignment == d->alignment)
    return;

  d->alignment = alignment;
  emit alignmentChanged(alignment);

  if (d->parentLayout) {
    if (d->widget)
      d->parentLayout->setAlignment(d->widget, d->alignment);

    if (d->layout)
      d->parentLayout->setAlignment(d->layout, d->alignment);
  }
}

Qt::Alignment DeclarativeGridLayoutAttached::alignment() const
{
  return d->alignment;
}

QString DeclarativeFormLayoutAttached::label() const
{
  return d->label;
}

// DeclarativeFormLayout
DeclarativeFormLayout::DeclarativeFormLayout(QObject *parent) : DeclarativeLayoutProxy<QFormLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeFormLayoutAttached *DeclarativeFormLayout::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeFormLayoutAttached(parent);
}

void DeclarativeFormLayout::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(declarativeObject, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    if (!properties->label().isEmpty()) {
      m_proxiedObject->addRow(properties->label(), widget);
      m_children.append(declarativeObject);
      return;
    }
  }

  m_proxiedObject->addRow(widget);
  m_children.append(declarativeObject);
}

void DeclarativeFormLayout::addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeFormLayout>(declarativeObject, false);
  DeclarativeFormLayoutAttached *properties = qobject_cast<DeclarativeFormLayoutAttached*>(attachedProperties);
  if (properties) {
    if (!properties->label().isEmpty()) {
      m_proxiedObject->addRow(properties->label(), layout);
      m_children.append(declarativeObject);
      return;
    }
  }
  m_proxiedObject->addRow(layout);
  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeFormLayout, QFormLayout)

// DeclarativeGridLayout
DeclarativeGridLayout::DeclarativeGridLayout(QObject *parent) : DeclarativeLayoutProxy<QGridLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeGridLayoutAttached *DeclarativeGridLayout::qmlAttachedProperties(QObject *parent)
{
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject) {
    QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
    if (widget)
      return new DeclarativeGridLayoutAttached(widget, parent);

    QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
    if (layout)
      return new DeclarativeGridLayoutAttached(layout, parent);
  }

  qmlInfo(parent) << "Can only attach GridLayout to widgets and layouts";
  return 0;
}

void DeclarativeGridLayout::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  int row = 0;
  int column = 0;
  int rowSpan = 1;
  int columnSpan = 1;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeGridLayout>(declarativeObject, false);
  DeclarativeGridLayoutAttached *properties = qobject_cast<DeclarativeGridLayoutAttached*>(attachedProperties);
  if (properties) {
    row = properties->row();
    column = properties->column();
    rowSpan = properties->rowSpan();
    columnSpan = properties->columnSpan();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addWidget(widget, row, column, rowSpan, columnSpan, alignment);
  m_children.append(declarativeObject);
}

void DeclarativeGridLayout::addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  int row = 0;
  int column = 0;
  int rowSpan = 1;
  int columnSpan = 1;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeGridLayout>(declarativeObject, false);
  DeclarativeGridLayoutAttached *properties = qobject_cast<DeclarativeGridLayoutAttached*>(attachedProperties);
  if (properties) {
    row = properties->row();
    column = properties->column();
    rowSpan = properties->rowSpan();
    columnSpan = properties->columnSpan();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addLayout(layout, row, column, rowSpan, columnSpan, alignment);
  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeGridLayout, QGridLayout)

// DeclarativeHBoxLayout
DeclarativeHBoxLayout::DeclarativeHBoxLayout(QObject *parent) : DeclarativeLayoutProxy<QHBoxLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeBoxLayoutAttached *DeclarativeHBoxLayout::qmlAttachedProperties(QObject *parent)
{
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject) {
    QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
    if (widget)
      return new DeclarativeBoxLayoutAttached(widget, parent);

    QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
    if (layout)
      return new DeclarativeBoxLayoutAttached(layout, parent);
  }

  qmlInfo(parent) << "Can only attach HBoxLayout to widgets and layouts";
  return 0;
}

void DeclarativeHBoxLayout::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(declarativeObject, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addWidget(widget, stretch, alignment);
  m_children.append(declarativeObject);
}

void DeclarativeHBoxLayout::addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(declarativeObject, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addLayout(layout, stretch);
  m_proxiedObject->setAlignment(layout, alignment);
  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeHBoxLayout, QHBoxLayout)

// DeclarativeStackedLayout
DeclarativeStackedLayout::DeclarativeStackedLayout(QObject *parent) : DeclarativeLayoutProxy<StackedLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeStackedLayout::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  m_proxiedObject->addWidget(widget);
  m_children.append(declarativeObject);
}

void DeclarativeStackedLayout::addLayout(QLayout*, AbstractDeclarativeObject *declarativeObject)
{
  qmlInfo(declarativeObject) << "StackedLayout does not support child layouts";
}

CUSTOM_METAOBJECT(DeclarativeStackedLayout, StackedLayout)

// DeclarativeVBoxLayout
DeclarativeVBoxLayout::DeclarativeVBoxLayout(QObject *parent) : DeclarativeLayoutProxy<QVBoxLayout>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeBoxLayoutAttached *DeclarativeVBoxLayout::qmlAttachedProperties(QObject *parent)
{
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject) {
    QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
    if (widget)
      return new DeclarativeBoxLayoutAttached(widget, parent);

    QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
    if (layout)
      return new DeclarativeBoxLayoutAttached(layout, parent);
  }

  qmlInfo(parent) << "Can only attach VBoxLayout to widgets and layouts";
  return 0;
}

void DeclarativeVBoxLayout::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeVBoxLayout>(declarativeObject, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addWidget(widget, stretch, alignment);
  m_children.append(declarativeObject);
}

void DeclarativeVBoxLayout::addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeVBoxLayout>(declarativeObject, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_proxiedObject);
  }

  m_proxiedObject->addLayout(layout, stretch);
  m_proxiedObject->setAlignment(layout, alignment);
  m_children.append(declarativeObject);
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

// DeclarativeColorDialog
class DeclarativeColorDialogAttached::Private
{
  public:
    Private() : options(0) {}

  public:
    QPointer<QObject> dialogParent;
    QString title;
    QColorDialog::ColorDialogOptions options;
};

DeclarativeColorDialogAttached::DeclarativeColorDialogAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

DeclarativeColorDialogAttached::~DeclarativeColorDialogAttached()
{
  delete d;
}

void DeclarativeColorDialogAttached::setDialogParent(QObject *parent)
{
  if (parent == d->dialogParent)
    return;

  d->dialogParent = parent;
  emit dialogParentChanged(parent);
}

QObject *DeclarativeColorDialogAttached::dialogParent() const
{
  return d->dialogParent;
}

void DeclarativeColorDialogAttached::setTitle(const QString &title)
{
  if (title == d->title)
    return;

  d->title = title;
  emit titleChanged(title);
}

QString DeclarativeColorDialogAttached::title() const
{
  return d->title;
}

QColor DeclarativeColorDialogAttached::getColor(const QColor &initialColor)
{
  QWidget *parent = bestParentWindow(d->dialogParent);
  if (!d->title.isEmpty() || d->options != 0)
    return QColorDialog::getColor(initialColor, parent, d->title, d->options);
  else
    return QColorDialog::getColor(initialColor, parent);
}

QWidget *DeclarativeColorDialogAttached::bestParentWindow(QObject *parent) const
{
  if (!parent)
    parent = this->parent();

  // if parent is a Declarative Object, search the proxied hierarchy
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject)
    parent = declarativeObject->object();

  while (parent) {
    QWidget *widget = qobject_cast<QWidget*>(parent);
    if (widget)
      return widget->topLevelWidget();

    parent = parent->parent();
  }

  return 0;
}

DeclarativeColorDialog::DeclarativeColorDialog(QObject *parent) : DeclarativeWidgetProxy<QColorDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeColorDialogAttached *DeclarativeColorDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeColorDialogAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeColorDialog, QColorDialog)

// DeclarativeColumnView
DeclarativeColumnView::DeclarativeColumnView(QObject *parent) : DeclarativeWidgetProxy<ColumnView>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeColumnView, ColumnView)

// DeclarativeCommandLinkButton
DeclarativeCommandLinkButton::DeclarativeCommandLinkButton(QObject *parent) : DeclarativeWidgetProxy<QCommandLinkButton>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeCommandLinkButton, QCommandLinkButton)

// DeclarativeDateEdit
DeclarativeDateEdit::DeclarativeDateEdit(QObject *parent) : DeclarativeWidgetProxy<QDateEdit>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeDateEdit, QDateEdit)

// DeclarativeDateTimeEdit
DeclarativeDateTimeEdit::DeclarativeDateTimeEdit(QObject *parent) : DeclarativeWidgetProxy<QDateTimeEdit>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeDateTimeEdit, QDateTimeEdit)

// DeclarativeDial
DeclarativeDial::DeclarativeDial(QObject *parent) : DeclarativeWidgetProxy<QDial>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeDial, QDial)

// DeclarativeDialog
DeclarativeDialog::DeclarativeDialog(QObject *parent) : DeclarativeWidgetProxy<QDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeDialog, QDialog)

// DeclarativeDialogButtonBox
DeclarativeDialogButtonBox::DeclarativeDialogButtonBox(QObject *parent) : DeclarativeWidgetProxy<QDialogButtonBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeDialogButtonBox, QDialogButtonBox)

// DeclarativeDoubleSpinBox
DeclarativeDoubleSpinBox::DeclarativeDoubleSpinBox(QObject *parent) : DeclarativeWidgetProxy<QDoubleSpinBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeDoubleSpinBox, QDoubleSpinBox)

// DeclarativeFileDialog
class DeclarativeFileDialogAttached::Private
{
  public:
    QPointer<QObject> dialogParent;
    QString caption;
    QString dir;
    QStringList nameFilters;
    QString selectedFilter;
};

DeclarativeFileDialogAttached::DeclarativeFileDialogAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

DeclarativeFileDialogAttached::~DeclarativeFileDialogAttached()
{
  delete d;
}

void DeclarativeFileDialogAttached::setDialogParent(QObject *parent)
{
  if (parent == d->dialogParent)
    return;

  d->dialogParent = parent;
  emit dialogParentChanged(parent);
}

QObject *DeclarativeFileDialogAttached::dialogParent() const
{
  return d->dialogParent;
}

void DeclarativeFileDialogAttached::setCaption(const QString &caption)
{
  if (caption == d->caption)
    return;

  d->caption = caption;
  emit captionChanged(caption);
}

QString DeclarativeFileDialogAttached::caption() const
{
  return d->caption;
}

void DeclarativeFileDialogAttached::setDir(const QString &dir)
{
  if (dir == d->dir)
    return;

  d->dir = dir;
  emit dirChanged(dir);
}

QString DeclarativeFileDialogAttached::dir() const
{
  return d->dir;
}

void DeclarativeFileDialogAttached::setNameFilters(const QStringList &nameFilters)
{
  if (nameFilters == d->nameFilters)
    return;

  d->nameFilters = nameFilters;
  emit nameFiltersChanged(nameFilters);
}

QStringList DeclarativeFileDialogAttached::nameFilters() const
{
  return d->nameFilters;
}

QString DeclarativeFileDialogAttached::selectedFilter() const
{
  return d->selectedFilter;
}

QString DeclarativeFileDialogAttached::getExistingDirectory()
{
  return QFileDialog::getExistingDirectory(bestParentWindow(d->dialogParent), d->caption, d->dir, QFileDialog::ShowDirsOnly);
}

QString DeclarativeFileDialogAttached::getOpenFileName()
{
  QString selectedFilter;
  const QString retVal = QFileDialog::getOpenFileName(bestParentWindow(d->dialogParent), d->caption, d->dir,
                                                      d->nameFilters.join(";;"), &selectedFilter, 0);
  setSelectedFilter(selectedFilter);
  return retVal;
}

QStringList DeclarativeFileDialogAttached::getOpenFileNames()
{
  QString selectedFilter;
  const QStringList retVal = QFileDialog::getOpenFileNames(bestParentWindow(d->dialogParent), d->caption, d->dir,
                                                           d->nameFilters.join(";;"), &selectedFilter, 0);
  setSelectedFilter(selectedFilter);
  return retVal;
}

QString DeclarativeFileDialogAttached::getSaveFileName()
{
  QString selectedFilter;
  const QString retVal = QFileDialog::getSaveFileName(bestParentWindow(d->dialogParent), d->caption, d->dir,
                                                      d->nameFilters.join(";;"), &selectedFilter, 0);
  setSelectedFilter(selectedFilter);
  return retVal;
}

QWidget *DeclarativeFileDialogAttached::bestParentWindow(QObject *parent) const
{
  if (!parent)
    parent = this->parent();

  // if parent is a Declarative Object, search the proxied hierarchy
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject)
    parent = declarativeObject->object();

  while (parent) {
    QWidget *widget = qobject_cast<QWidget*>(parent);
    if (widget)
      return widget->topLevelWidget();

    parent = parent->parent();
  }

  return 0;
}

void DeclarativeFileDialogAttached::setSelectedFilter(const QString &filter)
{
  if (filter == d->selectedFilter)
    return;

  d->selectedFilter = filter;
  emit selectedFilterChanged(filter);
}

DeclarativeFileDialog::DeclarativeFileDialog(QObject *parent) : DeclarativeWidgetProxy<FileDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeFileDialogAttached *DeclarativeFileDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeFileDialogAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeFileDialog, FileDialog)

// DeclarativeFontDialog
DeclarativeFontDialog::DeclarativeFontDialog(QObject *parent) : DeclarativeWidgetProxy<QFontDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeFontDialog, QFontDialog)

// DeclarativeFrame
DeclarativeFrame::DeclarativeFrame(QObject *parent) : DeclarativeWidgetProxy<QFrame>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeFrame, QFrame)

// DeclarativeGroupBox
DeclarativeGroupBox::DeclarativeGroupBox(QObject *parent) : DeclarativeWidgetProxy<QGroupBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeGroupBox, QGroupBox)

// DeclarativeInputDialog
class DeclarativeInputDialogAttached::Private
{
  public:
    Private() : dialogAccepted(false),
                value(0), min(-2147483647), max(2147483647), decimals(1), step(1),
                currentItem(0), itemsEditable(true),
                echoMode(QLineEdit::Normal)
    {}

  public:
    QPointer<QObject> dialogParent;
    QString title;
    QString label;
    bool dialogAccepted;

    QVariant value;
    QVariant min;
    QVariant max;
    int decimals;
    int step;

    int currentItem;
    bool itemsEditable;

    QLineEdit::EchoMode echoMode;
    QString text;
};

DeclarativeInputDialogAttached::DeclarativeInputDialogAttached(QObject *parent)
  : QObject(parent), d(new Private)
{
}

DeclarativeInputDialogAttached::~DeclarativeInputDialogAttached()
{
  delete d;
}

void DeclarativeInputDialogAttached::setDialogParent(QObject *parent)
{
  if (parent == d->dialogParent)
    return;

  d->dialogParent = parent;
  emit dialogParentChanged(parent);
}

QObject *DeclarativeInputDialogAttached::dialogParent() const
{
  return d->dialogParent;
}

void DeclarativeInputDialogAttached::setTitle(const QString &title)
{
  if (title == d->title)
    return;

  d->title = title;
  emit titleChanged(title);
}

QString DeclarativeInputDialogAttached::title() const
{
  return d->title;
}

void DeclarativeInputDialogAttached::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;
  emit labelChanged(label);
}

QString DeclarativeInputDialogAttached::label() const
{
  return d->label;
}

bool DeclarativeInputDialogAttached::dialogAccepted() const
{
  return d->dialogAccepted;
}

void DeclarativeInputDialogAttached::setValue(const QVariant &value)
{
  if (value == d->value)
    return;

  d->value = value;
  emit valueChanged(value);
}

QVariant DeclarativeInputDialogAttached::value() const
{
  return d->value;
}

void DeclarativeInputDialogAttached::setMin(const QVariant &min)
{
  if (min == d->min)
    return;

  d->min = min;
  emit minChanged(min);
}

QVariant DeclarativeInputDialogAttached::min() const
{
  return d->min;
}

void DeclarativeInputDialogAttached::setMax(const QVariant &max)
{
  if (max == d->max)
    return;

  d->max = max;
  emit maxChanged(max);
}

QVariant DeclarativeInputDialogAttached::max() const
{
  return d->max;
}

void DeclarativeInputDialogAttached::setDecimals(int decimals)
{
  if (decimals == d->decimals)
    return;

  d->decimals = decimals;
  emit decimalsChanged(decimals);
}

int DeclarativeInputDialogAttached::decimals() const
{
  return d->decimals;
}

void DeclarativeInputDialogAttached::setStep(int step)
{
  if (step == d->step)
    return;

  d->step = step;
  emit stepChanged(step);
}

int DeclarativeInputDialogAttached::step() const
{
  return d->step;
}

void DeclarativeInputDialogAttached::setCurrentItem(int current)
{
  if (current == d->currentItem)
    return;

  d->currentItem = current;
  emit currentItemChanged(current);
}

int DeclarativeInputDialogAttached::currentItem() const
{
  return d->currentItem;
}

void DeclarativeInputDialogAttached::setItemsEditable(bool editable)
{
  if (editable == d->itemsEditable)
    return;

  d->itemsEditable = editable;
  emit itemsEditableChanged(editable);
}

bool DeclarativeInputDialogAttached::itemsEditable() const
{
  return d->itemsEditable;
}

void DeclarativeInputDialogAttached::setEchoMode(QLineEdit::EchoMode echoMode)
{
  if (echoMode == d->echoMode)
    return;

  d->echoMode = echoMode;
  emit echoModeChanged(echoMode);
}

QLineEdit::EchoMode DeclarativeInputDialogAttached::echoMode() const
{
  return d->echoMode;
}

void DeclarativeInputDialogAttached::setText(const QString &text)
{
  if (text == d->text)
    return;

  d->text = text;
  emit textChanged(text);
}

QString DeclarativeInputDialogAttached::text() const
{
  return d->text;
}

double DeclarativeInputDialogAttached::getDouble()
{
  QWidget *parent = bestParentWindow(d->dialogParent);
  bool ok = false;
  const double value = d->value.canConvert<double>() ? d->value.value<double>() : 0.0;
  const double min = d->min.canConvert<double>() ? d->min.value<double>() : -2147483647;
  const double max = d->max.canConvert<double>() ? d->max.value<double>() : 2147483647;

  const double retVal = QInputDialog::getDouble(parent, d->title, d->label, value, min, max, d->decimals, &ok);

  setDialogAccepted(ok);
  return retVal;
}

int DeclarativeInputDialogAttached::getInt()
{
  QWidget *parent = bestParentWindow(d->dialogParent);
  bool ok = false;
  const int value = d->value.canConvert<int>() ? d->value.value<int>() : 0;
  const int min = d->min.canConvert<int>() ? d->min.value<int>() : -2147483647;
  const int max = d->max.canConvert<int>() ? d->max.value<int>() : 2147483647;

  const int retVal = QInputDialog::getInt(parent, d->title, d->label, value, min, max, d->step, &ok);

  setDialogAccepted(ok);
  return retVal;
}

QString DeclarativeInputDialogAttached::getItem(const QStringList &items)
{
  QWidget *parent = bestParentWindow(d->dialogParent);
  bool ok = false;

  const QString retVal = QInputDialog::getItem(parent, d->title, d->label, items, d->currentItem, d->itemsEditable, &ok);

  setDialogAccepted(ok);
  return retVal;
}

QString DeclarativeInputDialogAttached::getText()
{
  QWidget *parent = bestParentWindow(d->dialogParent);
  bool ok = false;

  const QString retVal = QInputDialog::getText(parent, d->title, d->label, d->echoMode, d->text, &ok);

  setDialogAccepted(ok);
  return retVal;
}

void DeclarativeInputDialogAttached::setDialogAccepted(bool accepted)
{
  if (accepted == d->dialogAccepted)
    return;

  d->dialogAccepted = accepted;
  emit dialogAcceptedChanged(accepted);
}

QWidget *DeclarativeInputDialogAttached::bestParentWindow(QObject *parent) const
{
  if (!parent)
    parent = this->parent();

  // if parent is a Declarative Object, search the proxied hierarchy
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject)
    parent = declarativeObject->object();

  while (parent) {
    QWidget *widget = qobject_cast<QWidget*>(parent);
    if (widget)
      return widget->topLevelWidget();

    parent = parent->parent();
  }

  return 0;
}

DeclarativeInputDialog::DeclarativeInputDialog(QObject *parent) : DeclarativeWidgetProxy<InputDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeInputDialogAttached *DeclarativeInputDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeInputDialogAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeInputDialog, InputDialog)

// DeclarativeLabel
DeclarativeLabel::DeclarativeLabel(QObject *parent) : DeclarativeWidgetProxy<QLabel>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeLabel, QLabel)

// DeclarativeLCDNumber
DeclarativeLCDNumber::DeclarativeLCDNumber(QObject *parent) : DeclarativeWidgetProxy<QLCDNumber>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeLCDNumber, QLCDNumber)

// DeclarativeLineEdit
DeclarativeLineEdit::DeclarativeLineEdit(QObject *parent) : DeclarativeWidgetProxy<QLineEdit>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeLineEdit, QLineEdit)

// DeclarativeListView
DeclarativeListView::DeclarativeListView(QObject *parent) : DeclarativeWidgetProxy<ListView>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeListView, ListView)

// DeclarativeMainWindow
DeclarativeMainWindow::DeclarativeMainWindow(QObject *parent) : DeclarativeWidgetProxy<QMainWindow>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeMainWindow::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  QMenuBar *menuBar = qobject_cast<QMenuBar*>(widget);
  QToolBar *toolBar = qobject_cast<QToolBar*>(widget);
  QStatusBar *statusBar = qobject_cast<QStatusBar*>(widget);
  QDialog *dialog = qobject_cast<QDialog*>(widget);

  if (menuBar) {
    m_proxiedObject->setMenuBar(menuBar);
  } else if (toolBar) {
    m_proxiedObject->addToolBar(toolBar);
  } else if (statusBar) {
    m_proxiedObject->setStatusBar(statusBar);
  } else if (dialog) {
    // We allow to place dialogs on the mainwindow
    dialog->setParent(m_proxiedObject, dialog->windowFlags());
  } else if (widget) {
    if (m_proxiedObject->centralWidget()) {
      qmlInfo(declarativeObject) << "The QMainWindow contains a central widget already";
      return;
    }

    m_proxiedObject->setCentralWidget(widget);
  }

  m_children.append(declarativeObject);
}

void DeclarativeMainWindow::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not set a QLayout to a QMainWindow";
}

CUSTOM_METAOBJECT(DeclarativeMainWindow, QMainWindow)

// DeclarativeMenu
DeclarativeMenu::DeclarativeMenu(QObject *parent) : DeclarativeWidgetProxy<QMenu>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeMenu::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  QMenu *menu = qobject_cast<QMenu*>(widget);
  if (!menu) {
    qmlInfo(declarativeObject) << "The QMenu can only contain QMenu, QAction or Separator";
    return;
  }

  m_proxiedObject->addMenu(menu);

  m_children.append(declarativeObject);
}

void DeclarativeMenu::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not set a QLayout to a QMenu";
}

void DeclarativeMenu::addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
{
  DeclarativeSeparator *separator = dynamic_cast<DeclarativeSeparator*>(declarativeObject);

  if (separator) {
    m_proxiedObject->addSeparator();
  } else {
    m_proxiedObject->addAction(action);
  }

  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeMenu, QMenu)

// DeclarativeMenuBar
DeclarativeMenuBar::DeclarativeMenuBar(QObject *parent) : DeclarativeWidgetProxy<QMenuBar>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeMenuBar::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  QMenu *menu = qobject_cast<QMenu*>(widget);
  if (!menu) {
    qmlInfo(declarativeObject) << "The QMenuBar can only contain QMenus";
    return;
  }

  m_proxiedObject->addMenu(menu);

  m_children.append(declarativeObject);
}

void DeclarativeMenuBar::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not set a QLayout to a QMenuBar";
}

void DeclarativeMenuBar::addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(action)

  DeclarativeSeparator *separator = dynamic_cast<DeclarativeSeparator*>(declarativeObject);

  if (separator) {
    m_proxiedObject->addSeparator();
  }

  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeMenuBar, QMenuBar)

// DeclarativeMessageBox
DeclarativeMessageBoxAttached::DeclarativeMessageBoxAttached(QObject *parent) : QObject(parent)
{
}

void DeclarativeMessageBoxAttached::about(QObject *parent, const QString &title, const QString &text)
{
  QMessageBox::about(bestParentWindow(parent), title, text);
}

void DeclarativeMessageBoxAttached::aboutQt(QObject *parent, const QString &title)
{
  QMessageBox::aboutQt(bestParentWindow(parent), title);
}

int DeclarativeMessageBoxAttached::critical(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::critical(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

int DeclarativeMessageBoxAttached::information(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::information(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

int DeclarativeMessageBoxAttached::question(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::question(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

int DeclarativeMessageBoxAttached::warning(QObject *parent, const QString &title, const QString &text, int buttons, int defaultButton)
{
  return QMessageBox::warning(bestParentWindow(parent), title, text, static_cast<QMessageBox::StandardButtons>(buttons), static_cast<QMessageBox::StandardButton>(defaultButton));
}

QWidget *DeclarativeMessageBoxAttached::bestParentWindow(QObject *parent) const
{
  if (!parent)
    parent = this->parent();

  // if parent is a Declarative Object, search the proxied hierarchy
  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(parent);
  if (declarativeObject)
    parent = declarativeObject->object();

  while (parent) {
    QWidget *widget = qobject_cast<QWidget*>(parent);
    if (widget)
      return widget->topLevelWidget();

    parent = parent->parent();
  }

  return 0;
}

DeclarativeMessageBox::DeclarativeMessageBox(QObject *parent) : DeclarativeObjectProxy<QMessageBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

DeclarativeMessageBoxAttached *DeclarativeMessageBox::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeMessageBoxAttached(parent);
}

CUSTOM_METAOBJECT(DeclarativeMessageBox, QMessageBox)

// DeclarativePlainTextEdit
DeclarativePlainTextEdit::DeclarativePlainTextEdit(QObject *parent) : DeclarativeWidgetProxy<QPlainTextEdit>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativePlainTextEdit, QPlainTextEdit)

// DeclarativeProgressBar
DeclarativeProgressBar::DeclarativeProgressBar(QObject *parent) : DeclarativeWidgetProxy<QProgressBar>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeProgressBar, QProgressBar)

// DeclarativePushButton
DeclarativePushButton::DeclarativePushButton(QObject *parent) : DeclarativeWidgetProxy<QPushButton>(parent)
{
  connectAllSignals(m_proxiedObject, this, QSet<QByteArray>() << "clicked()");
}

CUSTOM_METAOBJECT(DeclarativePushButton, QPushButton)

// DeclarativeRadioButton
DeclarativeRadioButton::DeclarativeRadioButton(QObject *parent) : DeclarativeWidgetProxy<QRadioButton>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeRadioButton, QRadioButton)

// DeclarativeScrollArea
DeclarativeScrollArea::DeclarativeScrollArea(QObject *parent) : DeclarativeWidgetProxy<QScrollArea>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeScrollArea::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  if (m_proxiedObject->widget()) {
    qmlInfo(declarativeObject) << "Can not add multiple Widgets to ScrollArea";
  } else {
    m_proxiedObject->setWidget(widget);
  }

  m_children.append(declarativeObject);
}

void DeclarativeScrollArea::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not add Layout to ScrollArea";
}

CUSTOM_METAOBJECT(DeclarativeScrollArea, QScrollArea)

// DeclarativeScrollBar
DeclarativeScrollBar::DeclarativeScrollBar(QObject *parent) : DeclarativeWidgetProxy<QScrollBar>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeScrollBar, QScrollBar)

// DeclarativeSlider
DeclarativeSlider::DeclarativeSlider(QObject *parent) : DeclarativeWidgetProxy<QSlider>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeSlider, QSlider)

// DeclarativeSpinBox
DeclarativeSpinBox::DeclarativeSpinBox(QObject *parent) : DeclarativeWidgetProxy<QSpinBox>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeSpinBox, QSpinBox)

// DeclarativeStackedWidget
DeclarativeStackedWidget::DeclarativeStackedWidget(QObject *parent) : DeclarativeWidgetProxy<QStackedWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeStackedWidget::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  m_proxiedObject->addWidget(widget);
  m_children.append(declarativeObject);
}

void DeclarativeStackedWidget::setLayout(QLayout*, AbstractDeclarativeObject *declarativeObject)
{
  qmlInfo(declarativeObject) << "StackedWidget does not support child layouts";
}

CUSTOM_METAOBJECT(DeclarativeStackedWidget, QStackedWidget)

// DeclarativeStatusBar
class DeclarativeStatusBarAttached::Private
{
  public:
    int stretch;
};

DeclarativeStatusBarAttached::DeclarativeStatusBarAttached(QObject *parent)
  : QObject(parent), d(new DeclarativeStatusBarAttached::Private)
{
  d->stretch = 0;
}

DeclarativeStatusBarAttached::~DeclarativeStatusBarAttached()
{
  delete d;
}

void DeclarativeStatusBarAttached::setStretch(int stretch)
{
  if (d->stretch == stretch)
    return;

  d->stretch = stretch;
  emit stretchChanged();
}

int DeclarativeStatusBarAttached::stretch() const
{
  return d->stretch;
}

DeclarativeStatusBar::DeclarativeStatusBar(QObject *parent) : DeclarativeWidgetProxy<QStatusBar>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeStatusBar::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  // TODO: error when layout is set

  m_children.append(declarativeObject);

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeStatusBar>(declarativeObject, false);
  DeclarativeStatusBarAttached *attached = qobject_cast<DeclarativeStatusBarAttached*>(attachedProperties);

  int stretch = 0;
  if (attached) {
    stretch = attached->stretch();
  }

  m_proxiedObject->addPermanentWidget(widget, stretch);
}

void DeclarativeStatusBar::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not add QLayout to QStatusBar";
}

DeclarativeStatusBarAttached *DeclarativeStatusBar::qmlAttachedProperties(QObject *object)
{
  return new DeclarativeStatusBarAttached(object);
}

CUSTOM_METAOBJECT(DeclarativeStatusBar, QStatusBar)

// DeclarativeTableView
DeclarativeTableView::DeclarativeTableView(QObject *parent) : DeclarativeWidgetProxy<TableView>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeTableView, TableView)

// DeclarativeTabWidget
class DeclarativeTabWidgetAttached::Private
{
  public:
    QString label;
    QIcon icon;
};

DeclarativeTabWidgetAttached::DeclarativeTabWidgetAttached(QObject *parent)
  : QObject(parent), d(new DeclarativeTabWidgetAttached::Private)
{
}

DeclarativeTabWidgetAttached::~DeclarativeTabWidgetAttached()
{
  delete d;
}

void DeclarativeTabWidgetAttached::setLabel(const QString &label)
{
  if (label == d->label)
    return;

  d->label = label;
  emit labelChanged(label);
}

QString DeclarativeTabWidgetAttached::label() const
{
  return d->label;
}

void DeclarativeTabWidgetAttached::setIcon(const QIcon &icon)
{
  d->icon = icon;
  emit iconChanged(icon);
}

QIcon DeclarativeTabWidgetAttached::icon() const
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
  DeclarativeTabWidgetAttached *tabHeader = qobject_cast<DeclarativeTabWidgetAttached*>(attachedProperties);
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

DeclarativeTabWidgetAttached *DeclarativeTabWidget::qmlAttachedProperties(QObject *object)
{
  return new DeclarativeTabWidgetAttached(object);
}

CUSTOM_METAOBJECT(DeclarativeTabWidget, QTabWidget)

// DeclarativeTextBrowser
DeclarativeTextBrowser::DeclarativeTextBrowser(QObject *parent) : DeclarativeWidgetProxy<QTextBrowser>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeTextBrowser, QTextBrowser)

// DeclarativeTextEdit
DeclarativeTextEdit::DeclarativeTextEdit(QObject *parent) : DeclarativeWidgetProxy<TextEdit>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeTextEdit, TextEdit)

// DeclarativeTimeEdit
DeclarativeTimeEdit::DeclarativeTimeEdit(QObject *parent) : DeclarativeWidgetProxy<QTimeEdit>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeTimeEdit, QTimeEdit)

// DeclarativeToolBar
DeclarativeToolBar::DeclarativeToolBar(QObject *parent) : DeclarativeWidgetProxy<QToolBar>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

void DeclarativeToolBar::addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
{
  m_proxiedObject->addWidget(widget);

  m_children.append(declarativeObject);
}

void DeclarativeToolBar::setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
{
  Q_UNUSED(layout);
  Q_UNUSED(declarativeObject);
  qmlInfo(this) << "Can not set a QLayout to a QToolBar";
}

void DeclarativeToolBar::addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
{
  DeclarativeSeparator *separator = dynamic_cast<DeclarativeSeparator*>(declarativeObject);

  if (separator) {
    m_proxiedObject->addSeparator();
  } else {
    m_proxiedObject->addAction(action);
  }

  m_children.append(declarativeObject);
}

CUSTOM_METAOBJECT(DeclarativeToolBar, QToolBar)

// DeclarativeToolButton
DeclarativeToolButton::DeclarativeToolButton(QObject *parent) : DeclarativeWidgetProxy<QToolButton>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeToolButton, QToolButton)

// DeclarativeTreeView
DeclarativeTreeView::DeclarativeTreeView(QObject *parent) : DeclarativeWidgetProxy<TreeView>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeTreeView, TreeView)

// DeclarativeWebView
DeclarativeWebView::DeclarativeWebView(QObject *parent) : DeclarativeWidgetProxy<QWebView>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeWebView, QWebView)

// DeclarativeWidget
DeclarativeWidget::DeclarativeWidget(QObject *parent) : DeclarativeWidgetProxy<QWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeWidget, QWidget)

