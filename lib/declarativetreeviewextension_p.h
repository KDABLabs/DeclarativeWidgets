#ifndef DECLARATIVETREEVIEWEXTENSION_P_H
#define DECLARATIVETREEVIEWEXTENSION_P_H

#include "declarativeitemviewextension_p.h"

class QHeaderView;
class QTreeView;

class DeclarativeTreeViewExtension : public DeclarativeItemViewExtension
{
  Q_OBJECT

  Q_PROPERTY(QHeaderView* header READ header WRITE setHeader NOTIFY headerChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeTreeViewExtension(QObject *parent = 0);

    QTreeView *extendedTreeView() const;

    void setHeader(QHeaderView *header);
    QHeaderView *header() const;

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel *model);
    void selectionModelChanged(QItemSelectionModel *selectionModel);

    void headerChanged(QHeaderView *header);
};

#endif // DECLARATIVETREEVIEWEXTENSION_P_H
