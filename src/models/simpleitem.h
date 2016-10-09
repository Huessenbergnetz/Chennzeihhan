#ifndef SIMPLEITEM
#define SIMPLEITEM

#include <QString>

struct SimpleItem {
    SimpleItem(uint _id, const QString &_name, const QString &_type, const QString &_sign) : id(_id), name(_name), type(_type), sign(_sign) {}
    uint id;
    QString name;
    QString type;
    QString sign;
};

#endif // SIMPLEITEM

