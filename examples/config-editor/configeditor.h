#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

#include <QTextDocument>
#include <QUrl>

class SettingsAdaptor;

class QFileInfo;

class ConfigEditor : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
  Q_PROPERTY(QTextDocument* textDocument READ textDocument CONSTANT)
  Q_PROPERTY(QUrl editorQml READ editorQml NOTIFY editorQmlChanged)
  Q_PROPERTY(QObject* settings READ settings CONSTANT)

  public:
    explicit ConfigEditor(QObject *parent = 0);

    QString fileName() const;

    QTextDocument *textDocument() const;

    QUrl editorQml() const;

    QObject *settings() const;

  public Q_SLOTS:
    void openFile(const QString &fileName);
    void saveText();
    void saveSettings();
    void updateOnSaveDone();

  Q_SIGNALS:
    void fileNameChanged();
    void editorQmlChanged();
    void requestUpdateOnSave();

  private:
    QString m_fileName;
    QUrl m_editorQml;
    QTextDocument *m_textDocument;
    SettingsAdaptor *m_settings;

  private:
    void setFileName(const QString &fileName);
    void setEditorQml(const QUrl &qmlUrl);
    void loadAsText();
    void loadAsSettings(const QUrl &customEditorQml);
    QUrl findCustomEditorQml(const QFileInfo &configFile) const;
};

#endif // EDITOR_H
