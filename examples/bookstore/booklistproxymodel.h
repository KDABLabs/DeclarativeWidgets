#ifndef BOOKLISTPROXYMODEL_H
#define BOOKLISTPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QHash>

class BookListProxyModel : public QAbstractProxyModel
{
  Q_OBJECT

  public:
    enum Roles {
      BookIdRole = Qt::UserRole + 1,
      BookTitleRole,
      BookPriceRole,
      BookNotesRole,
      AuthorIdRole,
      AuthorFirstNameRole,
      AuthorLastNameRole
    };

    explicit BookListProxyModel(QObject *parent = 0);

    void addColumnToRoleMapping(int column, int role);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    QVariant data(const QModelIndex &proxyIndex, int role) const;

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

  private:
    const QHash<int, QByteArray> m_rolesToNames;

    QHash<int, int> m_rolesToSourceColumns;
    QHash<int, int> m_sourceColumnsToRoles;
};

#endif // BOOKLISTPROXYMODEL_H
