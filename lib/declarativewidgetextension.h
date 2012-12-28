#ifndef DECLARATIVEWIDGETEXTENSION_H
#define DECLARATIVEWIDGETEXTENSION_H

#include "declarativeobjectextension.h"

class QAction;
class QLayout;
class QWidget;

class DeclarativeWidgetExtension : public DeclarativeObjectExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    DeclarativeWidgetExtension(QObject *parent);

    QWidget *extendedWidget() const;

  protected:
    void dataAppend(QObject *object);

    virtual void addAction(QAction *action);
    virtual void setLayout(QLayout *layout);
    virtual void addWidget(QWidget *widget);
};

#endif // DECLARATIVEWIDGETEXTENSION_H
