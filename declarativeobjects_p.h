#ifndef DECLARATIVEOBJECTS_H
#define DECLARATIVEOBJECTS_H

#include <QtCore/QObject>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTabWidget>
#include <QtDeclarative/QDeclarativeListProperty>

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
  Q_OBJECT

  public:
    DeclarativeVBoxLayout(QObject *parent = 0);
    ~DeclarativeVBoxLayout();

    virtual QObject* object();

    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

  private:
    QVBoxLayout* m_layout;
    QVector<QObject*> m_children;
};

class DeclarativeWidget : public DeclarativeObject
{
  Q_OBJECT

  public:
    DeclarativeWidget(QObject *parent = 0);
    ~DeclarativeWidget();

    virtual QObject* object();

  private:
    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

    QWidget* m_widget;
    QVector<QObject*> m_children;
};

class DeclarativeLabel : public DeclarativeWidget
{
  Q_OBJECT

  public:
    DeclarativeLabel(QObject *parent = 0);
    ~DeclarativeLabel();

    virtual QObject* object();

  private:
    QLabel* m_label;
};

class DeclarativeTabWidget : public DeclarativeWidget
{
  Q_OBJECT

  public:
    DeclarativeTabWidget(QObject *parent = 0);

    virtual QObject* object();

  private:
    virtual void dataAppend(QObject *);
    virtual int dataCount();
    virtual QObject *dataAt(int);
    virtual void dataClear();

    QVector<QObject*> m_children;
    QTabWidget* m_tabWidget;
};

#endif
