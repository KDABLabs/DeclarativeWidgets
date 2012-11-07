#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class QTextDocument;

class Editor : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QTextDocument* document READ document CONSTANT)

  public:
    explicit Editor(QObject *parent = 0);
    ~Editor();
    
    QTextDocument *document() const;

  public Q_SLOTS:
    void newDocument();

  private:
    QTextDocument *m_document;
};

#endif // EDITOR_H
