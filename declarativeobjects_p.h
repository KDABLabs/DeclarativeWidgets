#ifndef DECLARATIVEOBJECTS_H
#define DECLARATIVEOBJECTS_H

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtGui/QCheckBox>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTabWidget>
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

class DeclarativeObject : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    DeclarativeObject(QObject *parent = 0);
    virtual ~DeclarativeObject();

    virtual QObject* object() = 0;

  protected:
    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

  private:
    QDeclarativeListProperty<QObject> data();

    static void data_append(QDeclarativeListProperty<QObject> *, QObject *);
    static int data_count(QDeclarativeListProperty<QObject> *);
    static QObject *data_at(QDeclarativeListProperty<QObject> *, int);
    static void data_clear(QDeclarativeListProperty<QObject> *);
};

class DeclarativeVBoxLayout : public DeclarativeObject
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeVBoxLayout(QObject *parent = 0);
    ~DeclarativeVBoxLayout();

    virtual QObject* object();

    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

  private:
    QPointer<QVBoxLayout> m_layout;
    QVector<QObject*> m_children;
};

class DeclarativeWidget : public DeclarativeObject
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeWidget(QObject *parent = 0);
    ~DeclarativeWidget();

    virtual QObject* object();

  private:
    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

    QPointer<QWidget> m_widget;
    QVector<QObject*> m_children;
};

class DeclarativeLabel : public DeclarativeWidget
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeLabel(QObject *parent = 0);
    ~DeclarativeLabel();

    virtual QObject* object();

  private:
    QPointer<QLabel> m_label;
};

class DeclarativeTabWidget : public DeclarativeWidget
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTabWidget(QObject *parent = 0);
    ~DeclarativeTabWidget();

    virtual QObject* object();

  private:
    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

    QPointer<QTabWidget> m_tabWidget;
    QVector<QObject*> m_children;
};

class DeclarativePushButton : public DeclarativeWidget
{
  DECLARATIVE_OBJECT

  public:
    DeclarativePushButton(QObject *parent = 0);
    ~DeclarativePushButton();

    virtual QObject* object();

  private:
    QPointer<QPushButton> m_pushButton;
};

class DeclarativeCheckBox : public DeclarativeWidget
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeCheckBox(QObject *parent = 0);
    ~DeclarativeCheckBox();

    virtual QObject* object();

  private:
    QPointer<QCheckBox> m_checkBox;
};

#endif
