#ifndef DECLARATIVEOBJECTS_H
#define DECLARATIVEOBJECTS_H

#include "objectadaptors_p.h"

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtGui/QAction>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QColorDialog>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDial>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFontDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtWebKit/QWebView>
#include <QtDeclarative/QDeclarativeListProperty>
#include <QtDeclarative/qdeclarativeinfo.h>
#include <qdeclarative.h>

#include "objectadaptors_p.h"

Q_DECLARE_METATYPE(QAction*)

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

class AbstractDeclarativeObject : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    AbstractDeclarativeObject(QObject *parent = 0);
    virtual ~AbstractDeclarativeObject();

    virtual QObject* object() const = 0;

  protected:
    virtual void dataAppend(QObject *);
    virtual int dataCount() const;
    virtual QObject *dataAt(int) const;
    virtual void dataClear();

  private:
    QDeclarativeListProperty<QObject> data();

    static void data_append(QDeclarativeListProperty<QObject> *, QObject *);
    static int data_count(QDeclarativeListProperty<QObject> *);
    static QObject *data_at(QDeclarativeListProperty<QObject> *, int);
    static void data_clear(QDeclarativeListProperty<QObject> *);
};

template <class T>
class DeclarativeObjectProxy : public AbstractDeclarativeObject
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

class DeclarativeActionItem : public DeclarativeObjectProxy<ActionItem>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeActionItem(QObject *parent = 0);
};

template <class T>
class DeclarativeWidgetProxy : public DeclarativeObjectProxy<T>
{
  public:
    DeclarativeWidgetProxy(QObject *parent = 0) : DeclarativeObjectProxy<T>(parent) {}

  protected:
    virtual void dataAppend(QObject *object)
    {
        AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
        if (declarativeObject) {
          QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
          if (widget) {
            addWidget(widget, declarativeObject);
            return;
          }

          QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
          if (layout) {
            // TODO: error when widget is set

            if (DeclarativeObjectProxy<T>::m_proxiedObject->layout()) {
              qmlInfo(this) << "Can not add a second Layout";
              return;
            }

            setLayout(layout, declarativeObject);
            return;
          }

          DeclarativeActionItem *declarativeActionItem = dynamic_cast<DeclarativeActionItem*>(object);
          if (declarativeActionItem) {
            addAction(qobject_cast<ActionItem*>(declarativeActionItem->object())->action(), declarativeObject);
            return;
          }

          QAction *action = qobject_cast<QAction*>(declarativeObject->object());
          if (action) {
            addAction(action, declarativeObject);
            return;
          }

          addQObject(declarativeObject->object(), declarativeObject);
          return;
        }

        DeclarativeObjectProxy<T>::dataAppend(object);
    }

    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
    {
      Q_UNUSED(declarativeObject);
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      widget->setParent(DeclarativeObjectProxy<T>::m_proxiedObject, widget->windowFlags());
    }

    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->setLayout(layout);
    }

    virtual void addAction(QAction *action, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->addAction(action);
    }

    virtual void addQObject(QObject *object, AbstractDeclarativeObject *declarativeObject)
    {
      object->setParent(DeclarativeObjectProxy<T>::m_proxiedObject);
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
    }
};

template <class T>
class DeclarativeLayoutProxy : public DeclarativeObjectProxy<T>
{
  public:
    DeclarativeLayoutProxy(QObject *parent = 0) : DeclarativeObjectProxy<T>(parent) {}

  protected:
    virtual void dataAppend(QObject *object)
    {
      AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
      if (declarativeObject) {
        QWidget *widget = qobject_cast<QWidget*>(declarativeObject->object());
        if (widget) {
          addWidget(widget, declarativeObject);
          return;
        }

        QLayout *layout = qobject_cast<QLayout*>(declarativeObject->object());
        if (layout) {
          addLayout(layout, declarativeObject);
          return;
        }
      }

      DeclarativeObjectProxy<T>::dataAppend(object);
    }

    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject)
    {
      DeclarativeObjectProxy<T>::m_children.append(declarativeObject);
      DeclarativeObjectProxy<T>::m_proxiedObject->addWidget(widget);
    }

    virtual void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject) = 0;
};

//// Objects ///
class DeclarativeAction : public DeclarativeObjectProxy<QAction>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeAction(QObject *parent = 0);
};
Q_DECLARE_METATYPE(DeclarativeAction*)

class DeclarativeSeparator : public DeclarativeObjectProxy<QAction>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeSeparator(QObject *parent = 0);
};

