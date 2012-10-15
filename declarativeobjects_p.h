#ifndef DECLARATIVEOBJECTS_H
#define DECLARATIVEOBJECTS_H

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtDeclarative/QDeclarativeListProperty>

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
    DeclarativeObjectProxy(QObject *parent = 0) : AbstractDeclarativeObject(parent), m_proxiedObject(new T) {}

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

class DeclarativeWidget : public DeclarativeObjectProxy<QWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeWidget(QObject *parent = 0);

  protected:
    virtual void dataAppend(QObject *);
};

class DeclarativeLabel : public DeclarativeObjectProxy<QLabel>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeLabel(QObject *parent = 0);
};

class DeclarativeTabWidget : public DeclarativeObjectProxy<QTabWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTabWidget(QObject *parent = 0);

  protected:
    virtual void dataAppend(QObject *);
};
/*
class DeclarativeTab : public DeclarativeWidget
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTab(QObject *parent = 0);
    ~DeclarativeTab();

    virtual QObject* object();

  private:
    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

    QObject* m_child;
};
*/
class DeclarativePushButton : public DeclarativeObjectProxy<QPushButton>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativePushButton(QObject *parent = 0);
};

class DeclarativeCheckBox : public DeclarativeObjectProxy<QCheckBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeCheckBox(QObject *parent = 0);
};

class DeclarativeSlider : public DeclarativeObjectProxy<QSlider>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeSlider(QObject *parent = 0);
};

#endif
