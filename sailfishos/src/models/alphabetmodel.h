/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2016  Buschtrommel/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef ALPHABETMODEL_H
#define ALPHABETMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "../globals.h"

class DbManager;
class QStringListModel;

class AlphabetModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Chennzeihhan::Target sorting READ sorting WRITE setSorting NOTIFY sortingChanged)
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    Q_PROPERTY(DbManager *dbManager READ dbManager WRITE setDbManager NOTIFY dbManagerChanged)
    Q_ENUMS(Chennzeihhan::Target)
public:
    explicit AlphabetModel(QObject *parent = nullptr);
    ~AlphabetModel();

    enum Roles {
        Row = Qt::UserRole + 1
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

    Chennzeihhan::Target sorting() const;
    bool inOperation() const;
    DbManager *dbManager() const;

    void setSorting(Chennzeihhan::Target nSorting);
    void setDbManager(DbManager *nDbManager);

    Q_INVOKABLE void init(Chennzeihhan::Target sorting);

signals:
    void sortingChanged(Chennzeihhan::Target sorting);
    void inOperationChanged(bool inOperation);
    void dbManagerChanged(DbManager *dbManager);

private slots:
    void dbChanged();

private:
    Q_DISABLE_COPY(AlphabetModel)
    Chennzeihhan::Target m_sorting;
    bool m_inOperation;
    QList<QStringListModel*> m_alphabet;
    DbManager *m_dbManager;
    void setInOperation(bool nInOperation);
};

#endif // ALPHABETMODEL_H
