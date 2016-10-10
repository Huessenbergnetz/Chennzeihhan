#ifndef CHITEM_H
#define CHITEM_H

#include <QObject>
#include "item.h"

class ChItem : public Item
{
    Q_OBJECT
public:
    explicit ChItem(QObject *parent = nullptr);

    ~ChItem();

protected:
    void clear();
    void query();
};

#endif // CHITEM_H
