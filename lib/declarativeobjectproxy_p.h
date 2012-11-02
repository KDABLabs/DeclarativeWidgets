/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef DECLARATIVEOBJECTPROXY_P_H
#define DECLARATIVEOBJECTPROXY_P_H

#include "abstractdeclarativeobject_p.h"

#include <qdeclarative.h>
#include <QDeclarativeInfo>
#include <QPointer>
#include <QVector>

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


template <class T, bool needsParentInitialization = false>
class DeclarativeObjectProxy : public AbstractDeclarativeObject
{
};

template <class T>
class DeclarativeObjectProxy<T, false> : public AbstractDeclarativeObject
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
class DeclarativeObjectProxy<T, true> : public AbstractDeclarativeObject
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

//TODO: Find a solution to make the macro public but the usage of QMetaObjectBuilder private

#include "qmetaobjectbuilder_p.h"

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

#endif
