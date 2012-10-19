#ifndef OBJECTADAPTORS_P_H
#define OBJECTADAPTORS_P_H

#include <QtGui/QTextEdit>

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
