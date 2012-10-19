#ifndef OBJECTADAPTORS_P_H
#define OBJECTADAPTORS_P_H

#include <QtGui/QFileDialog>
#include <QtGui/QInputDialog>
#include <QtGui/QTextEdit>

class FileDialog : public QFileDialog
{
  Q_OBJECT

  Q_PROPERTY(QStringList selectedFiles READ selectedFiles)

  public:
    FileDialog(QWidget *parent = 0);
};

class InputDialog : public QInputDialog
{
  Q_OBJECT

  Q_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode)
  Q_PROPERTY(QString labelText READ labelText WRITE setLabelText)
  Q_PROPERTY(InputDialogOptions options READ options WRITE setOptions)
  Q_PROPERTY(QString textValue READ textValue WRITE setTextValue NOTIFY customTextValueChanged)
  Q_PROPERTY(int intValue READ intValue WRITE setIntValue NOTIFY customIntValueChanged)
  Q_PROPERTY(int doubleValue READ doubleValue WRITE setDoubleValue NOTIFY customDoubleValueChanged)
  Q_PROPERTY(QLineEdit::EchoMode textEchoMode READ textEchoMode WRITE setTextEchoMode)
  Q_PROPERTY(bool comboBoxEditable READ isComboBoxEditable WRITE setComboBoxEditable)
  Q_PROPERTY(QStringList comboBoxItems READ comboBoxItems WRITE setComboBoxItems)
  Q_PROPERTY(int intMinimum READ intMinimum WRITE setIntMinimum)
  Q_PROPERTY(int intMaximum READ intMaximum WRITE setIntMaximum)
  Q_PROPERTY(int intStep READ intStep WRITE setIntStep)
  Q_PROPERTY(double doubleMinimum READ doubleMinimum WRITE setDoubleMinimum)
  Q_PROPERTY(double doubleMaximum READ doubleMaximum WRITE setDoubleMaximum)
  Q_PROPERTY(int doubleDecimals READ doubleDecimals WRITE setDoubleDecimals)
  Q_PROPERTY(QString okButtonText READ okButtonText WRITE setOkButtonText)
  Q_PROPERTY(QString cancelButtonText READ cancelButtonText WRITE setCancelButtonText)

  Q_ENUMS(InputMode)
  Q_ENUMS(InputDialogOption)

  public:
    InputDialog(QWidget *parent = 0);

  Q_SIGNALS:
    void customTextValueChanged();
    void customIntValueChanged();
    void customDoubleValueChanged();
};

class TextEdit : public QTextEdit
{
  Q_OBJECT

  Q_PROPERTY(bool modified READ modified NOTIFY modifiedChanged)

  public:
    TextEdit(QWidget *parent = 0);

  Q_SIGNALS:
    void modifiedChanged();

  private:
    bool modified() const;
};

#endif
