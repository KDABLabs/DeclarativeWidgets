#ifndef DECLARATIVEOBJECTS_H
#define DECLARATIVEOBJECTS_H

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtGui/QAction>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtDeclarative/QDeclarativeListProperty>
#include <QtDeclarative/qdeclarativeinfo.h>
#include <qdeclarative.h>

#define DECLARATIVE_OBJECT \
  public: \
    Q_OBJECT_CHECK \
    static QMetaObject staticMetaObject; \
    static bool metaObjectInitialized; \
    static bool initializeMetaObject(); \
    static const QMetaObject &getStaticMetaObject(); \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char *); \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
  private: \

class AbstractDeclarativeObject : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    AbstractDeclarativeObject(QObject *parent = 0);
    virtual ~AbstractDeclarativeObject();

    virtual QObject* object() const = 0;

  protected:
    virtual void dataAppend(QObject *);
    virtual int dataCount() const;
    virtual QObject *dataAt(int) const;
    virtual void dataClear();

  private:
    QDeclarativeListProperty<QObject> data();

    static void data_append(QDeclarativeListProperty<QObject> *, QObject *);
    static int data_count(QDeclarativeListProperty<QObject> *);
    static QObject *data_at(QDeclarativeListProperty<QObject> *, int);
    static void data_clear(QDeclarativeListProperty<QObject> *);
};

template <class T>
class DeclarativeObjectProxy : public AbstractDeclarativeObject
{
  public:
    DeclarativeObjectProxy(QObject *parent = 0) : AbstractDeclarativeObject(parent), m_proxiedObject(new T(0)) {}

    ~DeclarativeObjectProxy() { delete m_proxiedObject; }

    virtual QObject *object() const { return m_proxiedObject.data(); }

  protected:
    virtual void dataAppend(QObject *object)
    {
      m_children.append(object);
    }

    virtual int dataCount() const { return m_children.count(); }
    virtual QObject *dataAt(int index) const { return m_children.at(index); }
    virtual void dataClear()
    {
      qDeleteAll(m_children);
      m_children.clear();
    }

  protected:
    QPointer<T> m_proxiedObject;
    QVector<QObject*> m_children;
};

template <class T>
class DeclarativeWidgetProxy : public DeclarativeObjectProxy<T>
{
  public:
    DeclarativeWidgetProxy(QObject *parent = 0) : DeclarativeObjectProxy<T>(parent) {}

  protected:
    virtual void dataAppend(QObject *object)
    {
        AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
        if (declarativeObject) {
          QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
          if (widget) {
            addWidget(widget, declarativeObject);
            return;
          }

          QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
          if (layout) {
            // TODO: error when widget is set

            if (DeclarativeObjectProxy<T>::m_proxiedObject->layout()) {
              qmlInfo(this) << "Can not add a second Layout";
              return;
            }

            setLayout(layout, declarativeObject);
            return;
          }

          QAction *action = qobject_cast<QAction*>(declarativeObject->object());
          if (action) {
            addAction(action, declarativeObject);
            return;
          }

          addQObject(declarativeObject->object(), declarativeObject);
          return;
        }

        DeclarativeObjectProxy<T>::dataAppend(object);
    }

    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
    {
      Q_UNUSED(declarativeObject);
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      widget->setParent(DeclarativeObjectProxy<T>::m_proxiedObject);
    }

    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->setLayout(layout);
    }

    virtual void addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->addAction(action);
    }

    virtual void addQObject(QObject *object, AbstractDeclarativeObject *declarativeObject)
    {
      object->setParent(DeclarativeObjectProxy<T>::m_proxiedObject);
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
    }
};

//// Objects ///
class DeclarativeAction : public DeclarativeObjectProxy<QAction>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeAction(QObject *parent = 0);
};

//// Layouts ////
template <class T>
class DeclarativeBoxLayout : public DeclarativeObjectProxy<T>
{
  public:
    DeclarativeBoxLayout(QObject *parent = 0) : DeclarativeObjectProxy<T>(parent) {}

  protected:
    virtual void dataAppend(QObject *object)
    {
      AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
      if (declarativeObject) {
        QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
        if (widget) {
          DeclarativeObjectProxy<T>::m_children.append(object);
          DeclarativeObjectProxy<T>::m_proxiedObject->addWidget(widget);
          return;
        }

        QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
        if (layout) {
          DeclarativeObjectProxy<T>::m_children.append(object);
          DeclarativeObjectProxy<T>::m_proxiedObject->addLayout(layout);
          return;
        }
      }

      DeclarativeObjectProxy<T>::dataAppend(object);
    }
};

class DeclarativeHBoxLayout : public DeclarativeBoxLayout<QHBoxLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeHBoxLayout(QObject *parent = 0);
};

class DeclarativeVBoxLayout : public DeclarativeBoxLayout<QVBoxLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeVBoxLayout(QObject *parent = 0);
};

//// Widgets ////
class DeclarativeCalendarWidget : public DeclarativeWidgetProxy<QCalendarWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeCalendarWidget(QObject *parent = 0);
};

class DeclarativeCheckBox : public DeclarativeWidgetProxy<QCheckBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeCheckBox(QObject *parent = 0);
};

class DeclarativeLabel : public DeclarativeWidgetProxy<QLabel>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeLabel(QObject *parent = 0);
};

class DeclarativeMainWindow : public DeclarativeWidgetProxy<QMainWindow>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMainWindow(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativeMenu : public DeclarativeWidgetProxy<QMenu>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMenu(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativeMenuBar : public DeclarativeWidgetProxy<QMenuBar>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMenuBar(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativePushButton : public DeclarativeWidgetProxy<QPushButton>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativePushButton(QObject *parent = 0);
};

class DeclarativeSlider : public DeclarativeWidgetProxy<QSlider>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeSlider(QObject *parent = 0);
};

// attached property for DeclarativeTabWidget
class TabWidgetTabHeader : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
  Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)

  public:
    TabWidgetTabHeader(QObject *parent = 0);
    ~TabWidgetTabHeader();

    void setLabel(const QString &label);
    QString label() const;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

  Q_SIGNALS:
    void labelChanged(const QString &label);
    void iconChanged(const QIcon &icon);

  private:
    class Private;
    Private *const d;
};

class DeclarativeTabWidget : public DeclarativeWidgetProxy<QTabWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTabWidget(QObject *parent = 0);

    static TabWidgetTabHeader *qmlAttachedProperties(QObject *object);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeTabWidget, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeTextEdit : public DeclarativeWidgetProxy<QTextEdit>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTextEdit(QObject *parent = 0);
};

class DeclarativeToolBar : public DeclarativeWidgetProxy<QToolBar>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeToolBar(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativeWidget : public DeclarativeWidgetProxy<QWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeWidget(QObject *parent = 0);
};

#endif
