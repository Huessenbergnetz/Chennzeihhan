#ifndef COUNTRIESMODELNEW_H
#define COUNTRIESMODELNEW_H

#include "countriesbasemodel.h"

class CountriesModelNew : public CountriesBaseModel
{
    Q_OBJECT
public:
    explicit CountriesModelNew(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(CountriesModelNew)
    void init();
};

#endif // COUNTRIESMODELNEW_H
