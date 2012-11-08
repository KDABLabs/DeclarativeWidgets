#ifndef EDITOR_H
#define EDITOR_H

#include <QIcon>
#include <QObject>

class QTextDocument;

class Editor : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QTextDocument* document READ document CONSTANT)
  Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

  public:
    explicit Editor(QObject *parent = 0);
    ~Editor();
    
    QTextDocument *document() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

    Q_INVOKABLE QIcon iconFromFile(const QString &fileName) const;
    Q_INVOKABLE QIcon iconFromTheme(const QString &iconName) const;

  Q_SIGNALS:
    void fileNameChanged(const QString &fileName);
    void requestSaveFileName();

    void information(const QString &message);
    void critical(const QString &message);

  public Q_SLOTS:
    void newDocument();
    void open(const QString &fileName);
    void save();

  private:
    QTextDocument *m_document;
    QString m_fileName;
};

#endif // EDITOR_H
