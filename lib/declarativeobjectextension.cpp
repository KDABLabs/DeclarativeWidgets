#include "declarativeobjectextension.h"

DeclarativeObjectExtension::DeclarativeObjectExtension(QObject *parent)
  : QObject(parent)
{
}

DeclarativeObjectExtension::~DeclarativeObjectExtension()
{
}

QDeclarativeListProperty<QObject> DeclarativeObjectExtension::data()
{
  return QDeclarativeListProperty<QObject>(this, 0, DeclarativeObjectExtension::data_append,
                                                    DeclarativeObjectExtension::data_count,
                                                    DeclarativeObjectExtension::data_at,
                                                    DeclarativeObjectExtension::data_clear);
}

void DeclarativeObjectExtension::dataAppend(QObject *object)
{
  m_children.append(object);
}

int DeclarativeObjectExtension::dataCount() const
{
  return m_children.count();
}

QObject* DeclarativeObjectExtension::dataAt(int index) const
{
  return m_children.at(index);
}

void DeclarativeObjectExtension::dataClear()
{
  m_children.clear();
}

void DeclarativeObjectExtension::data_append(QDeclarativeListProperty<QObject> *property, QObject *object)
{
  if (!object)
    return;

  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    that->dataAppend(object);
  else
    qWarning("cast went wrong in data_append");
}

int DeclarativeObjectExtension::data_count(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    return that->dataCount();
  else {
    qWarning("cast went wrong in data_count");
    return 0;
  }
}

QObject* DeclarativeObjectExtension::data_at(QDeclarativeListProperty<QObject> *property, int index)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    return that->dataAt(index);
  else {
    qWarning("cast went wrong in data_at");
    return 0;
  }
}

void DeclarativeObjectExtension::data_clear(QDeclarativeListProperty<QObject> *property)
{
  DeclarativeObjectExtension *that = qobject_cast<DeclarativeObjectExtension*>(property->object);
  if (that)
    that->dataClear();
  else
    qWarning("cast went wrong in data_clear");
}
