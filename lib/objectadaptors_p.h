/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef OBJECTADAPTORS_P_H
#define OBJECTADAPTORS_P_H

#include <QAction>
#include <QButtonGroup>
#include <QColumnView>
#include <QFileDialog>
#include <QInputDialog>
#include <QListView>
#include <QStackedLayout>
#include <QTableView>
#include <QTextEdit>
#include <QTreeView>

class ActionItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QVariant action READ qmlAction WRITE setAction NOTIFY actionChanged)

  public:
    explicit ActionItem(QObject *parent = 0);

    QAction* action();

  Q_SIGNALS:
    void actionChanged();

  private:
    void setAction(const QVariant &action);
    QVariant qmlAction() const;

    QVariant m_action;
    QAction* m_placeholderAction;
    QAction* m_qAction;
};

class ButtonGroup : public QButtonGroup
{
  Q_OBJECT

  Q_PROPERTY(QVariantList buttons READ buttons WRITE setButtons NOTIFY buttonsChanged)

  public:
    explicit ButtonGroup(QObject *parent = 0);

  Q_SIGNALS:
    void buttonsChanged();

  private:
    void setButtons(const QVariantList &buttons);
    QVariantList buttons() const;

    QVariantList m_buttons;
};

class ColumnView : public QColumnView
{
  Q_OBJECT

  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  public:
    explicit ColumnView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);
    void setSelectionModel(QItemSelectionModel *selectionModel);

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel*);
    void selectionModelChanged(QItemSelectionModel*);
};

class FileDialog : public QFileDialog
{
  Q_OBJECT

  Q_PROPERTY(QStringList selectedFiles READ selectedFiles)

  public:
    explicit FileDialog(QWidget *parent = 0);
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
    explicit InputDialog(QWidget *parent = 0);

  Q_SIGNALS:
    void customTextValueChanged();
    void customIntValueChanged();
    void customDoubleValueChanged();
};

class ListView : public QListView
{
  Q_OBJECT

  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  public:
    explicit ListView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);
    void setSelectionModel(QItemSelectionModel *selectionModel);

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel*);
    void selectionModelChanged(QItemSelectionModel*);
};

class StackedLayout : public QStackedLayout
{
  Q_OBJECT

  Q_PROPERTY(int count READ count)
};

class TableView : public QTableView
{
  Q_OBJECT

  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  public:
    explicit TableView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);
    void setSelectionModel(QItemSelectionModel *selectionModel);

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel*);
    void selectionModelChanged(QItemSelectionModel*);
};

class TextEdit : public QTextEdit
{
  Q_OBJECT

  // TODO
  // ideally QTextDocument's property declaration for modified would include the modificationChanged signal
  // as its NOTIFY, this and setTextDocument could then be removed
  Q_PROPERTY(bool modified READ modified NOTIFY modifiedChanged)
  Q_PROPERTY(QTextDocument* document READ document WRITE setTextDocument NOTIFY documentChanged)

  public:
    explicit TextEdit(QWidget *parent = 0);

    void setTextDocument(QTextDocument *document);

  Q_SIGNALS:
    void modifiedChanged();
    void documentChanged();

  private:
    bool modified() const;
};

class TreeView : public QTreeView
{
  Q_OBJECT

  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  public:
    explicit TreeView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);
    void setSelectionModel(QItemSelectionModel *selectionModel);

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel*);
    void selectionModelChanged(QItemSelectionModel*);
};

#endif
