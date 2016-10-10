#ifndef ATITEM_H
#define ATITEM_H

#include <QObject>
#include "extendeditem.h"

class AtItem : public ExtendedItem
{
    Q_OBJECT
public:
    explicit AtItem(QObject *parent = nullptr);

    ~AtItem();

protected:
    void clear();
    void query();
};

#endif // ATITEM_H
