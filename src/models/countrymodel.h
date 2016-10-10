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
