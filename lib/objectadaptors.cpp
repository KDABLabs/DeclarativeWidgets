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

#include "objectadaptors_p.h"

#include "declarativeaction_p.h"

#include <QAbstractButton>
#include <QDebug>

// ActionItem
ActionItem::ActionItem(QObject *parent)
  : QObject(parent)
  , m_placeholderAction(new QAction(this))
  , m_qAction(m_placeholderAction)
{
}

QAction* ActionItem::action()
{
  return m_qAction;
}

void ActionItem::setAction(const QVariant &action)
{
  if (m_action == action)
    return;

  m_action = action;

  QObject *object = m_action.value<QObject*>();

  // Is the passed action a QAction ...
  QAction *newAction = qobject_cast<QAction*>(object);

  // ... or a DeclarativeAction
  DeclarativeAction *declarativeAction = dynamic_cast<DeclarativeAction*>(object);
  if (declarativeAction) {
    newAction = qobject_cast<QAction*>(declarativeAction->object());
  }

  // Check if the placeholder must be replaced with the actual action
  if (m_qAction == m_placeholderAction) {
    const QList<QWidget*> widgets = m_placeholderAction->associatedWidgets();
    foreach (QWidget *widget, widgets) {
      // Replace the placeholder action with the new one
      widget->insertAction(m_placeholderAction, newAction);
      widget->removeAction(m_placeholderAction);
    }

    m_qAction = newAction;
  }

  emit actionChanged();
}

QVariant ActionItem::qmlAction() const
{
  return m_action;
}

// ButtonGroup
ButtonGroup::ButtonGroup(QObject *parent)
  : QButtonGroup(parent)
{
}

void ButtonGroup::setButtons(const QVariantList &buttons)
{
  if (m_buttons == buttons)
    return;

  // First remove the old buttons ...
  foreach (const QVariant &variant, m_buttons) {
    QObject *object = variant.value<QObject*>();
    if (object) {
      AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
      if (declarativeObject) {
        QAbstractButton *button = qobject_cast<QAbstractButton*>(declarativeObject->object());
        if (button)
          QButtonGroup::removeButton(button);
      }
    }
  }

  m_buttons = buttons;

  // ... then add the new ones
  foreach (const QVariant &variant, m_buttons) {
    QObject *object = variant.value<QObject*>();
    if (object) {
      AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);
      if (declarativeObject) {
        QAbstractButton *button = qobject_cast<QAbstractButton*>(declarativeObject->object());
        if (button)
          QButtonGroup::addButton(button);
      }
    }
  }

  emit buttonsChanged();
}

QVariantList ButtonGroup::buttons() const
{
  return m_buttons;
}

// ColumnView
ColumnView::ColumnView(QWidget *parent)
  : QColumnView(parent)
{
}

void ColumnView::setModel(QAbstractItemModel *model)
{
  if (this->model() == model)
    return;

  QColumnView::setModel(model);

  emit modelChanged(model);
  emit selectionModelChanged(selectionModel());
}

void ColumnView::setSelectionModel(QItemSelectionModel *selectionModel)
{
  if (this->selectionModel() == selectionModel)
    return;

  QColumnView::setSelectionModel(selectionModel);

  emit selectionModelChanged(selectionModel);
}

// FileDialog
FileDialog::FileDialog(QWidget *parent)
  : QFileDialog(parent)
{
}

// InputDialog
InputDialog::InputDialog(QWidget *parent)
  : QInputDialog(parent)
{
  connect(this, SIGNAL(textValueChanged(QString)), this, SIGNAL(customTextValueChanged()));
  connect(this, SIGNAL(intValueChanged(int)), this, SIGNAL(customIntValueChanged()));
  connect(this, SIGNAL(doubleValueChanged(double)), this, SIGNAL(customDoubleValueChanged()));
}

// ListView
ListView::ListView(QWidget *parent)
  : QListView(parent)
{
}

void ListView::setModel(QAbstractItemModel *model)
{
  if (this->model() == model)
    return;

  QListView::setModel(model);

  emit modelChanged(model);
  emit selectionModelChanged(selectionModel());
}

void ListView::setSelectionModel(QItemSelectionModel *selectionModel)
{
  if (this->selectionModel() == selectionModel)
    return;

  QListView::setSelectionModel(selectionModel);

  emit selectionModelChanged(selectionModel);
}

// TableView
TableView::TableView(QWidget *parent)
  : QTableView(parent)
{
}

void TableView::setModel(QAbstractItemModel *model)
{
  if (this->model() == model)
    return;

  QTableView::setModel(model);

  emit modelChanged(model);
  emit selectionModelChanged(selectionModel());
}

void TableView::setSelectionModel(QItemSelectionModel *selectionModel)
{
  if (this->selectionModel() == selectionModel)
    return;

  QTableView::setSelectionModel(selectionModel);

  emit selectionModelChanged(selectionModel);
}

// TextEdit
TextEdit::TextEdit(QWidget *parent)
  : QTextEdit(parent)
{
  connect(document(), SIGNAL(modificationChanged(bool)), this, SIGNAL(modifiedChanged()));
}

void TextEdit::setTextDocument(QTextDocument *document)
{
  if (document == 0)
    return;

  if (this->document() == document)
    return;

  if (this->document()) {
    disconnect(this->document(), SIGNAL(modificationChanged(bool)), this, SIGNAL(modifiedChanged()));
  }

  const bool oldModified = modified();

  setDocument(document);
  connect(document, SIGNAL(modificationChanged(bool)), this, SIGNAL(modifiedChanged()));

  emit documentChanged();

  if (oldModified != modified())
    emit modifiedChanged();
}

bool TextEdit::modified() const
{
  return document()->isModified();
}

// TreeView
TreeView::TreeView(QWidget *parent)
  : QTreeView(parent)
{
}

void TreeView::setModel(QAbstractItemModel *model)
{
  if (this->model() == model)
    return;

  QTreeView::setModel(model);

  emit modelChanged(model);
  emit selectionModelChanged(selectionModel());
}

void TreeView::setSelectionModel(QItemSelectionModel *selectionModel)
{
  if (this->selectionModel() == selectionModel)
    return;

  QTreeView::setSelectionModel(selectionModel);

  emit selectionModelChanged(selectionModel);
}
