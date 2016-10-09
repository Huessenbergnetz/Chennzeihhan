#ifndef DEITEM_H
#define DEITEM_H

#include "extendeditem.h"
#include <QObject>

class DeItem : public ExtendedItem
{
    Q_OBJECT
public:
    explicit DeItem(QObject *parent = nullptr);

    ~DeItem();

protected:
    void clear();
    void query();
};

#endif // DEITEM_H