//// Layouts ////
class DeclarativeBoxLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int stretch READ stretch WRITE setStretch NOTIFY stretchChanged)
  Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

  public:
    DeclarativeBoxLayoutAttached(QWidget *widget, QObject *parent);
    DeclarativeBoxLayoutAttached(QLayout *layout, QObject *parent);
    ~DeclarativeBoxLayoutAttached();

    void setParentLayout(QBoxLayout *parentLayout);

    void setStretch(int stretch);
    int stretch() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    Q_INVOKABLE QString foo() const { qDebug() << Q_FUNC_INFO; return "foo"; }

  Q_SIGNALS:
    void stretchChanged(int stretch);
    void alignmentChanged(Qt::Alignment alignment);

  private:
    class Private;
    Private *const d;
};

class DeclarativeFormLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

  public:
    DeclarativeFormLayoutAttached(QObject *parent);
    ~DeclarativeFormLayoutAttached();

    void setLabel(const QString &label);
    QString label() const;

  Q_SIGNALS:
    void labelChanged(const QString &label);

  private:
    class Private;
    Private *const d;
};

class DeclarativeGridLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
  Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
  Q_PROPERTY(int rowSpan READ rowSpan WRITE setRowSpan NOTIFY rowSpanChanged)
  Q_PROPERTY(int columnSpan READ columnSpan WRITE setColumnSpan NOTIFY columnSpanChanged)
  Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

  public:
    DeclarativeGridLayoutAttached(QWidget *widget, QObject *parent);
    DeclarativeGridLayoutAttached(QLayout *layout, QObject *parent);
    ~DeclarativeGridLayoutAttached();

    void setParentLayout(QGridLayout *parentLayout);

    void setRow(int row);
    int row() const;

    void setColumn(int column);
    int column() const;

    void setRowSpan(int rowSpan);
    int rowSpan() const;

    void setColumnSpan(int columnSpan);
    int columnSpan() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

  Q_SIGNALS:
    void rowChanged(int row);
    void columnChanged(int column);
    void rowSpanChanged(int rowSpan);
    void columnSpanChanged(int columnSpan);
    void alignmentChanged(Qt::Alignment alignment);

  private:
    class Private;
    Private *const d;
};

class DeclarativeFormLayout : public DeclarativeLayoutProxy<QFormLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeFormLayout(QObject *parent = 0);

    static DeclarativeFormLayoutAttached *qmlAttachedProperties(QObject *parent);

  protected:
    void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeFormLayout, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeGridLayout : public DeclarativeLayoutProxy<QGridLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeGridLayout(QObject *parent = 0);

    static DeclarativeGridLayoutAttached *qmlAttachedProperties(QObject *parent);

  protected:
    void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeGridLayout, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeHBoxLayout : public DeclarativeLayoutProxy<QHBoxLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeHBoxLayout(QObject *parent = 0);

    static DeclarativeBoxLayoutAttached *qmlAttachedProperties(QObject *parent);

  protected:
    void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};


QML_DECLARE_TYPEINFO(DeclarativeHBoxLayout, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeVBoxLayout : public DeclarativeLayoutProxy<QVBoxLayout>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeVBoxLayout(QObject *parent = 0);

    static DeclarativeBoxLayoutAttached *qmlAttachedProperties(QObject *parent);

  protected:
    void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeVBoxLayout, QML_HAS_ATTACHED_PROPERTIES)

//// Widgets ////
class DeclarativeCalendarWidget : public DeclarativeWidgetProxy<QCalendarWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeCalendarWidget(QObject *parent = 0);
};

class DeclarativeCheckBox : public DeclarativeWidgetProxy<QCheckBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeCheckBox(QObject *parent = 0);
};

class DeclarativeColorDialogAttached : public QObject
{
  Q_OBJECT

  public:
    DeclarativeColorDialogAttached(QObject *parent = 0);

    Q_INVOKABLE QColor getColor(const QColor &initialColor, QObject *parent, const QString &title, int options = 0);
    Q_INVOKABLE QColor getColor(const QColor &initialColor, QObject *parent = 0);

  private:
    QWidget *bestParentWindow(QObject *parent) const;
};

class DeclarativeColorDialog : public DeclarativeWidgetProxy<QColorDialog>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeColorDialog(QObject *parent = 0);

    static DeclarativeColorDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeColorDialog, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeCommandLinkButton : public DeclarativeWidgetProxy<QCommandLinkButton>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeCommandLinkButton(QObject *parent = 0);
};

class DeclarativeDateEdit : public DeclarativeWidgetProxy<QDateEdit>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeDateEdit(QObject *parent = 0);
};

