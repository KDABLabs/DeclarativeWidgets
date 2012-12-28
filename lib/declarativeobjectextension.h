#ifndef DECLARATIVEOBJECTEXTENSION_H
#define DECLARATIVEOBJECTEXTENSION_H

#include <QDeclarativeListProperty>
#include <QObject>

class DeclarativeObjectExtension : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeObjectExtension(QObject *parent = 0);
    ~DeclarativeObjectExtension();

    QObject *extendedObject() const { return parent(); }

  protected:
    QObjectList m_children;

    virtual void dataAppend(QObject *object);
    virtual int dataCount() const;
    virtual QObject *dataAt(int index) const;
    virtual void dataClear();

    QDeclarativeListProperty<QObject> data();

  private:
    static void data_append(QDeclarativeListProperty<QObject> *, QObject *);
    static int data_count(QDeclarativeListProperty<QObject> *);
    static QObject *data_at(QDeclarativeListProperty<QObject> *, int);
    static void data_clear(QDeclarativeListProperty<QObject> *);
};

#endif // DECLARATIVEOBJECTEXTENSION_H
