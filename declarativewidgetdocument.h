#ifndef DECLARATIVEWIDGETDOCUMENT_H
#define DECLARATIVEWIDGETDOCUMENT_H

#include <QtCore/QObject>
#include <QtCore/QUrl>

class QDeclarativeEngine;

class DeclarativeWidgetDocument : public QObject
{
  Q_OBJECT

  public:
    DeclarativeWidgetDocument(const QUrl &url, QObject *parent = 0);
    ~DeclarativeWidgetDocument();

    void setContextProperty(const QString &name, const QVariant &value);
    void setContextProperty(const QString &name, QObject *object);

    QDeclarativeEngine* engine() const;

    template <typename T>
    T* create()
    {
      QWidget *widget = createWidget();
      if (!widget)
        return 0;

      return qobject_cast<T*>(widget);
    }

  private:
    QWidget* createWidget();

    class Private;
    Private* const d;
};

#endif