class DeclarativeDateTimeEdit : public DeclarativeWidgetProxy<QDateTimeEdit>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeDateTimeEdit(QObject *parent = 0);
};

class DeclarativeDial : public DeclarativeWidgetProxy<QDial>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeDial(QObject *parent = 0);
};

class DeclarativeDialog : public DeclarativeWidgetProxy<QDialog>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeDialog(QObject *parent = 0);
};

class DeclarativeDialogButtonBox : public DeclarativeWidgetProxy<QDialogButtonBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeDialogButtonBox(QObject *parent = 0);
};

class DeclarativeDoubleSpinBox : public DeclarativeWidgetProxy<QDoubleSpinBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeDoubleSpinBox(QObject *parent = 0);
};

class DeclarativeFileDialogAttached : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QObject* parent READ dialogParent WRITE setDialogParent NOTIFY dialogParentChanged)
  Q_PROPERTY(QString caption READ caption WRITE setCaption NOTIFY captionChanged)
  Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
  Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
  // TODO dialog option
  Q_PROPERTY(QString selectedFilter READ selectedFilter NOTIFY selectedFilterChanged)

  public:
    DeclarativeFileDialogAttached(QObject *parent = 0);
    ~DeclarativeFileDialogAttached();

    void setDialogParent(QObject *parent);
    QObject *dialogParent() const;

    void setCaption(const QString &caption);
    QString caption() const;

    void setDir(const QString &dir);
    QString dir() const;

    void setNameFilters(const QStringList &nameFilters);
    QStringList nameFilters() const;

    QString selectedFilter() const;

    Q_INVOKABLE QString getExistingDirectory();

    Q_INVOKABLE QString getOpenFileName();

    Q_INVOKABLE QStringList getOpenFileNames();

    Q_INVOKABLE QString getSaveFileName();

  Q_SIGNALS:
    void dialogParentChanged(QObject *parent);
    void captionChanged(const QString &caption);
    void dirChanged(const QString &dir);
    void nameFiltersChanged(const QStringList &filters);
    void selectedFilterChanged(const QString &filter);

  private:
    QWidget *bestParentWindow(QObject *parent) const;
    void setSelectedFilter(const QString &filter);

    class Private;
    Private *const d;
};

class DeclarativeFileDialog : public DeclarativeWidgetProxy<FileDialog>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeFileDialog(QObject *parent = 0);

    static DeclarativeFileDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeFileDialog, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeFontDialog : public DeclarativeWidgetProxy<QFontDialog>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeFontDialog(QObject *parent = 0);
};

class DeclarativeFrame : public DeclarativeWidgetProxy<QFrame>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeFrame(QObject *parent = 0);
};

class DeclarativeGroupBox : public DeclarativeWidgetProxy<QGroupBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeGroupBox(QObject *parent = 0);
};

class DeclarativeInputDialogAttached : public QObject
{
  Q_OBJECT

  public:
    DeclarativeInputDialogAttached(QObject *parent = 0);

    Q_INVOKABLE double getDouble(QObject *parent, const QString &title, const QString &label,
                                 double value = 0, double min = -2147483647, double max = 2147483647, int decimals = 1);

    Q_INVOKABLE int getInt(QObject *parent, const QString &title, const QString &label,
                           int value = 0, int min = -2147483647, int max = 2147483647, int step = 1);

    Q_INVOKABLE QString getItem(QObject *parent, const QString &title, const QString &label,
                                const QStringList &items, int current = 0, bool editable = true);

    Q_INVOKABLE QString getText(QObject *parent, const QString &title, const QString &label,
                                int echoMode = QLineEdit::Normal, const QString &text = QString());

  private:
    QWidget *bestParentWindow(QObject *parent) const;
};

class DeclarativeInputDialog : public DeclarativeWidgetProxy<InputDialog>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeInputDialog(QObject *parent = 0);

    static DeclarativeInputDialogAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeInputDialog, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeLabel : public DeclarativeWidgetProxy<QLabel>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeLabel(QObject *parent = 0);
};

class DeclarativeLineEdit : public DeclarativeWidgetProxy<QLineEdit>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeLineEdit(QObject *parent = 0);
};

