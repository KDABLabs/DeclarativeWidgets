#include "declarativelayoutextension.h"

#include <QLayout>
#include <QWidget>

DeclarativeLayoutExtension::DeclarativeLayoutExtension(QObject *parent)
  : DeclarativeObjectExtension(parent)
{
  parent->setParent(0); // otherwise first call to parentWidget() will complain about wrong parent class
}

QLayout *DeclarativeLayoutExtension::extendedLayout() const
{
  QLayout *parentLayout = qobject_cast<QLayout*>(parent());
  Q_ASSERT(parentLayout);
  Q_UNUSED(parentLayout);

  return parentLayout;
}

void DeclarativeLayoutExtension::dataAppend(QObject *object)
{
  DeclarativeObjectExtension::dataAppend(object);

  QWidget *widget = qobject_cast<QWidget*>(object);
  if (widget) {
    addWidget(widget);
    return;
  }

  QLayout *layout = qobject_cast<QLayout*>(object);
  if (layout) {
    addLayout(layout);
    return;
  }
}
