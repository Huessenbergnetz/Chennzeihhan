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

#ifndef COUNTRYMODEL_H
#define COUNTRYMODEL_H

#include "simpleitemmodel.h"

class CountryModel : public SimpleItemModel
{
    Q_OBJECT
public:
    explicit CountryModel(QObject *parent = nullptr);

    QString countryCode() const;
    bool inOperation() const;

    void setCountryCode(const QString &nCountryCode);

signals:
    void inOperationChanged(bool inOperation);

private:
    Q_DISABLE_COPY(CountryModel)
    QString m_countryCode;
    bool m_inOperation;
    void init();
    void setInOperation(bool nInOperation);

};

#endif // COUNTRYMODEL_H
