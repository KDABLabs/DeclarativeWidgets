#include "objectadaptors_p.h"

TextEdit::TextEdit(QWidget *parent)
  : QTextEdit(parent)
{
  connect(document(), SIGNAL(modificationChanged(bool)), this, SIGNAL(modifiedChanged()));
}

bool TextEdit::modified() const
{
  return document()->isModified();
}
