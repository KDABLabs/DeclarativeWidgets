#include "declarativetableviewextension_p.h"

#include <QTableView>

DeclarativeTableViewExtension::DeclarativeTableViewExtension(QObject *parent)
  : DeclarativeItemViewExtension(parent)
{
}

QTableView *DeclarativeTableViewExtension::extendedTableView() const
{
  QTableView *tableView = qobject_cast<QTableView*>(extendedItemView());
  Q_ASSERT(tableView);

  return tableView;
}

void DeclarativeTableViewExtension::setHorizontalHeader(QHeaderView *header)
{
  if (header == extendedTableView()->horizontalHeader())
    return;

  extendedTableView()->setHorizontalHeader(header);
  emit horizontalHeaderChanged(header);
}

QHeaderView *DeclarativeTableViewExtension::horizontalHeader() const
{
  return extendedTableView()->horizontalHeader();
}

void DeclarativeTableViewExtension::setVerticalHeader(QHeaderView *header)
{
  if (header == extendedTableView()->verticalHeader())
    return;

  extendedTableView()->setVerticalHeader(header);
  emit verticalHeaderChanged(header);
}

QHeaderView *DeclarativeTableViewExtension::verticalHeader() const
{
  return extendedTableView()->verticalHeader();
}
