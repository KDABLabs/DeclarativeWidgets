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
DeclarativeAction::DeclarativeAction(QObject *parent) : DeclarativeObjectProxy<QAction>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeAction, QAction)

// DeclarativeSeparator
DeclarativeSeparator::DeclarativeSeparator(QObject *parent) : DeclarativeObjectProxy<QAction>(parent)
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
DeclarativeColorDialog::DeclarativeColorDialog(QObject *parent) : DeclarativeWidgetProxy<QColorDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeColorDialog, QColorDialog)

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

// DeclarativeFileDialog
DeclarativeFileDialog::DeclarativeFileDialog(QObject *parent) : DeclarativeWidgetProxy<FileDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeFileDialog, FileDialog)

// DeclarativeFontDialog
DeclarativeFontDialog::DeclarativeFontDialog(QObject *parent) : DeclarativeWidgetProxy<QFontDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeFontDialog, QFontDialog)

// DeclarativeInputDialog
DeclarativeInputDialog::DeclarativeInputDialog(QObject *parent) : DeclarativeWidgetProxy<InputDialog>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeInputDialog, InputDialog)

// DeclarativeLabel
DeclarativeLabel::DeclarativeLabel(QObject *parent) : DeclarativeWidgetProxy<QLabel>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeLabel, QLabel)

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

// DeclarativePushButton
DeclarativePushButton::DeclarativePushButton(QObject *parent) : DeclarativeWidgetProxy<QPushButton>(parent)
{
  connectAllSignals(m_proxiedObject, this, QSet<QByteArray>() << "clicked()");
}

CUSTOM_METAOBJECT(DeclarativePushButton, QPushButton)

// DeclarativeSlider
DeclarativeSlider::DeclarativeSlider(QObject *parent) : DeclarativeWidgetProxy<QSlider>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeSlider, QSlider)

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

// DeclarativeTextEdit
DeclarativeTextEdit::DeclarativeTextEdit(QObject *parent) : DeclarativeWidgetProxy<TextEdit>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeTextEdit, TextEdit)

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

// DeclarativeWidget
DeclarativeWidget::DeclarativeWidget(QObject *parent) : DeclarativeWidgetProxy<QWidget>(parent)
{
  connectAllSignals(m_proxiedObject, this);
}

CUSTOM_METAOBJECT(DeclarativeWidget, QWidget)

