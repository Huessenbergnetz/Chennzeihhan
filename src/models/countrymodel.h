#ifndef COUNTRYMODEL_H
#define COUNTRYMODEL_H

//#include <QSqlQueryModel>
#include "simpleitemmodel.h"

//#include "athelper.h"
//#include "dehelper.h"

class CountryModel : public SimpleItemModel
{
    Q_OBJECT
public:
    explicit CountryModel(QObject *parent = nullptr);

//    QVariant data(const QModelIndex &index, int role) const;
//    QHash<int,QByteArray> roleNames() const;

    QString countryCode() const;
    bool inOperation() const;

    void setCountryCode(const QString &nCountryCode);

signals:
    void inOperationChanged(bool inOperation);

public slots:
//    void refresh(const QString &cc, int sort, int searchTarget, const QString &search);

private:
//    const static char* COLUMN_NAMES[];
//    AtHelper *atHelper;
//    DeHelper *deHelper;
//    QString countryCode;
    Q_DISABLE_COPY(CountryModel)
    QString m_countryCode;
    bool m_inOperation;
    void init();
    void setInOperation(bool nInOperation);

};

#endif // COUNTRYMODEL_H
