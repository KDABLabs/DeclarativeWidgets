#ifndef DECLARATIVELAYOUTEXTENSION_H
#define DECLARATIVELAYOUTEXTENSION_H

#include "declarativeobjectextension.h"

class QLayout;
class QWidget;

class DeclarativeLayoutExtension : public DeclarativeObjectExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    DeclarativeLayoutExtension(QObject *parent);

    QLayout *extendedLayout() const;

  protected:
    void dataAppend(QObject *object);

    virtual void addLayout(QLayout *layout) = 0;
    virtual void addWidget(QWidget *widget) = 0;
};

#endif // DECLARATIVELAYOUTEXTENSION_H
