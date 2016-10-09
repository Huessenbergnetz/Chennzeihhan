#include "simpleitemmodel.h"

SimpleItemModel::SimpleItemModel(QObject *parent) : QAbstractListModel(parent)
{

}


SimpleItemModel::~SimpleItemModel()
{
    qDeleteAll(m_items);
    m_items.clear();
}



void SimpleItemModel::clear()
{
    if (!m_items.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, m_items.count() - 1);

        qDeleteAll(m_items);
        m_items.clear();

        endRemoveRows();
    }
}


int SimpleItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}



QHash<int, QByteArray> SimpleItemModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Id, QByteArrayLiteral("id"));
    roles.insert(Name, QByteArrayLiteral("name"));
    roles.insert(Type, QByteArrayLiteral("type"));
    roles.insert(Sign, QByteArrayLiteral("sign"));
    return roles;
}



QModelIndex SimpleItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}


QVariant SimpleItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount() - 1)) {
        return QVariant();
    }

    SimpleItem *si = m_items.at(index.row());

    switch(role) {
    case Id:
        return QVariant::fromValue(si->id);
    case Name:
        return QVariant::fromValue(si->name);
    case Type:
        return QVariant::fromValue(si->type);
    case Sign:
        return QVariant::fromValue(si->sign);
    default:
        return QVariant();
    }
}



void SimpleItemModel::addItem(SimpleItem *i)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_items.append(i);

    endInsertRows();
}



void SimpleItemModel::addItem(uint id, const QString &name, const QString &type, const QString &sign)
{
    addItem(new SimpleItem(id, name, type, sign));
}



void SimpleItemModel::addItems(const QList<SimpleItem *> &items)
{
    if (!items.isEmpty()) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.count() -1);

        m_items.append(items);

        endInsertRows();
    }
}
