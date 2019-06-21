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

#ifndef ITEM_H
#define ITEM_H

#include <QObject>

class CoverConnector;

/*!
 * \brief The Item class.
 */
class Item : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sign READ sign NOTIFY signChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString capital READ capital NOTIFY capitalChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    Q_PROPERTY(quint16 founded READ founded NOTIFY foundedChanged)
    Q_PROPERTY(quint16 disbanded READ disbanded NOTIFY disbandedChanged)
    Q_PROPERTY(quint16 optional READ optional NOTIFY optionalChanged)
    Q_PROPERTY(QString wikipedia READ wikipedia NOTIFY wikipediaChanged)
    Q_PROPERTY(QString coa READ coa NOTIFY coaChanged)
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    Q_PROPERTY(uint id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString countryCode READ countryCode CONSTANT)
    Q_PROPERTY(QString countryName READ countryName CONSTANT)
    Q_PROPERTY(CoverConnector *coverConnector READ coverConnector WRITE setCoverConnector NOTIFY coverConnectorChanged)
public:
    explicit Item(QObject *parent = nullptr);
    ~Item();

    QString sign() const;
    QString name() const;
    QString capital() const;
    QString type() const;
    QString state() const;
    quint16 founded() const;
    quint16 disbanded() const;
    quint16 optional() const;
    QString wikipedia() const;
    QString coa() const;
    bool inOperation() const;
    uint id() const;
    QString countryCode() const;
    QString countryName() const;
    CoverConnector *coverConnector() const;

    void setId(uint nId);
    void setCoverConnector(CoverConnector *nCoverConnector);

signals:
    void signChanged(const QString &sign);
    void nameChanged(const QString &name);
    void capitalChanged(const QString &capital);
    void typeChanged(const QString &type);
    void stateChanged(const QString &state);
    void foundedChanged(quint16 founded);
    void disbandedChanged(quint16 disbanded);
    void optionalChanged(quint16 optional);
    void wikipediaChanged(const QString &wikipedia);
    void coaChanged(const QString &coa);
    void inOperationChanged(bool inOperation);
    void idChanged(uint id);
    void coverConnectorChanged(CoverConnector *coverConnector);

protected:
    void setSign(const QString &nSign);
    void setName(const QString &nName);
    void setCapital(const QString &nCapital);
    void setType(const QString &nType);
    void setState(const QString &nState);
    void setFounded(quint16 nFounded);
    void setDisbanded(quint16 nDisbanded);
    void setOptional(quint16 nOptional);
    void setWikipedia(const QString &nWikipedia);
    void setCoa(const QString &nCoa);
    void setInOperation(bool nInOperation);
    void setCountryCode(const QString &cc);
    void setCountryName(const QString &cn);
    CoverConnector *m_coverConnector;

    virtual void query();
    virtual void clear();

private:
    Q_DISABLE_COPY(Item)
    QString m_sign;
    QString m_name;
    QString m_capital;
    QString m_type;
    QString m_state;
    quint16 m_founded;
    quint16 m_disbanded;
    quint16 m_optional;
    QString m_wikipedia;
    QString m_coa;
    bool m_inOperation;
    uint m_id;
    QString m_countryCode;
    QString m_countryName;
};

#endif // ITEM_H
