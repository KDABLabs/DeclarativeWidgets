#include "declarativetreeviewextension_p.h"

#include <QTreeView>

DeclarativeTreeViewExtension::DeclarativeTreeViewExtension(QObject *parent)
  : DeclarativeItemViewExtension(parent)
{
}

QTreeView *DeclarativeTreeViewExtension::extendedTreeView() const
{
  QTreeView *treeView = qobject_cast<QTreeView*>(extendedItemView());
  Q_ASSERT(treeView);

  return treeView;
}

void DeclarativeTreeViewExtension::setHeader(QHeaderView *header)
{
  if (header == extendedTreeView()->header())
    return;

  extendedTreeView()->setHeader(header);
  emit headerChanged(header);
}

QHeaderView *DeclarativeTreeViewExtension::header() const
{
  return extendedTreeView()->header();
}
