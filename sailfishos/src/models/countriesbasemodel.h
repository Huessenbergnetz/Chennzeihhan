/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

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

#ifndef COUNTRIESBASEMODEL_H
#define COUNTRIESBASEMODEL_H

#include <QObject>
#include <QAbstractListModel>

class QSqlQuery;

struct Country {
    Country(uint _id, const QString &_code, const QString &_sign, uint _type, bool _official, const QStringList &_colors, const QString &_name) :
        id(_id), code(_code), sign(_sign), type(_type), official(_official), colors(_colors), name(_name)
    {}
    uint id;
    QString code;
    QString sign;
    uint type;
    bool official;
    QStringList colors;
    QString name;
};

class CountriesBaseModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Id = Qt::UserRole +1,
        Code,
        Sign,
        Type,
        Official,
        Colors,
        Name
    };

    explicit CountriesBaseModel(QObject *parent = nullptr);

    ~CountriesBaseModel();

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


    void clear();


protected:
    void populate(QSqlQuery *q);
    QString getBaseQueryString() const;
    int findBySign(const QString &s) const;
    bool removeBySign(const QString &s);

    void addCountry(Country *c);

private:
    Q_DISABLE_COPY(CountriesBaseModel)
    QList<Country*> m_countries;
};

#endif // COUNTRIESBASEMODEL_H
