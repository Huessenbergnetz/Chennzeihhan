#ifndef SIMPLEITEM
#define SIMPLEITEM

#include <QString>

struct SimpleItem {
    SimpleItem(uint _id, const QString &_name, const QString &_type, const QString &_sign, const QString _state = QString(), bool _closed = false) :
        id(_id), name(_name), type(_type), sign(_sign), state(_state), closed(_closed)
    {}
    uint id;
    QString name;
    QString type;
    QString sign;
    QString state;
    bool closed;
};

#endif // SIMPLEITEM