class DeclarativeMainWindow : public DeclarativeWidgetProxy<QMainWindow>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMainWindow(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativeMenu : public DeclarativeWidgetProxy<QMenu>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMenu(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
    virtual void addAction(QAction *action, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativeMenuBar : public DeclarativeWidgetProxy<QMenuBar>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMenuBar(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
    virtual void addAction(QAction *action, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativeMessageBoxAttached : public QObject
{
  Q_OBJECT

  public:
    DeclarativeMessageBoxAttached(QObject *parent = 0);

    Q_INVOKABLE void about(QObject *parent, const QString &title, const QString &text);
    Q_INVOKABLE void aboutQt(QObject *parent, const QString &title);
    Q_INVOKABLE int critical(QObject *parent, const QString &title, const QString &text,
                             int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);
    Q_INVOKABLE int information(QObject *parent, const QString &title, const QString &text,
                                int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);
    Q_INVOKABLE int question(QObject *parent, const QString &title, const QString &text,
                             int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);
    Q_INVOKABLE int warning(QObject *parent, const QString &title, const QString &text,
                            int buttons = QMessageBox::Ok, int defaultButton = QMessageBox::NoButton);

  private:
    QWidget *bestParentWindow(QObject *parent) const;
};

class DeclarativeMessageBox : public DeclarativeObjectProxy<QMessageBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeMessageBox(QObject *parent = 0);

    static DeclarativeMessageBoxAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(DeclarativeMessageBox, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativePlainTextEdit : public DeclarativeWidgetProxy<QPlainTextEdit>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativePlainTextEdit(QObject *parent = 0);
};

class DeclarativePushButton : public DeclarativeWidgetProxy<QPushButton>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativePushButton(QObject *parent = 0);
};

class DeclarativeRadioButton : public DeclarativeWidgetProxy<QRadioButton>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeRadioButton(QObject *parent = 0);
};

class DeclarativeScrollBar : public DeclarativeWidgetProxy<QScrollBar>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeScrollBar(QObject *parent = 0);
};

class DeclarativeSlider : public DeclarativeWidgetProxy<QSlider>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeSlider(QObject *parent = 0);
};

class DeclarativeSpinBox : public DeclarativeWidgetProxy<QSpinBox>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeSpinBox(QObject *parent = 0);
};

// attached property for DeclarativeStatusBar
class DeclarativeStatusBarAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int stretch READ stretch WRITE setStretch NOTIFY stretchChanged)

  public:
    DeclarativeStatusBarAttached(QObject *parent = 0);
    ~DeclarativeStatusBarAttached();

    void setStretch(int stretch);
    int stretch() const;

  Q_SIGNALS:
    void stretchChanged();

  private:
    class Private;
    Private *const d;
};

class DeclarativeStatusBar : public DeclarativeWidgetProxy<QStatusBar>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeStatusBar(QObject *parent = 0);

    static DeclarativeStatusBarAttached *qmlAttachedProperties(QObject *object);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeStatusBar, QML_HAS_ATTACHED_PROPERTIES)

// attached property for DeclarativeTabWidget
class DeclarativeTabWidgetAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
  Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)

  public:
    DeclarativeTabWidgetAttached(QObject *parent = 0);
    ~DeclarativeTabWidgetAttached();

    void setLabel(const QString &label);
    QString label() const;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

  Q_SIGNALS:
    void labelChanged(const QString &label);
    void iconChanged(const QIcon &icon);

  private:
    class Private;
    Private *const d;
};

class DeclarativeTabWidget : public DeclarativeWidgetProxy<QTabWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTabWidget(QObject *parent = 0);

    static DeclarativeTabWidgetAttached *qmlAttachedProperties(QObject *object);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeTabWidget, QML_HAS_ATTACHED_PROPERTIES)

class DeclarativeTextBrowser : public DeclarativeWidgetProxy<QTextBrowser>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTextBrowser(QObject *parent = 0);
};

class DeclarativeTextEdit : public DeclarativeWidgetProxy<TextEdit>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTextEdit(QObject *parent = 0);
};

class DeclarativeTimeEdit : public DeclarativeWidgetProxy<QTimeEdit>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeTimeEdit(QObject *parent = 0);
};

class DeclarativeToolBar : public DeclarativeWidgetProxy<QToolBar>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeToolBar(QObject *parent = 0);

  protected:
    virtual void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    virtual void setLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
    virtual void addAction(QAction *action, AbstractDeclarativeObject *declarativeObject);
};

class DeclarativeToolButton : public DeclarativeWidgetProxy<QToolButton>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeToolButton(QObject *parent = 0);
};

class DeclarativeWebView : public DeclarativeWidgetProxy<QWebView>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeWebView(QObject *parent = 0);
};

class DeclarativeWidget : public DeclarativeWidgetProxy<QWidget>
{
  DECLARATIVE_OBJECT

  public:
    DeclarativeWidget(QObject *parent = 0);
};

#endif
