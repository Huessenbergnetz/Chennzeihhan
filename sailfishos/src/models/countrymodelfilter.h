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

#ifndef COUNTRYMODELFILTER_H
#define COUNTRYMODELFILTER_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "../globals.h"

class QTimer;
class CountryModel;

class CountryModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(Chennzeihhan::Target searchTarget READ searchTarget WRITE setSearchTarget NOTIFY searchTargetChanged)
    Q_PROPERTY(Chennzeihhan::Target sortTarget READ sortTarget WRITE setSortTarget NOTIFY sortTargetChanged)
    Q_PROPERTY(QString countryCode READ countryCode WRITE setCountryCode NOTIFY countryCodeChanged)
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    Q_ENUMS(Chennzeihhan::Target)
public:
    explicit CountryModelFilter(QObject *parent = nullptr);

    QString search() const;
    Chennzeihhan::Target searchTarget() const;
    Chennzeihhan::Target sortTarget() const;
    QString countryCode() const;
    bool inOperation() const;

    void setSearch(const QString &nSearch);
    void setSearchTarget(Chennzeihhan::Target nSearchTarget);
    void setSortTarget(Chennzeihhan::Target nSortTarget);
    void setCountryCode(const QString &nCountryCode);

signals:
    void searchChanged(const QString &search);
    void searchTargetChanged(Chennzeihhan::Target searchTarget);
    void sortTargetChanged(Chennzeihhan::Target sortTarget);
    void countryCodeChanged(const QString &countryCode);
    void inOperationChanged(bool inOperation);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private slots:
    void searchStringChanged();

private:
    Q_DISABLE_COPY(CountryModelFilter)
    QString m_search;
    Chennzeihhan::Target m_searchTarget;
    Chennzeihhan::Target m_sortTarget;
    QTimer *m_timer;
    CountryModel *m_cm;
};

#endif // COUNTRYMODELFILTER_H
