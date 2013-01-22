#ifndef DECLARATIVEWIDGETEXTENSION_H
#define DECLARATIVEWIDGETEXTENSION_H

#include "declarativeobjectextension.h"

#include <QRect>

class QAction;
class QLayout;
class QWidget;

class DeclarativeWidgetExtension : public DeclarativeObjectExtension
{
  Q_OBJECT

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_PROPERTY(int x READ x WRITE setX NOTIFY posChanged)
  Q_PROPERTY(int y READ y WRITE setY NOTIFY posChanged)
  Q_PROPERTY(int width READ width WRITE setWidth NOTIFY sizeChanged)
  Q_PROPERTY(int height READ height WRITE setHeight NOTIFY sizeChanged)
  Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    DeclarativeWidgetExtension(QObject *parent);

    QWidget *extendedWidget() const;

    int x() const;
    void setX(int value);

    int y() const;
    void setY(int value);

    int width() const;
    void setWidth(int value);

    int height() const;
    void setHeight(int value);

    QRect geometry() const;
    void setGeometry(const QRect &rect);

    bool eventFilter(QObject *watched, QEvent *event);

  Q_SIGNALS:
    void posChanged();
    void sizeChanged();
    void geometryChanged();

  protected:
    void dataAppend(QObject *object);

    virtual void addAction(QAction *action);
    virtual void setLayout(QLayout *layout);
    virtual void addWidget(QWidget *widget);
};

#endif // DECLARATIVEWIDGETEXTENSION_H
