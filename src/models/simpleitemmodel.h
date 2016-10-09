#ifndef SIMPLEITEMMODEL_H
#define SIMPLEITEMMODEL_H

#include <QAbstractListModel>
#include "simpleitem.h"

class SimpleItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SimpleItemModel(QObject *parent = nullptr);

    ~SimpleItemModel();

    enum Roles {
        Id = Qt::UserRole + 1,
        Name,
        Type,
        Sign
    };

    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractListModel.
     */
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;


    void addItem(SimpleItem *i);

    void addItem(uint id, const QString &name, const QString &type, const QString &sign);

    void addItems(const QList<SimpleItem*> &items);

    void clear();

private:
    Q_DISABLE_COPY(SimpleItemModel)
    QList<SimpleItem*> m_items;
};

#endif // SIMPLEITEMMODEL_H
