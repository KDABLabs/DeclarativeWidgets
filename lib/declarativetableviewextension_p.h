#ifndef DECLARATIVETABLEVIEWEXTENSION_P_H
#define DECLARATIVETABLEVIEWEXTENSION_P_H

#include "declarativeitemviewextension_p.h"

class QHeaderView;
class QTableView;

class DeclarativeTableViewExtension : public DeclarativeItemViewExtension
{
  Q_OBJECT

  Q_PROPERTY(QHeaderView* horizontalHeader READ horizontalHeader WRITE setHorizontalHeader NOTIFY horizontalHeaderChanged)
  Q_PROPERTY(QHeaderView* verticalHeader READ verticalHeader WRITE setVerticalHeader NOTIFY verticalHeaderChanged)

  // repeat property declarations, qmlRegisterExtendedType doesn't see the ones from base class
  Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)

  Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data DESIGNABLE false)

  Q_CLASSINFO("DefaultProperty", "data")

  public:
    explicit DeclarativeTableViewExtension(QObject *parent = 0);

    QTableView *extendedTableView() const;

    void setHorizontalHeader(QHeaderView *header);
    QHeaderView *horizontalHeader() const;

    void setVerticalHeader(QHeaderView *header);
    QHeaderView *verticalHeader() const;

  Q_SIGNALS:
    void modelChanged(QAbstractItemModel *model);
    void selectionModelChanged(QItemSelectionModel *selectionModel);

    void horizontalHeaderChanged(QHeaderView *header);
    void verticalHeaderChanged(QHeaderView *header);
};

#endif // DECLARATIVETABLEVIEWEXTENSION_P_H
